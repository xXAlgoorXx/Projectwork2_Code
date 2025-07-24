#include "nn_sim.h"
#include <stdio.h>

// Calculate float network on CPU
void nn_simulation_float(size_t size){
    float32_t input[size];
    float32_t output[size];

    // Initialize input vector (example: 1.0, 2.0, ..., 100.0)
    for (size_t i = 0; i < size; i++) {
        input[i] = (float32_t)(i + 1);
    }

    // Matrix-vector multiplication: output = dense_weights * input
    for (size_t i = 0; i < size; i++) {
        float32_t sum = 0.0f;
        for (size_t j = 0; j < size; j++) {
            sum += dense_weights_float_100[i%size][j%size] * input[j];
        }
        output[i] = sum;
    }
//    // Print output
//    printf("Output (pure float model):\n\r");
//    for (int i = 0; i < size; i++) {
//        printf("%10.6f\n\r", output[i]);
//    }
}

// Calculate int network on CPU
void nn_simulation_int8(size_t size,int8_t input[]){
    int8_t output[size];

    // Matrix-vector multiplication: output = dense_weights * input
    for (size_t i = 0; i < size; i++) {
        int32_t sum = 0;
        for (size_t j = 0; j < size; j++) {
            sum += dense_weights_int8_100[i%size][j%size]* input[j];
        }

        // Saturate to int8_t range
        if (sum > 127) sum = 127;
        if (sum < -128) sum = -128;

        output[i] = (int8_t)sum;
    }
    // Print output
    // printf("Output (int8 model):\n\r");
    // for (int i = 0; i < SIZE; i++) {
    //     printf("%d\n\r", output[i]);
    // }
}


