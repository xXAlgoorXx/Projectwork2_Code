 /**
 ******************************************************************************
 * @file    main.c
 * @author  GPM Application Team
 *
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "stm32n6570_discovery_bus.h"
#include "stm32n6570_discovery_xspi.h"
#include "stm32n6570_discovery.h"
#include "app_fuseprogramming.h"
#include "ll_aton_runtime.h"
#include "main.h"
#include <stdio.h>
#include "stm32n6xx_hal_rif.h"
#include "app_config.h"
#include "arm_math.h"



#define MAX_NUMBER_OUTPUT 5

uint8_t *nn_in;
void *pp_input;
char const *nn_top1_output_class_name;
float nn_top1_output_class_proba;

#define ALIGN_TO_16(value) (((value) + 15) & ~15)

/* for models not multiple of 16; needs a working buffer */
#if (NN_WIDTH * NN_BPP) != ALIGN_TO_16(NN_WIDTH * NN_BPP)
#define DCMIPP_OUT_NN_LEN (ALIGN_TO_16(NN_WIDTH * NN_BPP) * NN_HEIGHT)
#define DCMIPP_OUT_NN_BUFF_LEN (DCMIPP_OUT_NN_LEN + 32 - DCMIPP_OUT_NN_LEN%32)

__attribute__ ((aligned (32)))
uint8_t dcmipp_out_nn[DCMIPP_OUT_NN_BUFF_LEN];
#else
uint8_t *dcmipp_out_nn;
#endif

static void SystemClock_Config(void);
static void NPURam_enable(void);
static void NPUCache_config(void);
static void Network_Postprocess(void);
static void Bubblesort(float *prob, int *classes, int size);
static void Security_Config(void);
static void set_clk_sleep_mode(void);
static void IAC_Config(void);

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Power on ICACHE */
  MEMSYSCTL->MSCR |= MEMSYSCTL_MSCR_ICACTIVE_Msk;

  /* Set back system and CPU clock source to HSI */
  __HAL_RCC_CPUCLK_CONFIG(RCC_CPUCLKSOURCE_HSI);
  __HAL_RCC_SYSCLK_CONFIG(RCC_SYSCLKSOURCE_HSI);

  HAL_Init();

  SCB_EnableICache();

#if defined(USE_DCACHE)
  /* Power on DCACHE */
  MEMSYSCTL->MSCR |= MEMSYSCTL_MSCR_DCACTIVE_Msk;
  SCB_EnableDCache();
#endif

  SystemClock_Config();

  NPURam_enable();

  Fuse_Programming();

  NPUCache_config();

  /*** External RAM and NOR Flash *********************************************/
  BSP_XSPI_RAM_Init(0);
  BSP_XSPI_RAM_EnableMemoryMappedMode(0);

  BSP_XSPI_NOR_Init_t NOR_Init;
  NOR_Init.InterfaceMode = BSP_XSPI_NOR_OPI_MODE;
  NOR_Init.TransferRate = BSP_XSPI_NOR_DTR_TRANSFER;
  BSP_XSPI_NOR_Init(0, &NOR_Init);
  BSP_XSPI_NOR_EnableMemoryMappedMode(0);

  /* Set all required IPs as secure privileged */
  Security_Config();

  IAC_Config();
  set_clk_sleep_mode();

  /*** NN Init ****************************************************************/
  LL_ATON_DECLARE_NAMED_NN_INSTANCE_AND_INTERFACE(Default);
  const LL_Buffer_InfoTypeDef *nn_in_info = LL_ATON_Input_Buffers_Info_Default();
  const LL_Buffer_InfoTypeDef *nn_out_info = LL_ATON_Output_Buffers_Info_Default();

  nn_in = (uint8_t *) LL_Buffer_addr_start(&nn_in_info[0]);
  float32_t *nn_out[MAX_NUMBER_OUTPUT];
  int32_t nn_out_len[MAX_NUMBER_OUTPUT];

  int number_output = 0;

  /* Count number of outputs */
  while (nn_out_info[number_output].name != NULL)
  {
    number_output++;
  }
  assert(number_output <= MAX_NUMBER_OUTPUT);

  for (int i = 0; i < number_output; i++)
  {
    nn_out[i] = (float32_t *) LL_Buffer_addr_start(&nn_out_info[i]);
    nn_out_len[i] = LL_Buffer_len(&nn_out_info[i]);
  }

  uint32_t nn_in_len = LL_Buffer_len(&nn_in_info[0]);
  uint32_t pitch_nn = 0;

  UNUSED(nn_in_len);

  /*** Post Processing Init ***************************************************/
  pp_input = nn_out[0];


  /*** App Loop ***************************************************************/
  while (1)
  {

    if (pitch_nn != (NN_WIDTH * NN_BPP))
    {
      /* Start NN camera single capture Snapshot */
//      CAM_NNPipe_Start(dcmipp_out_nn, CMW_MODE_SNAPSHOT);
    }
    else
    {
      /* Start NN camera single capture Snapshot */
//      CAM_NNPipe_Start(nn_in, CMW_MODE_SNAPSHOT);
    }


    uint32_t ts[2] = { 0 };

    if (pitch_nn != (NN_WIDTH * NN_BPP))
    {
      SCB_InvalidateDCache_by_Addr(dcmipp_out_nn, sizeof(dcmipp_out_nn));
//      img_crop(dcmipp_out_nn, nn_in, pitch_nn, NN_WIDTH, NN_HEIGHT, NN_BPP);
      SCB_CleanInvalidateDCache_by_Addr(nn_in, nn_in_len);
    }

    ts[0] = HAL_GetTick();
    /* run ATON inference */
    LL_ATON_RT_Main(&NN_Instance_Default);
    ts[1] = HAL_GetTick();
    Network_Postprocess();

    uint32_t time  =  ts[1] - ts[0];
    /* Discard nn_out region (used by pp_input and pp_outputs variables) to avoid Dcache evictions during nn inference */
    for (int i = 0; i < number_output; i++)
    {
      float32_t *tmp = nn_out[i];
      SCB_InvalidateDCache_by_Addr(tmp, nn_out_len[i]);
    }
  }
}

static void NPURam_enable(void)
{
  __HAL_RCC_NPU_CLK_ENABLE();
  __HAL_RCC_NPU_FORCE_RESET();
  __HAL_RCC_NPU_RELEASE_RESET();

  /* Enable NPU RAMs (4x448KB) */
  __HAL_RCC_AXISRAM3_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM4_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM5_MEM_CLK_ENABLE();
  __HAL_RCC_AXISRAM6_MEM_CLK_ENABLE();
  __HAL_RCC_RAMCFG_CLK_ENABLE();
  RAMCFG_HandleTypeDef hramcfg = {0};
  hramcfg.Instance =  RAMCFG_SRAM3_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);
  hramcfg.Instance =  RAMCFG_SRAM4_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);
  hramcfg.Instance =  RAMCFG_SRAM5_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);
  hramcfg.Instance =  RAMCFG_SRAM6_AXI;
  HAL_RAMCFG_EnableAXISRAM(&hramcfg);
}

static void set_clk_sleep_mode(void)
{
  /*** Enable sleep mode support during NPU inference *************************/
  /* Configure peripheral clocks to remain active during sleep mode */
  /* Keep all IP's enabled during WFE so they can wake up CPU. Fine tune
   * this if you want to save maximum power
   */
  __HAL_RCC_XSPI1_CLK_SLEEP_ENABLE();    /* For display frame buffer */
  __HAL_RCC_XSPI2_CLK_SLEEP_ENABLE();    /* For NN weights */
  __HAL_RCC_NPU_CLK_SLEEP_ENABLE();      /* For NN inference */
  __HAL_RCC_CACHEAXI_CLK_SLEEP_ENABLE(); /* For NN inference */
  __HAL_RCC_LTDC_CLK_SLEEP_ENABLE();     /* For display */
  __HAL_RCC_DMA2D_CLK_SLEEP_ENABLE();    /* For display */
  __HAL_RCC_DCMIPP_CLK_SLEEP_ENABLE();   /* For camera configuration retention */
  __HAL_RCC_CSI_CLK_SLEEP_ENABLE();      /* For camera configuration retention */

  __HAL_RCC_FLEXRAM_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM1_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM2_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM3_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM4_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM5_MEM_CLK_SLEEP_ENABLE();
  __HAL_RCC_AXISRAM6_MEM_CLK_SLEEP_ENABLE(); 

}

static void NPUCache_config(void)
{

  npu_cache_init();
  npu_cache_enable();
}

static void Security_Config(void)
{
  __HAL_RCC_RIFSC_CLK_ENABLE();
  RIMC_MasterConfig_t RIMC_master = {0};
  RIMC_master.MasterCID = RIF_CID_1;
  RIMC_master.SecPriv = RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV;
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_NPU, &RIMC_master);
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_DMA2D, &RIMC_master);
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_DCMIPP, &RIMC_master);
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_LTDC1 , &RIMC_master);
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_LTDC2 , &RIMC_master);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_NPU , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_DMA2D , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_CSI    , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_DCMIPP , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_LTDC   , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_LTDCL1 , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_LTDCL2 , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
}

static void IAC_Config(void)
{
/* Configure IAC to trap illegal access events */
  __HAL_RCC_IAC_CLK_ENABLE();
  __HAL_RCC_IAC_FORCE_RESET();
  __HAL_RCC_IAC_RELEASE_RESET();
}

void IAC_IRQHandler(void)
{
  while (1)
  {
  }
}


/**
 * @brief Run post-processing operation
 */
void Network_Postprocess(void)
{
  int ranking[NB_CLASSES];

  /**Perform ranking**/
  for (int i = 0; i < NB_CLASSES; i++)
  {
    ranking[i] = i;
  }

  Bubblesort((float *) (pp_input), ranking, NB_CLASSES);

//  nn_top1_output_class_name = classes_table[ranking[0]];
  nn_top1_output_class_proba = *((float *) (pp_input));
}

/**
 * @brief Bubble sorting algorithm on probabilities
 * @param prob pointer to probabilities buffer
 * @param classes pointer to classes buffer
 * @param size numer of values
 */
static void Bubblesort(float *prob, int *classes, int size)
{
  float p;
  int c;

  for (int i = 0; i < size; i++)
  {
    for (int ii = 0; ii < size - i - 1; ii++)
    {
      if (prob[ii] < prob[ii + 1])
      {
        p = prob[ii];
        prob[ii] = prob[ii + 1];
        prob[ii + 1] = p;
        c = classes[ii];
        classes[ii] = classes[ii + 1];
        classes[ii + 1] = c;
      }
    }
  }
}


/**
  * @brief  DCMIPP Clock Config for DCMIPP.
  * @param  hcsi  DCMIPP Handle
  *         Being __weak it can be overwritten by the application
  * @retval HAL_status
  */
HAL_StatusTypeDef MX_DCMIPP_ClockConfig(DCMIPP_HandleTypeDef *hdcmipp)
{
  RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct = {0};
  HAL_StatusTypeDef ret = HAL_OK;

  RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_DCMIPP;
  RCC_PeriphCLKInitStruct.DcmippClockSelection = RCC_DCMIPPCLKSOURCE_IC17;
  RCC_PeriphCLKInitStruct.ICSelection[RCC_IC17].ClockSelection = RCC_ICCLKSOURCE_PLL2;
  RCC_PeriphCLKInitStruct.ICSelection[RCC_IC17].ClockDivider = 3;
  ret = HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);
  if (ret)
  {
    return ret;
  }

  RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CSI;
  RCC_PeriphCLKInitStruct.ICSelection[RCC_IC18].ClockSelection = RCC_ICCLKSOURCE_PLL1;
  RCC_PeriphCLKInitStruct.ICSelection[RCC_IC18].ClockDivider = 40;
  ret = HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);
  if (ret)
  {
    return ret;
  }

  return ret;
}

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct = {0};

  /* Ensure VDDCORE=0.9V before increasing the system frequency */
  BSP_SMPS_Init(SMPS_VOLTAGE_OVERDRIVE);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;

  /* PLL1 = 64 x 25 / 2 = 800MHz */
  RCC_OscInitStruct.PLL1.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL1.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL1.PLLM = 2;
  RCC_OscInitStruct.PLL1.PLLN = 25;
  RCC_OscInitStruct.PLL1.PLLFractional = 0;
  RCC_OscInitStruct.PLL1.PLLP1 = 1;
  RCC_OscInitStruct.PLL1.PLLP2 = 1;

  /* PLL2 = 64 x 125 / 8 = 1000MHz */
  RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL2.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL2.PLLM = 8;
  RCC_OscInitStruct.PLL2.PLLFractional = 0;
  RCC_OscInitStruct.PLL2.PLLN = 125;
  RCC_OscInitStruct.PLL2.PLLP1 = 1;
  RCC_OscInitStruct.PLL2.PLLP2 = 1;

  /* PLL3 = (64 x 225 / 8) / (1 * 2) = 900MHz */
  RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL3.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL3.PLLM = 8;
  RCC_OscInitStruct.PLL3.PLLN = 225;
  RCC_OscInitStruct.PLL3.PLLFractional = 0;
  RCC_OscInitStruct.PLL3.PLLP1 = 1;
  RCC_OscInitStruct.PLL3.PLLP2 = 2;

  /* PLL4 = (64 x 225 / 8) / (6 * 6) = 50 MHz */
  RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL4.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL4.PLLM = 8;
  RCC_OscInitStruct.PLL4.PLLFractional = 0;
  RCC_OscInitStruct.PLL4.PLLN = 225;
  RCC_OscInitStruct.PLL4.PLLP1 = 6;
  RCC_OscInitStruct.PLL4.PLLP2 = 6;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1);
  }

  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_CPUCLK | RCC_CLOCKTYPE_SYSCLK |
                                 RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 |
                                 RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK4 |
                                 RCC_CLOCKTYPE_PCLK5);

  /* CPU CLock (sysa_ck) = ic1_ck = PLL1 output/ic1_divider = 800 MHz */
  RCC_ClkInitStruct.CPUCLKSource = RCC_CPUCLKSOURCE_IC1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_IC2_IC6_IC11;
  RCC_ClkInitStruct.IC1Selection.ClockSelection = RCC_ICCLKSOURCE_PLL1;
  RCC_ClkInitStruct.IC1Selection.ClockDivider = 1;

  /* AXI Clock (sysb_ck) = ic2_ck = PLL1 output/ic2_divider = 400 MHz */
  RCC_ClkInitStruct.IC2Selection.ClockSelection = RCC_ICCLKSOURCE_PLL1;
  RCC_ClkInitStruct.IC2Selection.ClockDivider = 2;

  /* NPU Clock (sysc_ck) = ic6_ck = PLL2 output/ic6_divider = 1000 MHz */
  RCC_ClkInitStruct.IC6Selection.ClockSelection = RCC_ICCLKSOURCE_PLL2;
  RCC_ClkInitStruct.IC6Selection.ClockDivider = 1;

  /* AXISRAM3/4/5/6 Clock (sysd_ck) = ic11_ck = PLL3 output/ic11_divider = 900 MHz */
  RCC_ClkInitStruct.IC11Selection.ClockSelection = RCC_ICCLKSOURCE_PLL3;
  RCC_ClkInitStruct.IC11Selection.ClockDivider = 1;

  /* HCLK = sysb_ck / HCLK divider = 200 MHz */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;

  /* PCLKx = HCLK / PCLKx divider = 200 MHz */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;
  RCC_ClkInitStruct.APB5CLKDivider = RCC_APB5_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
  {
    while(1);
  }

  RCC_PeriphCLKInitStruct.PeriphClockSelection = 0;

  /* XSPI1 kernel clock (ck_ker_xspi1) = HCLK = 200MHz */
  RCC_PeriphCLKInitStruct.PeriphClockSelection |= RCC_PERIPHCLK_XSPI1;
  RCC_PeriphCLKInitStruct.Xspi1ClockSelection = RCC_XSPI1CLKSOURCE_HCLK;

  /* XSPI2 kernel clock (ck_ker_xspi1) = HCLK =  200MHz */
  RCC_PeriphCLKInitStruct.PeriphClockSelection |= RCC_PERIPHCLK_XSPI2;
  RCC_PeriphCLKInitStruct.Xspi2ClockSelection = RCC_XSPI2CLKSOURCE_HCLK;

  if (HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct) != HAL_OK)
  {
    while (1);
  }
}

void HAL_CACHEAXI_MspInit(CACHEAXI_HandleTypeDef *hcacheaxi)
{
  __HAL_RCC_CACHEAXIRAM_MEM_CLK_ENABLE();
  __HAL_RCC_CACHEAXI_CLK_ENABLE();
  __HAL_RCC_CACHEAXI_FORCE_RESET();
  __HAL_RCC_CACHEAXI_RELEASE_RESET();
}

void HAL_CACHEAXI_MspDeInit(CACHEAXI_HandleTypeDef *hcacheaxi)
{
  __HAL_RCC_CACHEAXIRAM_MEM_CLK_DISABLE();
  __HAL_RCC_CACHEAXI_CLK_DISABLE();
  __HAL_RCC_CACHEAXI_FORCE_RESET();
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  UNUSED(file);
  UNUSED(line);
  __BKPT(0);
  while (1)
  {
  }
}

#endif
