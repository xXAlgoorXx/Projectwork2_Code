/**
  ******************************************************************************
  * @file    network_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-05-15T10:21:46+0200
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "network_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_network_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_network_weights_array_u64[18] = {
  0x25c9bc7fa550607bU, 0x557e529488b08a8aU, 0x7f2ef552815cf721U, 0x98bdcea50d99aaafU,
  0xf77985af1d8174fbU, 0x64d6b81904e68c4U, 0x835381e0cf750991U, 0x7fb0c7bea563cb4bU,
  0xdf83a7517ac78561U, 0x81fef52b95536378U, 0x81f307189eac3e03U, 0xee49071595811060U,
  0xce6a5aceU, 0x0U, 0x0U, 0x0U,
  0x0U, 0x0U,
};


ai_handle g_network_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_network_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

