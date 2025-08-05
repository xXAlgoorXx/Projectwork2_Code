/*
 * tildeFFT.h
 *
 *  Created on: Aug 5, 2025
 *      Author: lukasschoepf
 */
#include "arm_math.h"
#ifndef TILEDFFT_TILEDFFT_H_
#define TILEDFFT_TILEDFFT_H_

void tiledDFT(int8_t* in,int8_t* outReal,int8_t* outImag,size_t N);
void generateDFTMatrices(float* W_real, float* W_imag, size_t N);
void quantizeMatrix(const float* in, int8_t* out, size_t size, float scale);

#endif /* TILEDFFT_TILEDFFT_H_ */
