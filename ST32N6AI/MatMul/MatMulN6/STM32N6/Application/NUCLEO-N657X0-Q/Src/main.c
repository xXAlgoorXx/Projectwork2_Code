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
#include "stm32n6xx_hal.h"
#include "stm32n6xx_nucleo_bus.h"
#include "stm32n6xx_nucleo_xspi.h"
#include "stm32n6xx_nucleo.h"

#include "app_fuseprogramming.h"
#include "ll_aton_runtime.h"
#include "main.h"
#include <stdio.h>
#include "arm_math.h"

#define MAX_NUMBER_OUTPUT 1
#define WEIGHTS_BASE_ADDR ((float *)0x70380000)
#define NUM_WEIGHTS 100  // 10 x 10 matrix
#define SIZE 10

static void SystemClock_Config(void);
static void NPURam_enable(void);
static void NPUCache_config(void);

static void Security_Config(void);
static void set_clk_sleep_mode(void);
static void IAC_Config(void);

static void Hardware_init(void);
static void NeuralNetwork_init(uint32_t *nnin_length, int8_t *nn_out[], int *number_output, int32_t nn_out_len[]);

// Lukas added funcitons
void Error_Handler(void);
void nn_simulation(void);
void nn_simulation_int(void);
void update_dense_weights(const float *new_weights);

COM_InitTypeDef BspCOMInit;
int8_t *nn_in;

int8_t dense_weights[10][10] = {
    {  47,   50,   45, -107,   11,  -26,  -29,  -78,  -17, -127 },
    {  86, -120,  -24,   52, -120,  -38,  127,   64,  -17, -116 },
    {  54,  -73,  -17,  -40,  125,  -42,  -15,  -89,   52,  127 },
    {-126,   -5,   24,  -43,  -24,   37, -127,   42,  113,  -43 },
    { -55,  -44,   75,  124,  -97,   84,   45, -102,   82, -127 },
    {-105,  -32,  -53,  -30,  127,   73,   -4,   46,  -58,   86 },
    {  44,    7,  -29, -120,   44,   62,   45, -125,  -81, -127 },
    { -38, -127,  106,   36,   -5,  -70,  -27,  -58,  -91,   21 },
    {-120,  104,   67, -110,  127,    7,  -46,  -17,  -51,   39 },
    {  25, -119,   -9,    4,  -96, -110,  127, -113, -118,   -3 }
};

void enableTiming_Cyc(void){
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;  // Enable cycle counter
}

void startTiming_Cyc(void){
	DWT->CYCCNT = 0; // Reset counter
}

uint32_t getTiming_Cyc(){
	uint32_t cycles = DWT->CYCCNT;
	return cycles;
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

int main(void)
{
    BSP_LED_Init(LED_BLUE);
    Hardware_init();
    printf("Init NN\n\r");
    BSP_LED_On(LED_BLUE);
    enableTiming_Cyc();

    /*** NN Init ****************************************************************/
    uint32_t nn_in_len = 0;
    int number_output = 0;
    int8_t *nn_out[MAX_NUMBER_OUTPUT];
    int32_t nn_out_len[MAX_NUMBER_OUTPUT];

    // Declare instance + interface
    LL_ATON_DECLARE_NAMED_NN_INSTANCE_AND_INTERFACE(Default);
    NeuralNetwork_init(&nn_in_len, nn_out, &number_output, nn_out_len);

    printf("Input length: %lu bytes\n\r", nn_in_len);
    printf("Number of output tensors: %d\n\r", number_output);

    /*** Prepare Quantized INT8 Input *******************************************/
    // This should match the expected input size of your network
    int8_t matrix1_q[100] = {
        129, 131, 133, 135, 136, 138, 140, 142, 144, 146,
        // Fill the rest with quantized int8 values (range -128 to 127)
    };

    // Optional: Quantization details if you want to convert float -> int8
    float input_scale = 0.003917836584150791f;
    int input_zero_point = 128;

    // If you're converting float to int8 dynamically:
    /*
    float matrix1_f[100] = { ... };
    for (int i = 0; i < 100; i++) {
        int32_t q = (int32_t)(matrix1_f[i] / input_scale + input_zero_point);
        if (q < -128) q = -128;
        if (q > 127) q = 127;
        matrix1_q[i] = (int8_t)q;
    }
    */


    while (1)
    {
        uint32_t ts[2] = { 0 };
        uint32_t cyclesCPU = 0;
		uint32_t cyclesNPU = 0;


        // Copy quantized input data
        memcpy(nn_in, matrix1_q, nn_in_len);
        SCB_CleanDCache_by_Addr(nn_in, nn_in_len);

        // Run inference
        ts[0] = HAL_GetTick();
        startTiming_Cyc();
        LL_ATON_RT_Main(&NN_Instance_Default);
        cyclesNPU = getTiming_Cyc();
        ts[1] = HAL_GetTick();
        printf("Inference time NPU: %lu ms\n\r", ts[1] - ts[0]);
        printf("Inference cycles NPU: %lu cycles\n\r", cyclesNPU);

        /*** Output: Dequantize INT8 -> Float ***********************************/
        float output_scale = 0.010583024471998215f;
        int output_zero_point = -50;

        for (int i = 0; i < number_output; i++) {
            int8_t *out_buf = nn_out[i];
            int num_bytes = nn_out_len[i];
            SCB_InvalidateDCache_by_Addr((void*)out_buf, num_bytes);

            printf("Output %d:\n\r", i);
            for (int j = 0; j < num_bytes; j++) {
                float val = (out_buf[j] - output_zero_point) * output_scale;
                printf("  %10.6f, Int: %4d\n\r", val, out_buf[j]);

            }
            printf("\n\r");
        }

        ts[0] = HAL_GetTick();
        startTiming_Cyc();
        nn_simulation_int();
        cyclesCPU = getTiming_Cyc();
		ts[1] = HAL_GetTick();
		printf("Inference time NPU: %lu ms\n\r", ts[1] - ts[0]);
		printf("Inference cycles CPU: %lu cycles\n\r", cyclesCPU);

        BSP_LED_Toggle(LED_BLUE);
        HAL_Delay(1000);
    }
}

static void NeuralNetwork_init(uint32_t *nnin_length, int8_t *nn_out[], int *number_output, int32_t nn_out_len[])
{
    const LL_Buffer_InfoTypeDef *nn_in_info = LL_ATON_Input_Buffers_Info_Default();
    const LL_Buffer_InfoTypeDef *nn_out_info = LL_ATON_Output_Buffers_Info_Default();

    nn_in = (int8_t *) LL_Buffer_addr_start(&nn_in_info[0]);

    while (nn_out_info[*number_output].name != NULL)
    {
        (*number_output)++;
    }

    for (int i = 0; i < *number_output; i++)
    {
        nn_out[i] = (int8_t *) LL_Buffer_addr_start(&nn_out_info[i]);
        nn_out_len[i] = LL_Buffer_len(&nn_out_info[i]);
    }

    *nnin_length = LL_Buffer_len(&nn_in_info[0]);
}


// Calculate network on CPU
//void nn_simulation() {
//    float32_t input[10] = {1,2,3,4,5,6,7,8,9,10};
//    float32_t output[10];
//
//    for (int i = 0; i < 10; i++) {
//        float32_t sum = 0.0f;
//        for (int j = 0; j < 10; j++) {
//            sum += dense_weights[i][j] * input[j];
//        }
//        output[i] = sum;
//    }
//
//    printf("Output (pure float model):\n\r");
//    for (int i = 0; i < 10; i++) {
//        printf("%10.6f\n\r", output[i]);
//    }
//}

// Calculate network on CPU (int8 simulation)
void nn_simulation_int() {
    int8_t input[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int32_t acc[SIZE] = {0};

    // Matrix-vector multiplication
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            acc[i] += dense_weights[i][j] * input[j];
        }
    }

//    // Define quantization parameters (you must know these!)
//    float input_scale = 0.003917837f;    // Example: from your model
//    float weight_scale = 0.027f;         // Replace with real scale
//    float output_scale = 0.010583024f;   // From your model
//    float effective_scale = (input_scale * weight_scale) / output_scale;

    // Dequantize output
    printf("Output (quantized int8 model simulated):\n\r");
    for (int i = 0; i < SIZE; i++) {
//        float val = acc[i] * effective_scale;
    	int32_t val = acc[i];
        printf("%10.6f\n\r", val);
    }
}

void update_dense_weights(const float *new_weights) {
    float *weights = (float *)0x70380000;  // as per network.c
    memcpy(weights, new_weights, NUM_WEIGHTS * sizeof(float));
    //    SCB_CleanDCache_by_Addr(weights, NUM_WEIGHTS * sizeof(float));
    // 	  Align address and size for cache maintenance
	uintptr_t addr = (uintptr_t)weights;
	uintptr_t end = addr + NUM_WEIGHTS * sizeof(float);
	addr &= ~(uintptr_t)(0x1F);  // align down to 32-byte boundary
	end = (end + 31U) & ~(uintptr_t)(0x1F);  // align up to next 32B boundary
	SCB_CleanDCache_by_Addr((void*)addr, end - addr);
}

int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&hcom_uart[COM1], (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
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

static void Hardware_init(void)
{
  /* Power on ICACHE */
  MEMSYSCTL->MSCR |= MEMSYSCTL_MSCR_ICACTIVE_Msk;

  /* Set back system and CPU clock source to HSI */
  __HAL_RCC_CPUCLK_CONFIG(RCC_CPUCLKSOURCE_HSI);
  __HAL_RCC_SYSCLK_CONFIG(RCC_SYSCLKSOURCE_HSI);
  __HAL_RCC_USART1_CLK_ENABLE();

  HAL_Init();

  SCB_EnableICache();

#if defined(USE_DCACHE)
  MEMSYSCTL->MSCR |= MEMSYSCTL_MSCR_DCACTIVE_Msk;
  SCB_EnableDCache();
#endif

  SystemClock_Config();

  NPURam_enable();
  Fuse_Programming();
  NPUCache_config();

  BSP_XSPI_NOR_Init_t NOR_Init;
  NOR_Init.InterfaceMode = BSP_XSPI_NOR_OPI_MODE;
  NOR_Init.TransferRate = BSP_XSPI_NOR_DTR_TRANSFER;
  BSP_XSPI_NOR_Init(0, &NOR_Init);
  BSP_XSPI_NOR_EnableMemoryMappedMode(0);

  Security_Config();
  IAC_Config();
  set_clk_sleep_mode();

  /*** Now initialize UART ***/
  COM_InitTypeDef com_config = {
    .BaudRate = 115200,
    .WordLength = UART_WORDLENGTH_8B,
    .StopBits = UART_STOPBITS_1,
    .Parity = UART_PARITY_NONE,
    .HwFlowCtl = UART_HWCONTROL_NONE
  };
  BSP_COM_Init(COM1, &com_config);
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
  HAL_RIF_RIMC_ConfigMasterAttributes(RIF_MASTER_INDEX_OTG1 , &RIMC_master);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_NPU , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_DMA2D , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_CSI    , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_DCMIPP , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_LTDC   , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_LTDCL1 , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_LTDCL2 , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_OTG1HS , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
  HAL_RIF_RISC_SetSlaveSecureAttributes(RIF_RISC_PERIPH_INDEX_SPI5 , RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV);
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
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


/**
  * @brief  DCMIPP Clock Config for DCMIPP.
  * @param  hdcmipp  DCMIPP Handle
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
