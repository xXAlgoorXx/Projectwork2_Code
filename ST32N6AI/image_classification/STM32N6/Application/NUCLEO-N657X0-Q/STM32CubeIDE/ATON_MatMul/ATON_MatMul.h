#include "arm_math.h"
#include <stdint.h>
#include "ll_aton_runtime.h"


#define MAX_NUMBER_OUTPUT 1

extern int8_t *nn_in;

typedef struct
{
	int bytes;

	int insize;
	int outsize;

	int weight_start;
	int weight_end;
	int weight_limit;

	int input_start;
	int input_end;
	int input_limit;

	int output_start;
	int output_end;
	int output_limit;
}Matmul_info;

void NeuralNetwork_init(int8_t **nn_in, uint32_t *nnin_length, int8_t *nn_out[], int *number_output, uint32_t nn_out_len[]);
void update_weights_float(float* NNweights, const float *new_weights,size_t Num_weights);
void update_weights_int8(int8_t* NNweights, const int8_t *new_weights,size_t Num_weights);

int8_t* getIdentityWeights_int8(size_t insize,size_t outsize);
float* getIdentityWeights_float(size_t insize, size_t outsize);

void calcAdresses(size_t insize, size_t outsize,size_t bytesOfType,volatile Matmul_info* infoStruct);
int npu_matvec_int8_init(size_t insize,size_t outsize); // initialize NN with correct size
int8_t* npu_matvec_int8_run(int8_t *inVec, size_t insizeVec, size_t outSize, int8_t *inMat); // initialize NN with correct size

int npu_matvec_float_init(size_t insize,size_t outsize); // run NN with correct size
float* npu_matvec_float_run(float *inVec, size_t insizeVec, size_t outSize, float *inMat); // run NN with correct size

int npu_tiledmatvec_int8(int8_t* invec,size_t insize,int8_t* outvec, size_t outsize, int8_t* inMat);
void copy_submatrix(int8_t *dest, int8_t *src,size_t start_row, size_t start_col,size_t src_cols, size_t sub_rows, size_t sub_cols);
void printNPUData(int8_t* invec,size_t insize,int8_t* outvec,size_t outsize,int8_t*wightvec);
