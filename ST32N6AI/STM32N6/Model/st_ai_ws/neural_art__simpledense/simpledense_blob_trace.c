#include "ll_aton_NN_interface.h"
#include "ll_aton.h"
#include "ll_aton_ec_trace.h"

#if 0
// Workaround: the tracer does not know the target at this moment
// and cannot call the functions since are used in static code
#define ATON_LIB_PHYSICAL_TO_VIRTUAL_ADDR(address) LL_Address_Physical2Virtual(address)
#define ATON_LIB_VIRTUAL_TO_PHYSICAL_ADDR(address) LL_Address_Virtual2Physical(address)
#else
#define ATON_LIB_PHYSICAL_TO_VIRTUAL_ADDR(address) (address)
#define ATON_LIB_VIRTUAL_TO_PHYSICAL_ADDR(address) (address)
#endif


mpool_reloc_info_t mpool_reloc_info[] = {
  {"AXISRAM6", "_mem_pool_AXISRAM6_simpledense", 0x34350000, 1, 0},
  {"AXISRAM5", "_mem_pool_AXISRAM5_simpledense", 0x342e0000, 1, 0},
  {"AXISRAM4", "_mem_pool_AXISRAM4_simpledense", 0x34270000, 1, 0},
  {"AXISRAM3", "_mem_pool_AXISRAM3_simpledense", 0x34200000, 1, 0},
  {"AXISRAM2", "_mem_pool_AXISRAM2_simpledense", 0x34100000, 1, 0},
  {"AXISRAM1", "_mem_pool_AXISRAM1_simpledense", 0x34080000, 1, 0},
  {"AXIFLEXMEM", "_mem_pool_AXIFLEXMEM_simpledense", 0x34000000, 1, 0},
  {"xSPI1", "_mem_pool_xSPI1_simpledense", 0x90000000, 1, 0},
  {"xSPI2", "_mem_pool_xSPI2_simpledense", 0x70380000, 1, 0},
  {"AXISRAM2_AXISRAM3_AXISRAM4_AXISRAM5_AXISRAM6", "_mem_pool_AXISRAM2_AXISRAM3_AXISRAM4_AXISRAM5_AXISRAM6_simpledense", 0x34100000, 1, 0},
  {NULL, NULL, 0, 0, 0}
};


static const uint64_t __ec_params_memory_pool_base[7] = {
0x37493C183ED646C4ULL,0x45FA3D163A954014ULL,0x000000003ED644BFULL,0x0000000000000000ULL,0x0000000000000000ULL,0x0000000000000000ULL,0x0000000000000000ULL,
};

void trace_ec__ec_blob_1(void) {
  ec_trace_start_blob("_ec_blob_1");
  ec_trace_start_epoch(1);
  {
  }
  {
  }
  ec_trace_end_epoch(1);
  ec_trace_start_epoch(2);
  {
    /* Unit= 18 [ARITH_ACC_V2 0] */
    /* kind=Sub node=Gemm_2_conv_4_suboff_6 */
    static const LL_Arithacc_InitTypeDef Gemm_2_conv_4_suboff_6_init2 = {
      .rounding_x = 0,
      .saturation_x = 0,
      .round_mode_x = 0,
      .inbytes_x = 1,
      .outbytes_x = 1,
      .shift_x = 0,
      .rounding_y = 0,
      .saturation_y = 0,
      .round_mode_y = 0,
      .inbytes_y = 1,
      .outbytes_y = 1,
      .combinebc = 1,
      .clipout = 0,
      .shift_y = 0,
      .rounding_o = 0,
      .saturation_o = 0,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 1,
      .shift_o = 14,
      .scalar = 1,
      .dualinput = 0,
      .operation = ARITH_AFFINE,
      .bcast = ARITH_BCAST_HEIGHT,
      .Ax_shift = 0,
      .By_shift = 0,
      .C_shift = 0,
      .fWidth = 1,
      .fHeight = 1,
      .fChannels = 10,
      .batchDepth = 10,
      .clipmin = 0,
      .clipmax = 0,
      .A_scalar = 16384,
      .B_scalar = 32,
      .C_scalar = (short)0,
      .A_vector = {0},
      .B_vector = {0},
      .C_vector = {0},
      .vec_precision = {8, 8, 8},
    };

    /* Unit=ARITH_ACC_V2 */
    LL_Arithacc_Init(0, &Gemm_2_conv_4_suboff_6_init2);


    /* Unit= 10 [CONV_ACC_V2 0] */
    /* kind=Conv node=Gemm_2_conv_4 */
    static const LL_Convacc_InitTypeDef Gemm_2_conv_4_init2 = {
      .simd = 1,
      .fsub = 0,
      .accumulate = 0,
      .rounding_f = 0,
      .saturation_f = 0,
      .round_mode_f = 0,
      .f_unsigned = 1,
      .k_unsigned = 0,
      .deepmode = 0,
      .dss2mode = 0,
      .kseten = 0,
      .zfbias = 0,
      .inbytes_f = 1,
      .shift_f = 0,
      .shift_a = 1,
      .rounding_o = 1,
      .saturation_o = 1,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 2,
      .shift_o = 1,
      .raw_o = 0,
      .fWidth = 1,
      .fHeight = 1,
      .kernelWidth = 1,
      .kernelHeight = 1,
      .nKernels = 10,
      .batchDepth = 10,
      .hstride = 1,
      .vstride = 1,
      .left_padding = 0,
      .right_padding = 0,
      .top_padding = 0,
      .bot_padding = 0,
      .left_crop = 0,
      .right_crop = 0,
      .top_crop = 0,
      .bot_crop = 0,
    };

    /* Unit=CONV_ACC_V2 */
    LL_Convacc_Init(0, &Gemm_2_conv_4_init2);


    /* Unit= 19 [ARITH_ACC_V2 1] */
    /* kind=Mul node=Gemm_2_conv_4_mul_scale_9 */
    static const LL_Arithacc_InitTypeDef Gemm_2_conv_4_mul_scale_9_init2 = {
      .rounding_x = 0,
      .saturation_x = 0,
      .round_mode_x = 0,
      .inbytes_x = 2,
      .outbytes_x = 2,
      .shift_x = 0,
      .rounding_y = 0,
      .saturation_y = 0,
      .round_mode_y = 0,
      .inbytes_y = 2,
      .outbytes_y = 2,
      .combinebc = 0,
      .clipout = 0,
      .shift_y = 0,
      .rounding_o = 1,
      .saturation_o = 1,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 2,
      .shift_o = 17,
      .scalar = 0,
      .dualinput = 0,
      .operation = ARITH_AFFINE,
      .bcast = ARITH_BCAST_CHAN,
      .Ax_shift = 0,
      .By_shift = 0,
      .C_shift = 0,
      .fWidth = 1,
      .fHeight = 1,
      .fChannels = 10,
      .batchDepth = 10,
      .clipmin = 0,
      .clipmax = 0,
      .A_scalar = 1,
      .B_scalar = 0,
      .C_scalar = 0,
      .A_vector = {((unsigned char *)((((uintptr_t)(__ec_params_memory_pool_base)) + 0))) /* Equivalent hex offset = 0x0 */},
      .B_vector = {0},
      .C_vector = {0},
      .vec_precision = {16, 16, 16},
    };

    /* Unit=ARITH_ACC_V2 */
    LL_Arithacc_Init(1, &Gemm_2_conv_4_mul_scale_9_init2);


    /* Unit= 20 [ARITH_ACC_V2 2] */
    /* kind=Add node=Gemm_2_conv_4_off_bias_12 */
    static const LL_Arithacc_InitTypeDef Gemm_2_conv_4_off_bias_12_init2 = {
      .rounding_x = 0,
      .saturation_x = 0,
      .round_mode_x = 0,
      .inbytes_x = 2,
      .outbytes_x = 2,
      .shift_x = 0,
      .rounding_y = 0,
      .saturation_y = 0,
      .round_mode_y = 0,
      .inbytes_y = 2,
      .outbytes_y = 2,
      .combinebc = 1,
      .clipout = 0,
      .shift_y = 0,
      .rounding_o = 1,
      .saturation_o = 1,
      .round_mode_o = 1,
      .relu_mode_o = 0,
      .outbytes_o = 1,
      .shift_o = 20,
      .scalar = 1,
      .dualinput = 0,
      .operation = ARITH_AFFINE,
      .bcast = ARITH_BCAST_HEIGHT,
      .Ax_shift = 0,
      .By_shift = 0,
      .C_shift = 0,
      .fWidth = 1,
      .fHeight = 1,
      .fChannels = 10,
      .batchDepth = 10,
      .clipmin = 0,
      .clipmax = 0,
      .A_scalar = 31267,
      .B_scalar = 80,
      .C_scalar = (short)0,
      .A_vector = {0},
      .B_vector = {0},
      .C_vector = {0},
      .vec_precision = {16, 16, 16},
    };

    /* Unit=ARITH_ACC_V2 */
    LL_Arithacc_Init(2, &Gemm_2_conv_4_off_bias_12_init2);


    /* Dma inputs units to cycle: */
    /* Unit= 1 [STREAM_ENG_V2 1] */
    /* Emit conf for STREAM_ENG_V2 node=Gemm_2_conv_4_suboff_6 input ports=0 range=1[0,10] */

    static const LL_Streng_TensorInitTypeDef Gemm_2_conv_4_suboff_6_dma_init_in_0_2 = {
      /* from memory with batch=10 */
      .dir = 0,
      .raw = 1,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 0,
      .addr_base = {(unsigned char *)(0x342e0000UL) /* Equivalent hex address = 0x342e0000UL */}, /* Gemm_2_reshape_x_2 */
      .offset_start = 0,
      .offset_end = 10,
      .offset_limit = 80,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 10,
      .line_offset = 0,
      .loop_offset = 0,
      .frame_loop_cnt = 0,
      .frame_tot_cnt = 1,
      .nbits_in = 8,
      .nbits_out = 8,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(1, &Gemm_2_conv_4_suboff_6_dma_init_in_0_2, 1);

    /* Unit= 9 [STREAM_ENG_V2 9] */
    /* Emit conf for STREAM_ENG_V2 node=Gemm_2_conv_4 input ports=1 range=8[0,100] */

    static const LL_Streng_TensorInitTypeDef Gemm_2_conv_4_dma_init_in_1_2 = {
      /* 10x1x1x10(8 bits) */
      .dir = 0,
      .raw = 1,
      .continuous = 1,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 0,
      .cacheable = 1,
      .cache_allocate = 0,
      .addr_base = {(unsigned char *)(0x70380000UL) /* Equivalent hex address = 0x70380000UL */}, /* Gemm_2_weights_transposed_3 */
      .offset_start = 0,
      .offset_end = 100,
      .offset_limit = 168,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 0,
      .line_offset = 0,
      .loop_offset = 0,
      .frame_loop_cnt = 0,
      .frame_tot_cnt = 1,
      .nbits_in = 8,
      .nbits_out = 8,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(9, &Gemm_2_conv_4_dma_init_in_1_2, 1);


    /* Dma input bandwidth from memory pools: */
    /* npuRAM5 -> 10 */
    /* octoFlash -> 100 */

    /* Dma output units from cycle: */
    /* Unit= 3 [STREAM_ENG_V2 3] */
    /* Emit conf for STREAM_ENG_V2 node=Gemm_2_conv_4_off_bias_12 output ports=0 range=1[16,26] */

    static const LL_Streng_TensorInitTypeDef Gemm_2_conv_4_off_bias_12_dma_init_out_0_2 = {
      /* to memory with batch=10 */
      .dir = 1,
      .raw = 1,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 0,
      .addr_base = {(unsigned char *)(0x342e0000UL) /* Equivalent hex address = 0x342e0000UL */}, /* Gemm_2_conv_4_off_bias_out_13 */
      .offset_start = 16,
      .offset_end = 26,
      .offset_limit = 96,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 10,
      .line_offset = 0,
      .loop_offset = 0,
      .frame_loop_cnt = 0,
      .frame_tot_cnt = 1,
      .nbits_in = 8,
      .nbits_out = 8,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(3, &Gemm_2_conv_4_off_bias_12_dma_init_out_0_2, 1);


    /* Dma output bandwidth to memory pools: */
    /* npuRAM5 <- 10 */

    static const LL_Switch_InitTypeDef switch_init_in_2[] = {
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 1, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4_suboff_6 IN: in unit=ARITH_ACC_V2 0 in port=0 out unit=STREAM_ENG_V2 1 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 1, LL_Switch_Init_Source(1) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Context(1) = 0, LL_Switch_Init_Frames(1) = 255, }, /* Gemm_2_conv_4 IN: in unit=CONV_ACC_V2 0 in port=0 out unit=ARITH_ACC_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 0, 1), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 9, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4 IN: in unit=CONV_ACC_V2 0 in port=1 out unit=STREAM_ENG_V2 9 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 1, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, CONVACC, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4_mul_scale_9 IN: in unit=ARITH_ACC_V2 1 in port=0 out unit=CONV_ACC_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 2, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 1, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4_off_bias_12 IN: in unit=ARITH_ACC_V2 2 in port=0 out unit=ARITH_ACC_V2 1 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, STRENG, 3, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 2, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4_off_bias_12 OUT: in unit=STREAM_ENG_V2 3 in port=0 out unit=ARITH_ACC_V2 2 out port=0 */
    };


    /* epoch=2 */
    LL_Switch_Init(switch_init_in_2, 6);

    static const LL_ATON_EnableUnits_InitTypeDef Enable_epoch_2_all_units[] = {
      { {STRENG, 3} }, /* STREAM_ENG_V2 */
      { {CONVACC, 0} }, /* CONV_ACC_V2 */
      { {ARITH, 0} }, /* ARITH_ACC_V2 */
      { {ARITH, 1} }, /* ARITH_ACC_V2 */
      { {ARITH, 2} }, /* ARITH_ACC_V2 */
      { {STRENG, 1} }, /* STREAM_ENG_V2 */
      { {STRENG, 9} }, /* STREAM_ENG_V2 */
    };


    LL_ATON_EnableUnits_Init(Enable_epoch_2_all_units, 7);

  }

  ec_trace_wait_epoch_end(0x8);

  {
    static const LL_Switch_DeinitTypeDef switch_deinit_in_2[] = {
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 1, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4_suboff_6 IN: in unit=ARITH_ACC_V2 0 in port=0 out unit=STREAM_ENG_V2 1 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 0, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 1, LL_Switch_Init_Source(1) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 0, 0), LL_Switch_Init_Context(1) = 0, LL_Switch_Init_Frames(1) = 255, }, /* Gemm_2_conv_4 IN: in unit=CONV_ACC_V2 0 in port=0 out unit=ARITH_ACC_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, CONVACC, 0, 1), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 9, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4 IN: in unit=CONV_ACC_V2 0 in port=1 out unit=STREAM_ENG_V2 9 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 1, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, CONVACC, 0, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4_mul_scale_9 IN: in unit=ARITH_ACC_V2 1 in port=0 out unit=CONV_ACC_V2 0 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, ARITH, 2, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 1, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4_off_bias_12 IN: in unit=ARITH_ACC_V2 2 in port=0 out unit=ARITH_ACC_V2 1 out port=0 */
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, STRENG, 3, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, ARITH, 2, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_conv_4_off_bias_12 OUT: in unit=STREAM_ENG_V2 3 in port=0 out unit=ARITH_ACC_V2 2 out port=0 */
    };


    /* epoch=2 */
    LL_Switch_Deinit(switch_deinit_in_2, 6);

    static const LL_ATON_DisableUnits_InitTypeDef Disable_epoch_2_all_units[] = {
      { {STRENG, 3} }, /* STREAM_ENG_V2 */
      { {CONVACC, 0} }, /* CONV_ACC_V2 */
      { {ARITH, 0} }, /* ARITH_ACC_V2 */
      { {ARITH, 1} }, /* ARITH_ACC_V2 */
      { {ARITH, 2} }, /* ARITH_ACC_V2 */
      { {STRENG, 1} }, /* STREAM_ENG_V2 */
      { {STRENG, 9} }, /* STREAM_ENG_V2 */
    };


    LL_ATON_DisableUnits_Init(Disable_epoch_2_all_units, 7);

  }
  ec_trace_end_epoch(2);
  ec_trace_start_epoch(3);
  {
    /* Dma input bandwidth from memory pools: */
    /* npuRAM5 -> 0 */

  }
  {
  }
  ec_trace_end_epoch(3);
  ec_trace_end_blob("_ec_blob_1");
}


int main () {
  ec_trace_init("simpledense_ecblobs.h", "simpledense");
  trace_ec__ec_blob_1();
  ec_trace_all_blobs_done();
}
