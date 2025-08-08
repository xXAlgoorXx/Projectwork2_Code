import numpy as np
import tensorflow as tf

# Load the TFLite model
interpreter = tf.lite.Interpreter(model_path="TestingNetworks/output/quantized_model.tflite")
interpreter.allocate_tensors()

# Get input/output details
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# Extract input quantization parameters
input_scale, input_zero_point = input_details[0]['quantization']
output_scale, output_zero_point = output_details[0]['quantization']

print(f"Input scale: {input_scale}, zero_point: {input_zero_point}")
print(f"Output scale: {output_scale}, zero_point: {output_zero_point}")

# Prepare input data: float -> quantized int8
input_data_f = np.array([1,2,3,4,5,6,7,8,9,10], dtype=np.float32)
input_data_q = (input_data_f / input_scale + input_zero_point).astype(np.int8)

# Reshape if required (some models expect [1, 10])
input_data_q = np.expand_dims(input_data_q, axis=0)

# Set input tensor
interpreter.set_tensor(input_details[0]['index'], input_data_q)

# Run inference
interpreter.invoke()

# Get raw output (quantized)
output_data_q = interpreter.get_tensor(output_details[0]['index'])[0]

# Dequantize output
output_data_f = (output_data_q.astype(np.float32) - output_zero_point) * output_scale

# Print result
print("\nDequantized model output:")
for i, val in enumerate(output_data_f):
    print(f"  Output[{i}]: {val:.6f}")
