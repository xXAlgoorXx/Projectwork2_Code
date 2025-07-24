/**
 ******************************************************************************
 * @file    uvcl.c
 * @author  MDG Application Team
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "uvcl.h"

#include <assert.h>

#include "uvcl_desc.h"
#include "uvcl_internal.h"

#ifdef UVC_LIB_USE_USBX
#include "uvcl_usbx.h"
#endif
#ifdef UVC_LIB_USE_STM32_USBD
#include "uvcl_stm32_usbd.h"
#endif

#ifndef MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef USB_REQ_SET_INTERFACE
#define USB_REQ_SET_INTERFACE 0x0BU
#endif

/* We want to be the owner so we can decide about location of this structure */
#ifdef UVC_LIB_USE_DMA
PCD_HandleTypeDef uvcl_pcd_handle UVCL_UNCACHED UVCL_ALIGN_32;
#else
PCD_HandleTypeDef uvcl_pcd_handle;
#endif

#if defined(UVC_LIB_USE_DMA) && defined(UVC_LIB_USE_STM32_USBD)
static uint8_t packet[UVC_ISO_HS_MPS] UVCL_UNCACHED UVCL_ALIGN_32;
#else
static uint8_t packet[UVC_ISO_HS_MPS];
#endif

static UVCL_Ctx_t ctx;
UVCL_Ctx_t *p_ctx_single;

static int UVCL_FpsOk(UVCL_Ctx_t *p_ctx)
{
  if (p_ctx->conf.is_immediate_mode)
    return 1;

  if (HAL_GetTick() - p_ctx->frame_start >= p_ctx->frame_period_in_ms)
  {
    return 1;
  }

  return 0;
}

static void UVCL_FillSentData(UVCL_Ctx_t *p_ctx, UVCL_OnFlyCtx_t *on_fly_ctx, uint8_t *p_frame, int fsize,
                             int packet_size)
{
  on_fly_ctx->packet_nb = (fsize + packet_size - 1) / (packet_size - 2);
  on_fly_ctx->last_packet_size = fsize % (packet_size - 2);
  if (!on_fly_ctx->last_packet_size)
  {
    on_fly_ctx->packet_nb--;
    on_fly_ctx->last_packet_size = packet_size - 2;
  }
  on_fly_ctx->cursor = p_frame;
  p_ctx->packet[1] ^= 1;

  p_ctx->is_starting = 0;
  p_ctx->frame_start = HAL_GetTick();
}

static UVCL_OnFlyCtx_t *UVCL_StartSelectedRaw(UVCL_Ctx_t *p_ctx, int packet_size)
{
  UVCL_OnFlyCtx_t *on_fly_ctx = &p_ctx->on_fly_storage_ctx;

  on_fly_ctx->frame_index = -1;
  UVCL_FillSentData(p_ctx, on_fly_ctx, p_ctx->p_frame, p_ctx->frame_size, packet_size);

  __DMB();
  p_ctx->p_frame = NULL;

  return on_fly_ctx;
}

static int UVCL_handle_set_itf_setup_request(UVCL_Ctx_t *p_ctx, UVCL_SetupReq_t *req)
{
  uint16_t wIndex = req->wIndex;
  uint16_t wValue = req->wValue;
  int ret;

  /* Only handle control on vs itf */
  if (wIndex != 1)
    return -1;

  switch (wValue) {
  case 0:
    /* set alternate itf to zero => stop streaming */
    ret = req->stop_streaming(req->ctx);
    break;
  case 1:
    /* set alternate itf to one => start streaming */
    ret = req->start_streaming(req->ctx);
    break;
  default:
    assert(0);
    return -1;
  }

  return ret;
}

static int UVCL_handle_std_itf_setup_request(UVCL_Ctx_t *p_ctx, UVCL_SetupReq_t *req)
{
  int ret;

  switch (req->bRequest) {
  case USB_REQ_SET_INTERFACE:
    ret = UVCL_handle_set_itf_setup_request(p_ctx, req);
    break;
  default:
    assert(0);
    return -1;
  }

  return ret;
}

static int UVCL_handle_probe_control_get_request(UVCL_Ctx_t *p_ctx, UVCL_SetupReq_t *req)
{
  p_ctx->UVC_VideoProbeControl.bmHint = 0;
  p_ctx->UVC_VideoProbeControl.dwFrameInterval = UVC_INTERVAL(p_ctx->conf.fps);
  p_ctx->UVC_VideoProbeControl.dwMaxVideoFrameSize = UVCL_ComputedwMaxVideoFrameSize(&p_ctx->conf);
  p_ctx->UVC_VideoProbeControl.dwMaxPayloadTransferSize = req->dwMaxPayloadTransferSize;
  p_ctx->UVC_VideoProbeControl.dwClockFrequency = 48000000;
  /* should not zero but not clear what value is possible for uncompressed format */
  p_ctx->UVC_VideoProbeControl.bPreferedVersion = 0x00U;
  p_ctx->UVC_VideoProbeControl.bMinVersion = 0x00U;
  p_ctx->UVC_VideoProbeControl.bMaxVersion = 0x00U;

  return req->send_data(req->ctx, (uint8_t *)&p_ctx->UVC_VideoProbeControl,
                        MIN(req->wLength, sizeof(p_ctx->UVC_VideoProbeControl)));
}

static int UVCL_handle_probe_control_set_request(UVCL_Ctx_t *p_ctx, UVCL_SetupReq_t *req)
{
  return req->receive_data(req->ctx, (uint8_t *)&p_ctx->UVC_VideoProbeControl,
                           MIN(req->wLength, sizeof(p_ctx->UVC_VideoProbeControl)));
}

static int UVCL_handle_probe_control_request(UVCL_Ctx_t *p_ctx, UVCL_SetupReq_t *req)
{
  int ret;

  switch (req->bRequest) {
  case UVC_GET_DEF:
  case UVC_GET_MIN:
  case UVC_GET_MAX:
  case UVC_GET_CUR:
    ret = UVCL_handle_probe_control_get_request(p_ctx, req);
    break;
  case UVC_SET_CUR:
    ret = UVCL_handle_probe_control_set_request(p_ctx, req);
    break;
  default:
    assert(0);
    return -1;
  }

  return ret;
}

static int UVCL_handle_probe_commit_set_request(UVCL_Ctx_t *p_ctx, UVCL_SetupReq_t *req)
{
  return req->receive_data(req->ctx, (uint8_t *)&p_ctx->UVC_VideoCommitControl,
                           MIN(req->wLength, sizeof(p_ctx->UVC_VideoCommitControl)));
}

static int UVCL_handle_commit_control_request(UVCL_Ctx_t *p_ctx, UVCL_SetupReq_t *req)
{
  int ret;

  switch (req->bRequest) {
  case UVC_SET_CUR:
    ret = UVCL_handle_probe_commit_set_request(p_ctx, req);
    break;
  default:
    assert(0);
    return -1;
  }

  return ret;
}

static int UVCL_handle_class_itf_setup_request(UVCL_Ctx_t *p_ctx, UVCL_SetupReq_t *req)
{
  int itf_nb = req->wIndex;
  int cs = req->wValue >> 8;
  int ret;

  /* no control for vc itf */
  if (!itf_nb)
    return -1;

  switch (cs) {
  case VS_PROBE_CONTROL_CS:
    ret = UVCL_handle_probe_control_request(p_ctx, req);
    break;
  case VS_COMMIT_CONTROL_CS:
    ret = UVCL_handle_commit_control_request(p_ctx, req);
    break;
  default:
    assert(0);
    return -1;
  }

  return ret;
}

static int UVCL_handle_itf_setup_request(UVCL_Ctx_t *p_ctx, UVCL_SetupReq_t *req)
{
  int ret;

  switch (req->bmRequestType & USB_REQ_TYPE_MASK) {
  case USB_REQ_TYPE_STANDARD:
    ret = UVCL_handle_std_itf_setup_request(p_ctx, req);
    break;
  case USB_REQ_TYPE_CLASS:
    ret = UVCL_handle_class_itf_setup_request(p_ctx, req);
    break;
  default:
    assert(0);
    return -1;
  }

  return ret;
}

static int UVCL_usb_init(PCD_HandleTypeDef *pcd_handle, PCD_TypeDef *pcd_instance)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
  int ret;

  /* First be sure HSE is turn on */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if (ret)
    return ret;

  /* configure usb */
  pcd_handle->Instance = pcd_instance;
  pcd_handle->Init.dev_endpoints = 9;
  pcd_handle->Init.speed = PCD_SPEED_HIGH;
#ifdef UVC_LIB_USE_DMA
  pcd_handle->Init.dma_enable = ENABLE;
#else
  pcd_handle->Init.dma_enable = DISABLE;
#endif
  pcd_handle->Init.phy_itface = USB_OTG_HS_EMBEDDED_PHY;
#ifdef UVC_LIB_USE_SOF
  pcd_handle->Init.Sof_enable = ENABLE;
#else
  pcd_handle->Init.Sof_enable = DISABLE;
#endif
  pcd_handle->Init.low_power_enable = DISABLE;
  pcd_handle->Init.lpm_enable = DISABLE;
  pcd_handle->Init.vbus_sensing_enable = DISABLE;
  pcd_handle->Init.use_dedicated_ep1 = DISABLE;
  pcd_handle->Init.use_external_vbus = DISABLE;
  ret = HAL_PCD_Init(pcd_handle);
  if (ret)
    return ret;

  HAL_PCDEx_SetRxFiFo(pcd_handle, 0x80);
  HAL_PCDEx_SetTxFiFo(pcd_handle, 0, 0x10);
  HAL_PCDEx_SetTxFiFo(pcd_handle, 1, 0x300);

  return 0;
}

static int UVCL_cbs_check(UVCL_Callbacks_t *cbs)
{
  if (!cbs)
    return -1;

  if (!cbs->frame_release)
    return -1;

  return 0;
}

static int UVCL_conf_check(UVCL_Conf_t *conf)
{
  if (!conf)
    return -1;

  if (conf->payload_type != UVCL_PAYLOAD_UNCOMPRESSED_YUY2 &&
      conf->payload_type != UVCL_PAYLOAD_FB_RGB565 &&
      conf->payload_type != UVCL_PAYLOAD_FB_GREY &&
      conf->payload_type != UVCL_PAYLOAD_JPEG &&
      conf->payload_type != UVCL_PAYLOAD_FB_H264 &&
      conf->payload_type != UVCL_PAYLOAD_FB_BGR3 &&
      conf->payload_type != UVCL_PAYLOAD_FB_JPEG &&
      conf->payload_type != UVCL_PAYLOAD_FB_GREY_D3DFMT_L8
      )
    return -1;

  return 0;
}

static void UVCL_vc_init(UVC_VideoControlTypeDef *vc)
{
  vc->bmHint = 0x0000U;
  vc->bFormatIndex = 0x01U;
  vc->bFrameIndex = 0x01U;
  vc->dwFrameInterval = UVC_INTERVAL(30);
  vc->wKeyFrameRate = 0x0000U;
  vc->wPFrameRate = 0x0000U;
  vc->wCompQuality = 0x0000U;
  vc->wCompWindowSize = 0x0000U;
  vc->wDelay = 0x0000U;
  vc->dwMaxVideoFrameSize = 0x0000U;
  vc->dwMaxPayloadTransferSize = 0x00000000U;
  vc->dwClockFrequency = 0x00000000U;
  vc->bmFramingInfo = 0x00U;
  vc->bPreferedVersion = 0x00U;
  vc->bMinVersion = 0x00U;
  vc->bMaxVersion = 0x00U;
}

static void UVCL_ctx_init(UVCL_Ctx_t *p_ctx, UVCL_Conf_t *conf, UVCL_Callbacks_t *cbs)
{
  p_ctx->conf = *conf;
  p_ctx->cbs = cbs;
  p_ctx->buffer_nb = USBX_BUFFER_NB;
  p_ctx->packet = packet;
  p_ctx->frame_period_in_ms = 1000 / conf->fps;
  UVCL_vc_init(&p_ctx->UVC_VideoCommitControl);
  UVCL_vc_init(&p_ctx->UVC_VideoProbeControl);

  p_ctx_single = p_ctx;
}

/* internal API for common code */
UVCL_OnFlyCtx_t *UVCL_StartNewFrameTransmission(UVCL_Ctx_t *p_ctx, int packet_size)
{
  int is_fps_ok = UVCL_FpsOk(p_ctx);

  if (p_ctx->is_starting == 0 && !is_fps_ok)
    return NULL;

  if (!p_ctx->p_frame)
    return NULL;

  return UVCL_StartSelectedRaw(p_ctx, packet_size);
}

int UVCL_handle_setup_request(UVCL_Ctx_t *p_ctx, UVCL_SetupReq_t *req)
{
  int ret;

  switch (req->bmRequestType & USB_REQ_RECIPIENT_MASK) {
  case USB_REQ_RECIPIENT_INTERFACE:
    ret = UVCL_handle_itf_setup_request(p_ctx, req);
    break;
  default:
    assert(0);
    return -1;
  }

  return ret;
}

void UVCL_UpdateOnFlyCtx(UVCL_Ctx_t *p_ctx, int len)
{
  UVCL_OnFlyCtx_t *on_fly_ctx = p_ctx->on_fly_ctx;

  assert(on_fly_ctx);

  on_fly_ctx->packet_index = (on_fly_ctx->packet_index + 1) % on_fly_ctx->packet_nb;
  on_fly_ctx->cursor += len - 2;
  on_fly_ctx->prev_len = len;

  if (on_fly_ctx->packet_index)
    return ;

  /* Once displayed we can make frame free */
  p_ctx->cbs->frame_release(p_ctx->cbs, on_fly_ctx->p_frame);

  /* We reach last packet */
  p_ctx->on_fly_ctx = NULL;
}

void UVCL_AbortOnFlyCtx(UVCL_Ctx_t *p_ctx)
{
  UVCL_OnFlyCtx_t *on_fly_ctx = p_ctx->on_fly_ctx;

  assert(on_fly_ctx);

  p_ctx->cbs->frame_release(p_ctx->cbs, on_fly_ctx->p_frame);
  p_ctx->on_fly_ctx = NULL;
}

uint32_t UVCL_ComputedwMaxVideoFrameSize(UVCL_Conf_t *conf)
{
  uint32_t res = conf->width * conf->height * 2;

  switch (conf->payload_type) {
  case UVCL_PAYLOAD_FB_GREY:
  case UVCL_PAYLOAD_FB_GREY_D3DFMT_L8:
    res = conf->width * conf->height * 1;
    break;
  case UVCL_PAYLOAD_UNCOMPRESSED_YUY2:
  case UVCL_PAYLOAD_FB_RGB565:
    res = conf->width * conf->height * 2;
    break;
  case UVCL_PAYLOAD_FB_BGR3:
    res = conf->width * conf->height * 3;
    break;
  case UVCL_PAYLOAD_JPEG:
    res = conf->dwMaxVideoFrameSize ?  conf->dwMaxVideoFrameSize : conf->width * conf->height;
    break;
  case UVCL_PAYLOAD_FB_H264:
    res = conf->dwMaxVideoFrameSize ?  conf->dwMaxVideoFrameSize : conf->width * conf->height;
    break;
  case UVCL_PAYLOAD_FB_JPEG:
    res = conf->dwMaxVideoFrameSize ?  conf->dwMaxVideoFrameSize : conf->width * conf->height;
    break;
  default:
    assert(0);
  }

  return res;
}

/* public API */
/* FIXME : handle errors correctly */
int UVCL_Init(PCD_TypeDef *pcd_instance, UVCL_Conf_t *conf, UVCL_Callbacks_t *cbs)
{
  int ret;

  if (p_ctx_single)
    return -1;

  ret = UVCL_cbs_check(cbs);
  if (ret)
    return ret;

  ret = UVCL_conf_check(conf);
  if (ret)
    return ret;

  ret = UVCL_usb_init(&uvcl_pcd_handle, pcd_instance);
  if (ret)
    return ret;

#ifdef UVC_LIB_USE_USBX
  ret = UVCL_usbx_init(&ctx, &uvcl_pcd_handle, pcd_instance, conf);
#endif
#ifdef UVC_LIB_USE_STM32_USBD
  ret = UVCL_stm32_usbd_init(&ctx, &uvcl_pcd_handle, pcd_instance, conf);
#endif
  if (ret)
    return ret;

  UVCL_ctx_init(&ctx, conf, cbs);

  return HAL_PCD_Start(&uvcl_pcd_handle);
}

int UVCL_Deinit()
{
  assert(0);

  //p_ctx = NULL;

  return -1;
}

void UVCL_IRQHandler()
{
#if defined(UVCL_USBD_USE_THREADX) || defined(UVCL_USBD_USE_FREERTOS)
  UVCL_stm32_usbd_IRQHandler();
#elif defined(UVC_LIB_USE_USBX)
  UVCL_stm32_usbx_IRQHandler();
#else
  HAL_PCD_IRQHandler(&uvcl_pcd_handle);
#endif
}

int UVCL_ShowFrame(void *frame, int frame_size)
{
  UVCL_Ctx_t *p_ctx = p_ctx_single;

  if (p_ctx->state != UVCL_STATUS_STREAMING)
    return -1;
  if (p_ctx->p_frame)
    return -1;
  if (!frame)
    return -1;
  if (!frame_size)
    return -1;

  p_ctx->frame_size = frame_size;
  __DMB();
  p_ctx->p_frame = frame;

  return 0;
}
