/**
******************************************************************************
* @file    app_config.h
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

/* ---------------    Generated code    ----------------- */
#ifndef APP_CONFIG
#define APP_CONFIG

#define USE_DCACHE

#include "arm_math.h"

/*Defines: CMW_MIRRORFLIP_NONE; CMW_MIRRORFLIP_FLIP; CMW_MIRRORFLIP_MIRROR; CMW_MIRRORFLIP_FLIP_MIRROR;*/
#define CAMERA_FLIP CMW_MIRRORFLIP_NONE


#define ASPECT_RATIO_CROP       (2)
#define ASPECT_RATIO_FIT        (1)
#define ASPECT_RATIO_FULLSCREEN (3)

#define ASPECT_RATIO_MODE    ASPECT_RATIO_CROP

#define CAPTURE_FORMAT DCMIPP_PIXEL_PACKER_FORMAT_RGB565_1
#define CAPTURE_BPP 2
/* Leave the driver use the default resolution */
#define CAMERA_WIDTH 0
#define CAMERA_HEIGHT 0

#define LCD_FG_WIDTH             800
#define LCD_FG_HEIGHT            480
#define LCD_FG_FRAMEBUFFER_SIZE  (LCD_FG_WIDTH * LCD_FG_HEIGHT * 2)
#define NN_HEIGHT     (128)
#define NN_WIDTH      (128)
#define NN_BPP 3

#define COLOR_BGR (0)
#define COLOR_RGB (1)
#define COLOR_MODE    COLOR_RGB
/* Classes */
/* I/O configuration */
#define NB_CLASSES   (5)
#define CLASSES_TABLE const char* classes_table[NB_CLASSES] = {\
   "daisy" ,   "dandelion" ,   "roses" ,   "sunflowers" ,   "tulips"}\

#define WELCOME_MSG_1     "mobilenet_v2_0.35_128_fft_int8.tflite"
#define WELCOME_MSG_2       "Model Running in STM32 MCU internal memory"

#endif      /* APP_CONFIG */
