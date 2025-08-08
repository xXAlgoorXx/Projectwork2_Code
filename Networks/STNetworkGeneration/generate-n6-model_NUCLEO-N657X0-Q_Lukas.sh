#!/bin/bash
#float32,int8,unint8

MODEL_DIR="ONNX"
MODEL_NAME="qlinear_matmul.onnx"

stedgeai generate \
  --model "$MODEL_DIR"/"$MODEL_NAME" \
  --target stm32n6 \
  --st-neural-art default@STNetworkGeneration/user_neuralart_RamOnlyNUCLEO_N6.json\
  --input-data-type int8 \
  -w "NetworkFiles/"\
  -o "NetworkFiles/output/" 


# cp st_ai_output/network.c "$MODEL_DIR/NetworkFiles/"
# cp st_ai_output/network_ecblobs.h "$MODEL_DIR/NetworkFiles/"
# cp st_ai_output/network_atonbuf.xSPI2.raw "$MODEL_DIR/NetworkFiles/network_data.xSPI2.bin"

# arm-none-eabi-objcopy \
#   -I binary \
#   "$MODEL_DIR/NetworkFiles/network_data.xSPI2.bin" \
#   --change-addresses 0x70380000 \
#   -O ihex \
#   "$MODEL_DIR/NetworkFiles/network_data.hex"

