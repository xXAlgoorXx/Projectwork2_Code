/*---------------------------------------------------------------------------------------------
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file in
 * the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *--------------------------------------------------------------------------------------------*/

#ifndef __SSEG_DEEPLABV3_PP_IF__
#define __SSEG_DEEPLABV3_PP_IF__


#ifdef __cplusplus
 extern "C" {
#endif

#include "sseg_pp_output_if.h"

typedef enum {
  AI_SSEG_DATA_FLOAT = 1,
  AI_SSEG_DATA_UINT8,
  AI_SSEG_DATA_INT8
} e_sseg_data_type;


typedef struct {
  size_t width;
  size_t height;
  uint32_t nb_classes;
  e_sseg_data_type type;
} sseg_deeplabv3_pp_static_param_t;


typedef struct {
  void *pRawData;
} sseg_deeplabv3_pp_in_t;



int32_t sseg_deeplabv3_pp_reset(sseg_deeplabv3_pp_static_param_t *pInput_static_param);


int32_t sseg_deeplabv3_pp_process(sseg_deeplabv3_pp_in_t *pInput,
                                      sseg_pp_out_t *pOutput,
                                      sseg_deeplabv3_pp_static_param_t *pInput_static_param);

#ifdef __cplusplus
  }
#endif

#endif      /* __OD_CENTERNET_PP_IF_H__  */


