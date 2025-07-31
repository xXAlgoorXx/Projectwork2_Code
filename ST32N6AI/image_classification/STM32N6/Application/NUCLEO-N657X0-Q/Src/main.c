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
#include "stm32_lcd_ex.h"
#include "ll_aton_runtime.h"
#include "app_camerapipeline.h"
#include "main.h"
#include <stdio.h>
#include "app_config.h"

#include "nn_sim.h"
#include "ATON_MatMul.h"

#include "arm_math.h"
#include "dsp/matrix_functions.h"

COM_InitTypeDef BspCOMInit;
static void SystemClock_Config(void);
static void NPURam_enable(void);
static void NPUCache_config(void);

#define MAX_NUMBER_OUTPUT 1

static void Security_Config(void);
static void set_clk_sleep_mode(void);
static void IAC_Config(void);

static void Hardware_init(void);

// Lukas added functions
void Error_Handler(void);
void controllOutput(int8_t* in, int8_t* weights, size_t insize, size_t outsize);
void setOutputZero(int8_t* outp, size_t size);
int main_NPU_test(void);
int main_NPU_int8(void);
int main_NPU_float(void);
int main_ARM_int8(void);
int main_ARM_float(void);
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

int main(void)
{
	main_ARM_int8();

}

int main_NPU_int8(void){
	Hardware_init();
	printf("=== MatMul int8 Main ===\n\r");
	size_t insize = 8;
	size_t outsize = 8;

    int8_t inVec[insize];
    for (int i = 0; i < insize; i++) {
    	inVec[i] = (int8_t)((i) % 256);  // Example input: cycles through -128 to 127
    }
    int8_t* identityWeights = getIdentityWeights_int8(insize,outsize);
    int8_t* outvector;

	npu_matvec_int8_init(insize,outsize);
	while(1){
		outvector = npu_matvec_int8_run(inVec,insize,outsize,identityWeights);
		for(size_t i = 0;i < outsize;i++){
			int8_t output = outvector[i];
			printf("Output %2d: %4d\n\r",i,output);
		}
	}

}


int main_NPU_float(void){
	Hardware_init();
	printf("=== MatMul float Main ===\n\r");
	size_t insize = 8;
	size_t outsize = 8;

    float inVec[insize];
    for (int i = 0; i < insize; i++) {
    	inVec[i] = (int8_t)((i) % 256);  // Example input: cycles through -128 to 127
    }
    float* identityWeights = getIdentityWeights_float(insize,outsize);
    float* outvector;

    npu_matvec_float_init(insize,outsize);
	while(1){
		outvector = npu_matvec_float_run(inVec,insize,outsize,identityWeights);
		for(size_t i = 0;i < outsize;i++){
			float output = outvector[i];
			printf("Output %2d: %4.0f\n\r",i,output);
		}
	}
}

int main_ARM_int8(void) {
    size_t insize = 8;
    size_t outsize = 8;

    q7_t inVec[insize];
    for (int i = 0; i < insize; i++) {
        inVec[i] = (q7_t)((i * 16) % 128);  // Input vector in Q7
    }

    // Identity weight matrix
    q7_t* identityWeights = getIdentityWeights_int8(insize, outsize);
    if (!identityWeights) {
        printf("Memory allocation failed\n");
        return -1;
    }

    q7_t dataOut[outsize];
    q7_t scratch[insize * outsize];

    arm_matrix_instance_q7 in;
    arm_matrix_instance_q7 weight;
    arm_matrix_instance_q7 out;

    in.numCols = insize;
    in.numRows = 1;
    in.pData = inVec;

    weight.numCols = outsize;
    weight.numRows = insize;
    weight.pData = identityWeights;

    out.numCols = outsize;
    out.numRows = 1;
    out.pData = dataOut;


    // Start benchmarking
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    arm_status status = arm_mat_mult_q7(&in, &weight, &out, scratch);

    uint32_t cycles = DWT->CYCCNT;
    float time = ((float)cycles / SystemCoreClock) * 1000.0f;

    if (status == ARM_MATH_SUCCESS) {
        printf("Time CMSIS Q7: %f ms, Cycles: %lu\n", time, cycles);
        for (int i = 0; i < outsize; ++i) {
            printf("Out[%d]: %4d -> %7.4f\n", i, dataOut[i], dataOut[i] / 128.0f);
        }
    } else {
        printf("Matrix multiplication failed!\n");
    }

    free(identityWeights);
    return 0;
}

//int main_ARM_float(void) {
//    size_t insize = 8;
//    size_t outsize = 8;
//
//    float32_t inVec[insize];
//    for (int i = 0; i < insize; i++) {
//        inVec[i] = i * 0.1f;  // Example float input values
//    }
//
//    // Identity weight matrix
//    float32_t* identityWeights = getIdentityWeights_float(insize, outsize);
//    if (!identityWeights) {
//        printf("Memory allocation failed\n");
//        return -1;
//    }
//
//    float32_t dataOut[outsize];
//
//    arm_matrix_instance_f32 in;
//    arm_matrix_instance_f32 weight;
//    arm_matrix_instance_f32 out;
//
//    arm_mat_init_f32(&in, 1, insize, inVec);
//    arm_mat_init_f32(&weight, insize, outsize, identityWeights);
//    arm_mat_init_f32(&out, 1, outsize, dataOut);
//
//    // Start benchmarking
//    DWT->CYCCNT = 0;
//    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
//
//    arm_status status = arm_mat_mult_f32(&in, &weight, &out);
//
//    uint32_t cycles = DWT->CYCCNT;
//    float time = ((float)cycles / SystemCoreClock) * 1000.0f;
//
//    if (status == ARM_MATH_SUCCESS) {
//        printf("Time CMSIS float32: %f ms, Cycles: %lu\n", time, cycles);
//        for (int i = 0; i < outsize; ++i) {
//            printf("Out[%d]: %7.4f\n", i, dataOut[i]);
//        }
//    } else {
//        printf("Matrix multiplication failed!\n");
//    }
//
//    free(identityWeights);
//    return 0;
//}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

int main_NPU_test(void)
{
    uint32_t cyclesInitNPU = 0;

    enableTiming_Cyc();
    BSP_LED_Init(LED_BLUE);
    Hardware_init();
    BSP_LED_On(LED_BLUE);
    printf("\n\r== Begin measurement ==\n\r");

    /*** NN Init ****************************************************************/
    uint32_t nn_in_len = 0;
    int number_output = 0;
    int8_t *nn_out[MAX_NUMBER_OUTPUT];             // int8 output
    uint32_t nn_out_len[MAX_NUMBER_OUTPUT];
    int8_t* nn_in = NULL;

    LL_ATON_DECLARE_NAMED_NN_INSTANCE_AND_INTERFACE(Default);

    startTiming_Cyc();
    NeuralNetwork_init(&nn_in, &nn_in_len, nn_out, &number_output, nn_out_len);
    cyclesInitNPU = getTiming_Cyc();

//    printf("Init cycles NPU: %lu cycles\n\r", cyclesInitNPU);
    printf("Input length: %lu bytes\n\r", nn_in_len);
//    printf("Number of output tensors: %d\n\r", number_output);
    printf("Output length: %lu bytes\n\r", nn_out_len[0]);
    printf("In pointer: %p\n\r",nn_in);
    printf("Out pointer: %p\n\r",nn_out[0]);

    /*** Prepare Input **********************************************************/
    int8_t matrix1[nn_in_len];
    for (int i = 0; i < nn_in_len; i++) {
        matrix1[i] = (int8_t)((i) % 256);  // Example input: cycles through -128 to 127
    }

    int8_t* identityWeights = getIdentityWeights_int8(nn_in_len,nn_out_len[0]);
	if (identityWeights == NULL) {
		// Handle error (e.g., return or log)
		printf("Error in weights Allocation");
	}

	size_t weight_size = nn_in_len * nn_out_len[0];  // Based on weight tensor shape in network.c
	int8_t* nnweights = (int8_t*)(0x34200000UL);
	size_t loopcount = 0;
//	setOutputZero(nn_out[0],nn_out_len[0]);
    while (1)
    {
    	printf("Loop count main:%4d\n\r",loopcount);
        uint32_t ts[2] = { 0 };
        uint32_t cyclesCPU = 0;
        uint32_t cyclesNPU = 0;

        // Prepare input buffer
        memcpy(nn_in, matrix1, nn_in_len);
        SCB_CleanDCache_by_Addr((void*)nn_in, nn_in_len);

        // Print input
		printf("Inputs: %p\n\r",nn_in);
		for (int i = 0; i < nn_in_len; i++) {
		    printf("%4d", nn_in[i]);
		}
		printf("\n\r");

        // Run NPU inference
		SCB_CleanDCache_by_Addr((void*)nnweights, weight_size);
        ts[0] = HAL_GetTick();

        startTiming_Cyc();
        LL_ATON_RT_Main(&NN_Instance_Default);
        cyclesNPU = getTiming_Cyc();
        ts[1] = HAL_GetTick();

        // Print output
        printf("NPU Output: %p\n\r",nn_out[0]);
		for (int i = 0; i < nn_out_len[0]; i++) {
			printf("%4d", nn_out[0][i]);
		}
		printf("\n\r");

		// Print control output for reference
        controllOutput(matrix1, nnweights, nn_in_len,nn_out_len[0]);
        uint32_t time_npu = ts[1] - ts[0];

//        printf("Inference time NPU: %lu ms\n\r", time_npu);
//        printf("Inference cycles NPU: %lu cycles\n\r", cyclesNPU);

        /*** Optional CPU Simulation (reference implementation) ***/
//        ts[0] = HAL_GetTick();
//        startTiming_Cyc();
//        nn_simulation_int8(nn_in_len,matrix1);
//        cyclesCPU = getTiming_Cyc();
//        ts[1] = HAL_GetTick();
//        uint32_t time_cpu = ts[1] - ts[0];

//        printf("Inference time CPU: %lu ms\n\r", time_cpu);
//        printf("Inference cycles CPU: %lu cycles\n\r", cyclesCPU);

        BSP_LED_Toggle(LED_BLUE);
        HAL_Delay(1000);

//        // Print weights
//        printf("Weights:\n\r");
//        for (int i = 0; i < nn_out_len[0]; i++) {
//            for (int j = 0; j < nn_in_len; j++) {
//                printf("%4d ", nnweights[i * nn_in_len + j]);  // Correct indexing
//            }
//            printf("\n\r");
//        }
//    	printf("Weights:\n\r");
//    	for (int i = 0; i < nn_in_len; i++) {
//    	    for (int j = 0; j < nn_out_len[0]; j++) {
//    	    	int pointer = i * nn_out_len[0] + j;
//    			printf("%4d:",pointer);
//    	    	printf("%4d ", nnweights[i * nn_out_len[0] + j]);  // Correct indexing
//    	    }
//    	    printf("\n\r");
//    	}

        // Set weights of NN to identity matrix
		update_weights_int8(nnweights, identityWeights, weight_size);
		loopcount++;
//		setOutputZero(nn_out[0],nn_out_len[0]);

    }
}

void controllOutput(int8_t* in, int8_t* weights, size_t insize, size_t outsize) {
    printf("Controll Output:\n\r ");
    for (size_t i = 0; i < outsize; i++) {  // Iterate over output size
        int32_t acc = 0;
        for (size_t j = 0; j < insize; j++) {  // Iterate over input size
//        	printf("In: %3d, Weight: %3d\n\r",(int32_t)in[j],(int32_t)weights[i * outsize + j]);
            acc += in[j] * weights[i + outsize * j];  // Correct indexing
        }
        printf("%3d ", acc);  // Print the result as a 32-bit integer
    }
    printf("\n\r");
}



void setOutputZero(int8_t* outp, size_t size){
	for(size_t i = 0;i < size;i++){
		outp[i] = 0;
	}
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
void Error_Handler(void) {
    printf("Fatal error occurred!\n\r");
    __disable_irq();
    while (1);
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
