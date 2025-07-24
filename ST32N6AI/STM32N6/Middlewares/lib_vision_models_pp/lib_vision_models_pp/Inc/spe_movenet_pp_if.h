/*---------------------------------------------------------------------------------------------
#  * Copyright (c) 2023 STMicroelectronics.
#  * All rights reserved.
#  *
#  * This software is licensed under terms that can be found in the LICENSE file in
#  * the root directory of this software component.
#  * If no LICENSE file comes with this software, it is provided AS-IS.
#  *--------------------------------------------------------------------------------------------*/

#ifndef __SPE_MOVENET_PP_IF_H__
#define __SPE_MOVENET_PP_IF_H__


#ifdef __cplusplus
 extern "C" {
#endif

#include "spe_pp_output_if.h"


/* I/O structures for Movenet model type */
/* ------------------------------------- */
typedef struct spe_movenet_pp_in
{
/*	float32_t inBuff[AI_SPE_MOVENET_PP_NB_KEYPOINTS *
                     AI_SPE_MOVENET_PP_HEATMAP_WIDTH *
                     AI_SPE_MOVENET_PP_HEATMAP_HEIGHT];
                     */
	float32_t *inBuff;
} spe_movenet_pp_in_t;



typedef struct spe_movenet_pp_static_param {
#ifdef _OLD_IMPL
  float32_t *pTmpHeatMap;   /* Must be an array of size
                               AI_SPE_MOVENET_PP_HEATMAP_WIDTH * AI_SPE_MOVENET_PP_HEATMAP_HEIGHT */
#endif
  uint32_t  heatmap_width;
  uint32_t  heatmap_height;
  uint32_t  nb_keypoints;
} spe_movenet_pp_static_param_t;



/* Exported functions ------------------------------------------------------- */

/*!
 * @brief Resets Movenet post processing
 *
 * @param [IN] Input static parameters
 * @retval Error code
 */
int32_t spe_movenet_pp_reset(spe_movenet_pp_static_param_t *pInput_static_param);


/*!
 * @brief Movenet post processing
 *
 * @param [IN] Pointer on input data
 *             Pointer on output data
 *             pointer on static parameters
 * @retval Error code
 */
int32_t spe_movenet_pp_process(spe_movenet_pp_in_t *pInput,
                               spe_pp_out_t     *pOutput,
                               spe_movenet_pp_static_param_t *pInput_static_param);


#ifdef __cplusplus
  }
#endif

#endif      /* __SPE_MOVENET_PP_IF_H__  */

