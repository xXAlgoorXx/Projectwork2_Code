#include "arm_math.h"
#include <stdint.h>
#include "ll_aton_runtime.h"


#define MAX_NUMBER_OUTPUT 1

extern int8_t *nn_in;

void ActivationAdr(size_t* internal_lentgh, int8_t* internal_p);
void NeuralNetwork_init(int8_t **nn_in, uint32_t *nnin_length, int8_t *nn_out[], int *number_output, uint32_t nn_out_len[]);
void update_weights_float(float* NNweights, const float *new_weights,size_t Num_weights);
void update_weights_int8(int8_t* NNweights, const int8_t *new_weights,size_t Num_weights);
int8_t* getIdentityWeights_int8(size_t insize,size_t outsize);

void npu_matvec_int8_init(void); // initialize NN with correct size
void npu_matvec_int8_run(void); // initialize NN with correct size
void npu_matvec_float_init(void); // run NN with correct size
void npu_matvec_float_run(void); // run NN with correct size

bool npu_matvec_run(int size, const int8_t* input, const int8_t* weights, int8_t* output);

