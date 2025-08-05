/*
 * tiledFFT.c
 *
 *  Created on: Aug 5, 2025
 *      Author: lukasschoepf
 */
#include <math.h>
#include "tiledFFT.h"
#include "ATON_MatMul.h"

void tiledDFT(int8_t* in,int8_t* outReal,int8_t* outImag,size_t N){
	float W_real[N*N];
	float W_imag[N*N];
	int8_t W_realq[N*N];
	int8_t W_imagq[N*N];
	float quantScale = 16;

	generateDFTMatrices(W_real, W_imag, N);
	quantizeMatrix(W_real, W_realq, N, quantScale);
	quantizeMatrix(W_imag, W_imagq, N, quantScale);
	npu_tiledmatvec_int8(in, N, outReal, N, W_realq);
	npu_tiledmatvec_int8(in, N, outImag, N, W_imagq);
}


// 2 matrices, real and imaginary
void generateDFTMatrices(float* W_real, float* W_imag, size_t N) {
    for (size_t k = 0; k < N; k++) {
        for (size_t n = 0; n < N; n++) {
            float angle = -2.0f * M_PI * k * n / N;
            W_real[k * N + n] = cosf(angle);
            W_imag[k * N + n] = -sinf(angle);
        }
    }
}

void quantizeMatrix(const float* in, int8_t* out, size_t size, float scale) {
    for (size_t i = 0; i < size; i++) {
        float val = in[i] * scale;
        if (val > 127) val = 127;
        if (val < -128) val = -128;
        out[i] = (int8_t)(val);
    }
}
