/**
 ******************************************************************************
 * @file    stedgeai_app_main.c
 * @author  MCD/AIS Team
 * @brief   Minimal main template to use the STM AI generated c-model for n6
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019,2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software is licensed under terms that can be found in the LICENSE file in
 * the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include <stdio.h>
#include <string.h>

#include "ll_aton.h"
#include "ll_aton_runtime.h"
#include "ai_platform.h"

LL_ATON_DECLARE_NAMED_NN_INSTANCE_AND_INTERFACE(Default) // Defines NN_Instance_Default and NN_Interface_Default with network.c info

AI_ALIGNED(32)
static ai_u8 activations_1[0];
AI_ALIGNED(32)
static ai_u8 activations_2[0];
AI_ALIGNED(32)
static ai_u8 activations_3[0];
AI_ALIGNED(32)
static ai_u8 activations_4[32];

AI_ALIGNED(32)
static ai_u8 weights_1[0];
AI_ALIGNED(32)
static ai_u8 weights_2[0];
AI_ALIGNED(32)
static ai_u8 weights_3[0];
AI_ALIGNED(32)
static ai_u8 weights_4[162];

/* 
 * Example of system initialization function
 */
void SystemInit(void)
{

}

/* 
 * Example of main application function
 */
int main(int argc, char* argv[])
{
  SystemInit();
  while(1)
  {
    LL_ATON_RT_Main(&NN_Instance_Default);
  }
}
