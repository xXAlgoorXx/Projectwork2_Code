/*
 * SIMD_MatMul.h
 *
 *  Created on: Jul 31, 2025
 *      Author: lukasschoepf
 */
#include <stdint.h>
#include <arm_math.h>


#ifndef SIMD_MATMUL_SIMD_MATMUL_H_
#define SIMD_MATMUL_SIMD_MATMUL_H_

void simd_matrix_vector_mul_int8(
    const int8_t* matrix,   // Pointer to MxN matrix
    const int8_t* vector,   // Pointer to vector of size N
    int32_t* result,        // Output vector of size M
    uint32_t M,             // Number of rows (Input Size)
    uint32_t N              // Number of columns (must be multiple of 4)(Output Size)
);

// Helium flag not recognised (-mve)
//void mve_matrix_vector_mul_int8(
//    const int8_t* matrix,   // [outsize][insize]
//    const int8_t* vector,   // [insize]
//    int32_t* result,        // [outsize]
//    uint32_t outsize,
//    uint32_t insize
//);

#endif /* SIMD_MATMUL_SIMD_MATMUL_H_ */
