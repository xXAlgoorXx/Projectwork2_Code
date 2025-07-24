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
  {"AXISRAM6", "_mem_pool_AXISRAM6_Default", 0x34350000, 1, 0},
  {"AXISRAM5", "_mem_pool_AXISRAM5_Default", 0x342e0000, 1, 0},
  {"AXISRAM4", "_mem_pool_AXISRAM4_Default", 0x34270000, 1, 0},
  {"AXISRAM3", "_mem_pool_AXISRAM3_Default", 0x34200000, 1, 0},
  {"AXISRAM2", "_mem_pool_AXISRAM2_Default", 0x34100000, 1, 0},
  {"AXISRAM1", "_mem_pool_AXISRAM1_Default", 0x34080000, 1, 0},
  {"AXIFLEXMEM", "_mem_pool_AXIFLEXMEM_Default", 0x34000000, 1, 0},
  {"xSPI1", "_mem_pool_xSPI1_Default", 0x90000000, 1, 0},
  {"xSPI2", "_mem_pool_xSPI2_Default", 0x70380000, 1, 0},
  {"AXISRAM2_AXISRAM3_AXISRAM4_AXISRAM5_AXISRAM6", "_mem_pool_AXISRAM2_AXISRAM3_AXISRAM4_AXISRAM5_AXISRAM6_Default", 0x34100000, 1, 0},
  {NULL, NULL, 0, 0, 0}
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
    /* Unit= 28 [NULL_UNIT 0] */
    /* kind=Identity node=Identity_inserted_id19 */
    /* node=Identity_inserted_id19 satisfies input and output adjacency (DMA->DMA) and can be omitted */

    /* Dma inputs units to cycle: */
    /* Unit= 3 [STREAM_ENG_V2 3] */
    /* Emit conf for STREAM_ENG_V2 node=Identity_inserted_id19 input ports=0 range=1[48,80] */

    static const LL_Streng_TensorInitTypeDef Identity_inserted_id19_dma_init_in_0_2 = {
      /* from memory with batch=1 */
      .dir = 0,
      .raw = 1,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 0,
      .addr_base = {(unsigned char *)(0x342e0000UL) /* Equivalent hex address = 0x342e0000UL */}, /* Gemm_2_gemm_7_0_reshape_x_13_inserted_in19 */
      .offset_start = 48,
      .offset_end = 56,
      .offset_limit = 144,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 8,
      .line_offset = 0,
      .loop_offset = 0,
      .frame_loop_cnt = 0,
      .frame_tot_cnt = 4,
      .nbits_in = 16,
      .nbits_out = 16,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(3, &Identity_inserted_id19_dma_init_in_0_2, 1);


    /* Dma input bandwidth from memory pools: */
    /* npuRAM5 -> 32 */

    /* Dma output units from cycle: */
    /* Unit= 9 [STREAM_ENG_V2 9] */
    /* Emit conf for STREAM_ENG_V2 node=Identity_inserted_id19 output ports=0 range=1[80,112] */

    static const LL_Streng_TensorInitTypeDef Identity_inserted_id19_dma_init_out_0_2 = {
      /* to memory canonical from batch=1 */
      .dir = 1,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 0,
      .addr_base = {(unsigned char *)(0x342e0000UL) /* Equivalent hex address = 0x342e0000UL */}, /* Gemm_2_gemm_7_0_reshape_x_13_inserted_out19 */
      .offset_start = 80,
      .offset_limit = 176,
      .frame_count = 0,
      .fwidth = 2,
      .fheight = 1,
      .batch_depth = 2,
      .batch_offset = 16,
      .frame_offset = 4,
      .line_offset = 0,
      .loop_offset = 32,
      .frame_loop_cnt = 4,
      .frame_tot_cnt = 4,
      .nbits_in = 16,
      .nbits_out = 16,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(9, &Identity_inserted_id19_dma_init_out_0_2, 1);


    /* Dma output bandwidth to memory pools: */
    /* npuRAM5 <- 32 */

    static const LL_Switch_InitTypeDef switch_init_in_2[] = {
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, STRENG, 9, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 3, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Identity_inserted_id19 OUT: in unit=STREAM_ENG_V2 9 in port=0 out unit=STREAM_ENG_V2 3 out port=0 */
    };


    /* epoch=2 */
    LL_Switch_Init(switch_init_in_2, 1);

    static const LL_ATON_EnableUnits_InitTypeDef Enable_epoch_2_all_units[] = {
      { {STRENG, 9} }, /* STREAM_ENG_V2 */
      { {STRENG, 3} }, /* STREAM_ENG_V2 */
    };


    LL_ATON_EnableUnits_Init(Enable_epoch_2_all_units, 2);

  }

  ec_trace_wait_epoch_end(0x200);

  {
    static const LL_Switch_DeinitTypeDef switch_deinit_in_2[] = {
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, STRENG, 9, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 3, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Identity_inserted_id19 OUT: in unit=STREAM_ENG_V2 9 in port=0 out unit=STREAM_ENG_V2 3 out port=0 */
    };


    /* epoch=2 */
    LL_Switch_Deinit(switch_deinit_in_2, 1);

    static const LL_ATON_DisableUnits_InitTypeDef Disable_epoch_2_all_units[] = {
      { {STRENG, 9} }, /* STREAM_ENG_V2 */
      { {STRENG, 3} }, /* STREAM_ENG_V2 */
    };


    LL_ATON_DisableUnits_Init(Disable_epoch_2_all_units, 2);

  }
  ec_trace_end_epoch(2);
  ec_trace_end_blob("_ec_blob_1");
}

void trace_ec__ec_blob_4(void) {
  ec_trace_start_blob("_ec_blob_4");
  ec_trace_start_epoch(4);
  {
    /* Unit= 28 [NULL_UNIT 0] */
    /* kind=Reshape node=Gemm_2_out_0_0_10 */
    /* node=Gemm_2_out_0_0_10 satisfies input and output adjacency (DMA->DMA) and can be omitted */

    /* Dma inputs units to cycle: */
    /* Unit= 3 [STREAM_ENG_V2 3] */
    /* Emit conf for STREAM_ENG_V2 node=Gemm_2_out_0_0_10 input ports=0 range=1[48,72] */

    static const LL_Streng_TensorInitTypeDef Gemm_2_out_0_0_10_dma_init_in_0_4 = {
      /* memory canonical to batch=1 */
      .dir = 0,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 0,
      .addr_base = {(unsigned char *)(0x342e0000UL) /* Equivalent hex address = 0x342e0000UL */}, /* ???_19 */
      .offset_start = 48,
      .offset_limit = 136,
      .frame_count = 0,
      .fwidth = 2,
      .fheight = 1,
      .batch_depth = 2,
      .batch_offset = 12,
      .frame_offset = 4,
      .line_offset = 0,
      .loop_offset = 24,
      .frame_loop_cnt = 3,
      .frame_tot_cnt = 3,
      .nbits_in = 16,
      .nbits_out = 16,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(3, &Gemm_2_out_0_0_10_dma_init_in_0_4, 1);


    /* Dma input bandwidth from memory pools: */
    /* npuRAM5 -> 24 */

    /* Dma output units from cycle: */
    /* Unit= 7 [STREAM_ENG_V2 7] */
    /* Emit conf for STREAM_ENG_V2 node=Gemm_2_out_0_0_10 output ports=0 range=1[80,104] */

    static const LL_Streng_TensorInitTypeDef Gemm_2_out_0_0_10_dma_init_out_0_4 = {
      /* to memory with batch=1 */
      .dir = 1,
      .raw = 1,
      .noblk = 0,
      .align_right = 0,
      .nbits_unsigned = 0,
      .addr_base = {(unsigned char *)(0x342e0000UL) /* Equivalent hex address = 0x342e0000UL */}, /* Gemm_2_out_0_0_10_o */
      .offset_start = 80,
      .offset_end = 104,
      .offset_limit = 168,
      .frame_count = 0,
      .fwidth = 0,
      .fheight = 0,
      .batch_depth = 0,
      .batch_offset = 0,
      .frame_offset = 24,
      .line_offset = 0,
      .loop_offset = 0,
      .frame_loop_cnt = 0,
      .frame_tot_cnt = 1,
      .nbits_in = 16,
      .nbits_out = 16,
    };

    /* Unit=STREAM_ENG_V2 */
    LL_Streng_TensorInit(7, &Gemm_2_out_0_0_10_dma_init_out_0_4, 1);


    /* Dma output bandwidth to memory pools: */
    /* npuRAM5 <- 24 */

    static const LL_Switch_InitTypeDef switch_init_in_4[] = {
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, STRENG, 7, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 3, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_out_0_0_10 OUT: in unit=STREAM_ENG_V2 7 in port=0 out unit=STREAM_ENG_V2 3 out port=0 */
    };


    /* epoch=4 */
    LL_Switch_Init(switch_init_in_4, 1);

    static const LL_ATON_EnableUnits_InitTypeDef Enable_epoch_4_all_units[] = {
      { {STRENG, 7} }, /* STREAM_ENG_V2 */
      { {STRENG, 3} }, /* STREAM_ENG_V2 */
    };


    LL_ATON_EnableUnits_Init(Enable_epoch_4_all_units, 2);

  }

  ec_trace_wait_epoch_end(0x80);

  {
    static const LL_Switch_DeinitTypeDef switch_deinit_in_4[] = {
      { LL_Switch_Init_Dest() = ATONN_DSTPORT(STRSWITCH, 0, STRENG, 7, 0), LL_Switch_Init_Source(0) = ATONN_SRCPORT(STRSWITCH, 0, STRENG, 3, 0), LL_Switch_Init_Context(0) = 1, LL_Switch_Init_Frames(0) = 0, }, /* Gemm_2_out_0_0_10 OUT: in unit=STREAM_ENG_V2 7 in port=0 out unit=STREAM_ENG_V2 3 out port=0 */
    };


    /* epoch=4 */
    LL_Switch_Deinit(switch_deinit_in_4, 1);

    static const LL_ATON_DisableUnits_InitTypeDef Disable_epoch_4_all_units[] = {
      { {STRENG, 7} }, /* STREAM_ENG_V2 */
      { {STRENG, 3} }, /* STREAM_ENG_V2 */
    };


    LL_ATON_DisableUnits_Init(Disable_epoch_4_all_units, 2);

  }
  ec_trace_end_epoch(4);
  ec_trace_start_epoch(5);
  {
  }
  {
  }
  ec_trace_end_epoch(5);
  ec_trace_start_epoch(6);
  {
    /* Dma input bandwidth from memory pools: */
    /* npuRAM5 -> 0 */

  }
  {
  }
  ec_trace_end_epoch(6);
  ec_trace_end_blob("_ec_blob_4");
}


int main () {
  ec_trace_init("network_ecblobs.h", "Default");
  trace_ec__ec_blob_1();
  trace_ec__ec_blob_4();
  ec_trace_all_blobs_done();
}
