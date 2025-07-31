/*
 * SIMD_MatMul.c
 *
 *  Created on: Jul 31, 2025
 *      Author: lukasschoepf
 */

#include "SIMD_MatMul.h"
#include <stdint.h>
#include <arm_math.h>
#include <arm_mve.h>

// Helium flag not recognised (-mve)

//void mve_matrix_vector_mul_int8(
//    const int8_t* matrix,   // [outsize][insize]
//    const int8_t* vector,   // [insize]
//    int32_t* result,        // [outsize]
//    uint32_t outsize,
//    uint32_t insize
//) {
//    for (uint32_t row = 0; row < outsize; row++) {
//        const int8_t* mat_row = &matrix[row * insize];
//        int32x4_t acc = vdupq_n_s32(0);
//
//        uint32_t i = 0;
//        for (; i + 15 < insize; i += 16) {
//            int8x16_t vec_chunk = vld1q_s8(&vector[i]);
//            int8x16_t mat_chunk = vld1q_s8(&mat_row[i]);
//
//            acc = vdotq_s32(acc, mat_chunk, vec_chunk);
////            acc = veorq_s32(acc, mat_chunk, vec_chunk);
//
//        }
//
//        // Horizontal add of 4 int32 lanes to scalar result
//        result[row] = vaddvq_s32(acc);
//
//        // Handle tail (less than 16)
//        int32_t tail_acc = 0;
//        for (; i < insize; i++) {
//            tail_acc += (int32_t)mat_row[i] * (int32_t)vector[i];
//        }
//        result[row] += tail_acc;
//    }
//}

void simd_matrix_vector_mul_int8(
    const int8_t* matrix,   // Pointer to MxN matrix
    const int8_t* vector,   // Pointer to vector of size N
    int32_t* result,        // Output vector of size M
    uint32_t M,             // Number of rows
    uint32_t N              // Number of columns (must be multiple of 4)
) {
    for (uint32_t i = 0; i < M; i++) {
        const int8_t* mat_row = &matrix[i * N];
        int32_t acc = 0;

        for (uint32_t j = 0; j < N; j += 4) {
            // Load 4 int8_t matrix elements and widen to int16_t
            int16_t mat16_0 = (int16_t)mat_row[j];
            int16_t mat16_1 = (int16_t)mat_row[j+1];
            int16_t mat16_2 = (int16_t)mat_row[j+2];
            int16_t mat16_3 = (int16_t)mat_row[j+3];

            int16_t vec16_0 = (int16_t)vector[j];
            int16_t vec16_1 = (int16_t)vector[j+1];
            int16_t vec16_2 = (int16_t)vector[j+2];
            int16_t vec16_3 = (int16_t)vector[j+3];

            // Pack two 16-bit values into one 32-bit value (low | high)
            int32_t mat_pack1 = __PKHBT(mat16_0, mat16_1, 16);
            int32_t mat_pack2 = __PKHBT(mat16_2, mat16_3, 16);

            int32_t vec_pack1 = __PKHBT(vec16_0, vec16_1, 16);
            int32_t vec_pack2 = __PKHBT(vec16_2, vec16_3, 16);

            // Multiply-accumulate using SIMD (SMLAD: dual 16-bit signed multiply and accumulate)
            acc = __SMLAD(mat_pack1, vec_pack1, acc);
            acc = __SMLAD(mat_pack2, vec_pack2, acc);
        }

        result[i] = acc;
    }
}
