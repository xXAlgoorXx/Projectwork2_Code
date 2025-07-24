/**
  ******************************************************************************
  * @file    two_inputs_matmul.h
  * @author  STEdgeAI
  * @date    2025-05-30 13:47:33
  * @brief   Minimal description of the generated c-implemention of the network
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */
#ifndef LL_ATON_TWO_INPUTS_MATMUL_H
#define LL_ATON_TWO_INPUTS_MATMUL_H

/******************************************************************************/
#define LL_ATON_TWO_INPUTS_MATMUL_C_MODEL_NAME        "two_inputs_matmul"
#define LL_ATON_TWO_INPUTS_MATMUL_ORIGIN_MODEL_NAME   "matmul_two_inputs_model"

/************************** USER ALLOCATED IOs ********************************/
// No user allocated inputs
// No user allocated outputs

/************************** INPUTS ********************************************/
#define LL_ATON_TWO_INPUTS_MATMUL_IN_NUM        (2)    // Total number of input buffers
// Input buffer 1 -- Input_1_out_0
#define LL_ATON_TWO_INPUTS_MATMUL_IN_1_ALIGNMENT   (32)
#define LL_ATON_TWO_INPUTS_MATMUL_IN_1_SIZE_BYTES  (48)
// Input buffer 2 -- Input_0_out_0
#define LL_ATON_TWO_INPUTS_MATMUL_IN_2_ALIGNMENT   (32)
#define LL_ATON_TWO_INPUTS_MATMUL_IN_2_SIZE_BYTES  (32)

/************************** OUTPUTS *******************************************/
#define LL_ATON_TWO_INPUTS_MATMUL_OUT_NUM        (1)    // Total number of output buffers
// Output buffer 1 -- Gemm_2_out_0
#define LL_ATON_TWO_INPUTS_MATMUL_OUT_1_ALIGNMENT   (32)
#define LL_ATON_TWO_INPUTS_MATMUL_OUT_1_SIZE_BYTES  (24)

#endif /* LL_ATON_TWO_INPUTS_MATMUL_H */
