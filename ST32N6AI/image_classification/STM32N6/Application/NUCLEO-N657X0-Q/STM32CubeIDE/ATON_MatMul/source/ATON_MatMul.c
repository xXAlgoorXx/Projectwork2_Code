/*
 * ATON_MatMul.c
 *
 *  Created on: Jul 4, 2025
 *      Author: lukasschoepf
 */

#include "ATON_MatMul.h"
#include "ll_aton_runtime.h"
#include "ll_aton_NN_interface.h"

volatile Matmul_info matmulInfo_int;
volatile Matmul_info matmulInfo_Float;

LL_ATON_DECLARE_NAMED_NN_INSTANCE_AND_INTERFACE(int8); //Initializes NN with name int8
LL_ATON_DECLARE_NAMED_NN_INSTANCE_AND_INTERFACE(Float);//Initializes NN with name Float

void update_weights_float(float* NNweights, const float *new_weights,size_t Num_weights) {
    memcpy(NNweights, new_weights, Num_weights * sizeof(float));
//    printf("Cleaning weights at %p, size %d\n\r", NNweights, Num_weights);
    SCB_CleanDCache_by_Addr(NNweights, Num_weights * sizeof(float));
}

void update_weights_int8(int8_t* NNweights, const int8_t *new_weights,size_t Num_weights) {
    memcpy(NNweights, new_weights, Num_weights * sizeof(int8_t));
//    printf("Cleaning weights at %p, size %d\n\r", NNweights, Num_weights);
	SCB_CleanDCache_by_Addr(NNweights, Num_weights * sizeof(int8_t));
}

void calcAdresses(size_t insize, size_t outsize,size_t bytesOfType,volatile Matmul_info* infoStruct){
	infoStruct->bytes = bytesOfType;
	infoStruct->insize = insize;
	infoStruct->outsize = outsize;

	int inBytes = bytesOfType * insize;
	int outBytes = bytesOfType * outsize;

	infoStruct->weight_start = 0;
	infoStruct->weight_end   = infoStruct->weight_start + inBytes * outBytes;
	infoStruct->weight_limit = infoStruct->weight_end + inBytes;

	infoStruct->input_start = infoStruct->weight_limit ;
	infoStruct->input_end   = infoStruct->input_start + inBytes;
	infoStruct->input_limit = infoStruct->input_end + inBytes;

	infoStruct->output_start = infoStruct->input_limit;
	infoStruct->output_end   = infoStruct->output_start + outBytes;
	infoStruct->output_limit = infoStruct->output_end + outBytes;
}

int npu_matvec_int8_init(size_t insize,size_t outsize){
	extern volatile Matmul_info matmulInfo_int;
	size_t insizeNPU = 0;
	size_t outsizeNPU = 0;

	// Calculate valid insize and outsize. At the moment only 8,16,24 are valid
	if((insize > 24) || (outsize > 24)){
		printf("Insize or Outsize too big. Has to be lower or equal to 24\n\r");
		return -1;
	}

	if((insize < 1) || (outsize < 1)){
		printf("Insize or Outsize too small. Has to be higher or equal to 1\n\r");
		return -1;
	}

	// Set insize to a valid size
	if((insize % 8) != 0){
		insizeNPU = ((insize/8) + 1) * 8;
	}

	else{
		insizeNPU = insize;
	}

	// Set outsize to a valid size
	if((outsize % 8) != 0){
		outsizeNPU = ((outsize/8) + 1) * 8;
	}

	else{
		outsizeNPU = outsize;
	}

	// Calculate Adresses
	calcAdresses(insizeNPU,outsizeNPU,1,&matmulInfo_int);
	return 0;
}

int8_t* npu_matvec_int8_run(int8_t *inVec, size_t insizeVec, size_t outSize, int8_t *inMat){
	//LL_ATON_DECLARE_NAMED_NN_INSTANCE_AND_INTERFACE(int8);
	extern volatile Matmul_info matmulInfo_int;

	// Prepare input buffer: 0x34200000UL is the base address
	memcpy((int8_t*)(0x34200000UL + matmulInfo_int.input_start), inVec, matmulInfo_int.insize);
	SCB_CleanDCache_by_Addr((void*)(0x34200000UL + matmulInfo_int.input_start), insizeVec);

	// Prepare Matrix
	update_weights_int8((int8_t*)(0x34200000UL), inMat, insizeVec * outSize);

	LL_ATON_RT_Main(&NN_Instance_int8);

	return (int8_t*)(0x34200000UL + matmulInfo_int.output_start);
}

int npu_matvec_float_init(size_t insize,size_t outsize){
	extern volatile Matmul_info matmulInfo_Float;
	size_t insizeNPU = insize;
	size_t outsizeNPU = outsize;

	// Calculate Adresses
	calcAdresses(insizeNPU,outsizeNPU,4,&matmulInfo_Float);
	return 0;
}

float* npu_matvec_float_run(float *inVec, size_t insizeVec, size_t outSize, float *inMat){
	//LL_ATON_DECLARE_NAMED_NN_INSTANCE_AND_INTERFACE(int8);
	extern volatile Matmul_info matmulInfo_Float;

	// Prepare input buffer: 0x34200000UL is the base address
	memcpy((float*)(0x34200000UL + matmulInfo_Float.input_start), inVec, matmulInfo_Float.insize);
	SCB_CleanDCache_by_Addr((void*)(0x34200000UL + matmulInfo_Float.input_start), insizeVec);

	// Prepare Matrix
	update_weights_float((float*)(0x34200000UL), inMat, insizeVec * outSize);

	LL_ATON_RT_Main(&NN_Instance_int8);

	return (float*)(matmulInfo_Float.output_start);
}

int8_t* getIdentityWeights_int8(size_t insize, size_t outsize) {
    int8_t* identity = malloc(insize * outsize * sizeof(int8_t));
    if (identity == NULL) {
        return NULL;
    }

    // Initialize to 0
    memset(identity, 0, insize * outsize * sizeof(int8_t));

    // Identity matrix is defined by: out[i] = in[i]
    // So we need to set W[i][i] = 1, which is at index: i * insize + i
    size_t min_dim = (insize < outsize) ? insize : outsize;

    for (size_t i = 0; i < min_dim; i++) {
        identity[i * insize + i] = 1;
    }

    return identity;
}

float* getIdentityWeights_float(size_t insize, size_t outsize) {
    float* identity = malloc(insize * outsize * sizeof(float));
    if (identity == NULL) {
        return NULL;
    }

    // Initialize all elements to 0
    memset(identity, 0, insize * outsize * sizeof(float));

    // Set diagonal to 1
    for (size_t i = 0; i < insize && i < outsize; i++) {
        identity[i * outsize + i] = 1.0f;
    }

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

int npu_tiledmatvec_int8(int8_t* invec, size_t insize, int8_t* outvec, size_t outsize, int8_t* inMat) {
    size_t refSize = 24;

    extern volatile Matmul_info matmulInfo_int;

    // Calculate addresses
    calcAdresses(refSize, refSize, 1, &matmulInfo_int);
    int8_t* outp = (int8_t*)(0x34200000UL + matmulInfo_int.output_start);

    // Initialize output vector to 0
    memset(outvec, 0, outsize * sizeof(int8_t));

    size_t num_tiles_out = (outsize + refSize - 1) / refSize;
    size_t num_tiles_in  = (insize + refSize - 1) / refSize;

    for (size_t i = 0; i < num_tiles_out; i++) {
        int8_t acc[24] = {0};  // Accumulator for output tile

        for (size_t j = 0; j < num_tiles_in; j++) {
            // --- Load vector tile (handle partial tiles safely) ---
            int8_t vecTile[24] = {0};
            size_t vecCopy = (j * refSize + refSize <= insize) ? refSize : (insize - j * refSize);
            memcpy(vecTile, &invec[j * refSize], vecCopy);
            memcpy((int8_t*)(0x34200000UL + matmulInfo_int.input_start), vecTile, refSize);

            // --- Load matrix sub-tile (handle edges) ---
            int8_t matTile[24*24] = {0};
            size_t sub_rows = (i * refSize + refSize <= outsize) ? refSize : (outsize - i * refSize);
            size_t sub_cols = (j * refSize + refSize <= insize) ? refSize : (insize - j * refSize);

            copy_submatrix(
                matTile,             // destination buffer
                inMat,               // source matrix (outsize x insize)
                i * refSize,         // start_row
                j * refSize,         // start_col
                insize,              // full row width
                sub_rows,            // rows in this tile
                sub_cols             // cols in this tile
            );

            memcpy((int8_t*)(0x34200000UL + matmulInfo_int.weight_start), matTile, refSize * refSize);

            // --- Launch NPU ---
            LL_ATON_RT_Main(&NN_Instance_int8);
//            printNPUData(
//            		(int8_t*)(0x34200000UL + matmulInfo_int.input_start),
//					refSize,
//					(int8_t*)(0x34200000UL + matmulInfo_int.output_start),
//					refSize,
//					(int8_t*)(0x34200000UL + matmulInfo_int.weight_start)
//            );
            // --- Accumulate output from this tile ---
            for (size_t k = 0; k < sub_rows; k++) {
                acc[k] += outp[k];
            }
        }

        // --- Write back the accumulated result to outvec ---
        size_t write_count = (i * refSize + refSize <= outsize) ? refSize : (outsize - i * refSize);
        memcpy(&outvec[i * refSize], acc, write_count);
    }

    return 0; // Success
}



void copy_submatrix(int8_t *dest, int8_t *src,
                    size_t start_row, size_t start_col,
                    size_t src_cols, size_t sub_rows, size_t sub_cols) {
    for (size_t i = 0; i < sub_rows; i++) {
        size_t src_index = (start_row + i) * src_cols + start_col;
        size_t dest_index = i * sub_cols;
        memcpy(&dest[dest_index], &src[src_index], sub_cols * sizeof(int8_t));
    }
}

void printNPUData(int8_t* invec,size_t insize,int8_t* outvec,size_t outsize,int8_t*wightvec){
	for(int i = 0; i<insize;i++){
		printf("Input[%2d]:%4d",i,invec[i]);
	}
	printf("\n\r");
	printf("Weights:\n\r");
	for(int i = 0; i<outsize;i++){
		for(int j = 0; j < insize;j++){
			printf("%4d", wightvec[i * insize + j]);
		}
		printf("\n\r");
	}

	for(int i = 0; i<outsize;i++){
			printf("Output[%2d]:%4d",i,outvec[i]);
	}
}

