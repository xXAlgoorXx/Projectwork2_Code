/*
 * ATON_MatMul.c
 *
 *  Created on: Jul 4, 2025
 *      Author: lukasschoepf
 */
#include "ATON_MatMul.h"
#include "ll_aton_runtime.h"
#include "ll_aton_NN_interface.h"
//#include "Testing.c"
// pregenrated Networks
//#include "network_16.c"
//#include "network_32.c"
//#include "network_64.c"
//#include "network_128.c"
//#include "network_256.c"
//#include "network_512.c"
//#include "network_1024.c"
//
//typedef struct {
//    int size;
//    LL_ATON_NN_Instance_t* instance;
//    const LL_Buffer_InfoTypeDef* (*get_input_info)(void);
//    const LL_Buffer_InfoTypeDef* (*get_output_info)(void);
//} NPU_Network_Config;
//
//static const NPU_Network_Config matvec_models[] = {
//    {16,    &NN_Instance_Size16,    LL_ATON_Input_Buffers_Info_Size16,    LL_ATON_Output_Buffers_Info_Size16},
//    {32,    &NN_Instance_Size32,    LL_ATON_Input_Buffers_Info_Size32,    LL_ATON_Output_Buffers_Info_Size32},
//    {64,    &NN_Instance_Size64,    LL_ATON_Input_Buffers_Info_Size64,    LL_ATON_Output_Buffers_Info_Size64},
//    {128,   &NN_Instance_Size128,   LL_ATON_Input_Buffers_Info_Size128,   LL_ATON_Output_Buffers_Info_Size128},
//    {256,   &NN_Instance_Size256,   LL_ATON_Input_Buffers_Info_Size256,   LL_ATON_Output_Buffers_Info_Size256},
//    {512,   &NN_Instance_Size512,   LL_ATON_Input_Buffers_Info_Size512,   LL_ATON_Output_Buffers_Info_Size512},
//	{1024,  &NN_Instance_Size1024,  LL_ATON_Input_Buffers_Info_Size1024,  LL_ATON_Output_Buffers_Info_Size1024},
//	{0, NULL, NULL, NULL}
//};


void update_weights_float(float* NNweights, const float *new_weights,size_t Num_weights) {
    memcpy(NNweights, new_weights, Num_weights * sizeof(float));
    //    SCB_CleanDCache_by_Addr(weights, NUM_WEIGHTS * sizeof(float));
}

void update_weights_int8(int8_t* NNweights, const int8_t *new_weights,size_t Num_weights) {
    memcpy(NNweights, new_weights, Num_weights * sizeof(int8_t));
    printf("Cleaning weights at %p, size %lu\n\r", NNweights, Num_weights);
	SCB_CleanDCache_by_Addr(NNweights, Num_weights * sizeof(int8_t));
}

//bool npu_matvec_run(int size, const int8_t* input, const int8_t* weights, int8_t* output) {
//    const NPU_Network_Config* config = NULL;
//    for (int i = 0; matvec_models[i].size != 0; i++) {
//        if (matvec_models[i].size == size) {
//            config = &matvec_models[i];
//            break;
//        }
//    }
//    if (!config) return false;
//
//    const LL_Buffer_InfoTypeDef* in_info = config->get_input_info();
//    const LL_Buffer_InfoTypeDef* out_info = config->get_output_info();
//
//    int8_t* nn_input = (int8_t*)LL_Buffer_addr_start(&in_info[0]);
//    int8_t* nn_weights = (int8_t*)LL_Buffer_addr_start(&in_info[1]);
//    int8_t* nn_output = (int8_t*)LL_Buffer_addr_start(&out_info[0]);
//
//    memcpy(nn_input, input, size);
//    memcpy(nn_weights, weights, size * size);
//
//    SCB_CleanDCache_by_Addr(nn_input, size);
//    SCB_CleanDCache_by_Addr(nn_weights, size * size);
//
//    LL_ATON_RT_Main(config->instance);
//
//    SCB_InvalidateDCache_by_Addr(nn_output, size);
//    memcpy(output, nn_output, size);
//    return true;
//}



int8_t* getIdentityWeights_int8(size_t insize, size_t outsize) {
    int8_t* identity = malloc(insize * outsize * sizeof(int8_t));
    if (identity == NULL) {
        return NULL;
    }

    // Initialize the entire matrix to 0
    memset(identity, 0, insize * outsize * sizeof(int8_t));

    // Set 1 on the diagonal
    for (size_t i = 0; i < insize; i++) {
        for (size_t j = 0; j < outsize; j++) {
            if (i == j) {
//            	printf("%4d: 1",i * outsize + j);
                identity[i * outsize + j] = 1;  // Set diagonal to 1
            }
            else{
//            	printf("%4d: 0",i * outsize + j);
                identity[i * outsize + j] = 0;  // Set diagonal to 1
            }
        }
//    printf("\n\r");
    }

//	for (int i = 0; i < nn_in_len; i++) {
//	    for (int j = 0; j < nn_out_len[0]; j++) {
//	    	int pointer = i * nn_out_len[0] + j;
//			printf("%4d:",pointer);
//	        printf("%4d ", identityWeights[i * nn_in_len + j]);  // Correct indexing
//	    }
//	    printf("\n\r");
//	}
//

    return identity;
}

void NeuralNetwork_init(int8_t **nn_in, uint32_t *nnin_length, int8_t *nn_out[], int *number_output, uint32_t nn_out_len[])
{
    const LL_Buffer_InfoTypeDef *nn_in_info = LL_ATON_Input_Buffers_Info_Default(); // INFO
    const LL_Buffer_InfoTypeDef *nn_out_info = LL_ATON_Output_Buffers_Info_Default(); // INFO

    // Get the input buffer address (as int8_t now)
    *nn_in = (int8_t *)LL_Buffer_addr_start(&nn_in_info[0]); // Needed

    /* Count number of outputs */
    *number_output = 0;
    while (nn_out_info[*number_output].name != NULL)
    {
        (*number_output)++;
    }

    assert(*number_output <= MAX_NUMBER_OUTPUT);

    for (int i = 0; i < *number_output; i++)
    {
        // Get the output buffers address as int8_t
        nn_out[i] = (int8_t *) LL_Buffer_addr_start(&nn_out_info[i]);
        nn_out_len[i] = LL_Buffer_len(&nn_out_info[i]);
    }

    *nnin_length = LL_Buffer_len(&nn_in_info[0]);
}


