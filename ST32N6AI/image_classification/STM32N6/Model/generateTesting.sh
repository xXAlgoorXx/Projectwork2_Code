

stedgeai generate\
   --model testing/matmulModel_32_int8.tflite\
   --target stm32n6\
   --input-data-type int8\
   --output-data-type int8\
   --st-neural-art default@flagTesting.json\
   -o testing\
   -w testing/ws\
