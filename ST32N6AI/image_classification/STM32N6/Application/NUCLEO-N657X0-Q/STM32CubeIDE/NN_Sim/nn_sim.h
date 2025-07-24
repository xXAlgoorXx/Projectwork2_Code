#include <stdint.h>
#include "arm_math.h"


extern int8_t dense_weights_int8_100[100][100];
extern float32_t dense_weights_float_100[100][100];

// Calculate network on CPU
void nn_simulation_float(size_t size);
void nn_simulation_int8(size_t size,int8_t input[]);
