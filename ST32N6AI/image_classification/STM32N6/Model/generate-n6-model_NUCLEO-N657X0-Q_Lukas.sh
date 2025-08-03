#!/bin/bash
#float32,int8,unint8

MODEL_DIR=testing #"ownModels/matmulModel_128_64_float"
MODEL_NAME="matmulModel_8_16_int8.tflite"

stedgeai generate \
  --model "$MODEL_DIR"/"$MODEL_NAME" \
  --target stm32n6 \
  --st-neural-art default@user_neuralart_NUCLEO-N657X0-Q.json\
  --input-data-type float32 \
  -w "$MODEL_DIR/NetworkFiles/"\
  -o "$MODEL_DIR/NetworkFiles/output/" 


cp st_ai_output/network.c "$MODEL_DIR/NetworkFiles/"
cp st_ai_output/network_ecblobs.h "$MODEL_DIR/NetworkFiles/"
cp st_ai_output/network_atonbuf.xSPI2.raw "$MODEL_DIR/NetworkFiles/network_data.xSPI2.bin"

arm-none-eabi-objcopy \
  -I binary \
  "$MODEL_DIR/NetworkFiles/network_data.xSPI2.bin" \
  --change-addresses 0x70380000 \
  -O ihex \
  "$MODEL_DIR/NetworkFiles/network_data.hex"

