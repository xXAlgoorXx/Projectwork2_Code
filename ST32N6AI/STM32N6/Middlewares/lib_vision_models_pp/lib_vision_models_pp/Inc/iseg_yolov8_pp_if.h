/*---------------------------------------------------------------------------------------------
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *--------------------------------------------------------------------------------------------*/

#ifndef __ISEG_YOLOV8_PP_IF_H__
#define __ISEG_YOLOV8_PP_IF_H__


#ifdef __cplusplus
 extern "C" {
#endif


#include "iseg_pp_output_if.h"


/* I/O structures for YoloV8 SEG type */
/* --------------------------------------- */

typedef struct yolov8_seg_pp_in_centroid_int8
{
  int8_t *pRaw_detections;
  int8_t *pRaw_masks;
} yolov8_seg_pp_in_centroid_int8_t;

typedef struct
{
	int8_t x_center;
	int8_t y_center;
	int8_t width;
	int8_t height;
	int8_t conf;
	uint8_t class_index;
	int8_t *pMask; // AI_ISEG_YOLOV8_PP_SEG_MASK_NB application definition
} iseg_postprocess_scratchBuffer_s8_t;


typedef struct yolov8_seg_pp_static_param {
  int32_t  nb_classes;
  int32_t  nb_total_boxes;
  int32_t  max_boxes_limit;
  float32_t conf_threshold;
  float32_t iou_threshold;
  int32_t nb_detect;
  int32_t nb_masks;
  int32_t size_masks;
  int32_t raw_output_zero_point;
  float32_t raw_output_scale;
  int32_t mask_raw_output_zero_point;
  float32_t mask_raw_output_scale;
  float32_t *pMask;
  iseg_postprocess_scratchBuffer_s8_t *pTmpBuff;
} yolov8_seg_pp_static_param_t;


/* Exported functions ------------------------------------------------------- */

/*!
 * @brief Resets object detection YoloV8 post processing
 *
 * @param [IN] Input static parameters
 * @retval Error code
 */
int32_t iseg_yolov8_pp_reset(yolov8_seg_pp_static_param_t *pInput_static_param);


/*!
 * @brief Object detector post processing : includes output detector remapping,
 *        nms and score filtering for YoloV8.
 *
 * @param [IN] Pointer on input data
 *             Pointer on output data
 *             pointer on static parameters
 * @retval Error code
 */
int32_t iseg_yolov8_pp_process(yolov8_seg_pp_in_centroid_int8_t *pInput,
                               iseg_postprocess_out_t *pOutput,
                               yolov8_seg_pp_static_param_t *pInput_static_param);



#ifdef __cplusplus
  }
#endif

#endif      /* __ISEG_YOLOV8_PP_IF_H__  */


