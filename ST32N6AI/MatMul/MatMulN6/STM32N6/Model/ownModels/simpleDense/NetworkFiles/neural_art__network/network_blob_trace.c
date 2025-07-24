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
  ec_trace_end_blob("_ec_blob_1");
}

void trace_ec__ec_blob_3(void) {
  ec_trace_start_blob("_ec_blob_3");
  ec_trace_start_epoch(3);
  {
  }
  {
  }
  ec_trace_end_epoch(3);
  ec_trace_start_epoch(4);
  {
    /* Dma input bandwidth from memory pools: */
    /* npuRAM5 -> 0 */

  }
  {
  }
  ec_trace_end_epoch(4);
  ec_trace_end_blob("_ec_blob_3");
}


int main () {
  ec_trace_init("network_ecblobs.h", "Default");
  trace_ec__ec_blob_1();
  trace_ec__ec_blob_3();
  ec_trace_all_blobs_done();
}
