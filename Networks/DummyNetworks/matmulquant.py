import tensorflow as tf
import numpy as np

# 1. Custom layer that multiplies matrices with dynamic second dimension
class MatMulLayer(tf.keras.layers.Layer):
    def call(self, inputs):
        a, b = inputs
        b = tf.transpose(b, perm=[0, 2, 1])  # transpose last two dims of b
        return tf.matmul(a, b)

# 2. Build model with dynamic input shapes (None)
def build_model():
    input_a = tf.keras.Input(shape=(4, 4), name="matrix_a")
    input_b = tf.keras.Input(shape=(4, 4), name="matrix_b_raw")
    output = MatMulLayer()([input_a, input_b])
    return tf.keras.Model(inputs=[input_a, input_b], outputs=output)

model = build_model()
model.summary()

# 3. Save model
tf.saved_model.save(model, "matmul_two_inputs_model_dynamic")

# 4. Representative dataset generator for INT8 quantization
def representative_data_gen():
    for _ in range(100):
        dim = np.random.choice([2, 3])
        a = np.random.uniform(-1, 1, size=(1, 4, 4)).astype(np.float32)
        b = np.random.uniform(-1, 1, size=(1, 4, 4)).astype(np.float32)
        yield [a, b]

# 5. Convert to INT8 quantized TFLite
converter = tf.lite.TFLiteConverter.from_saved_model("matmul_two_inputs_model_dynamic")
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.representative_dataset = representative_data_gen
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
converter.inference_input_type = tf.int8
converter.inference_output_type = tf.int8
tflite_model = converter.convert()

# 6. Save TFLite model
with open("DummyNetworks/output/matmul_two_inputs_model_dynamic_int8.tflite", "wb") as f:
    f.write(tflite_model)

print("✅ Model converted and saved with dynamic shapes.")

# 7. Load interpreter and allocate tensors
interpreter = tf.lite.Interpreter(model_path="DummyNetworks/output/matmul_two_inputs_model_dynamic_int8.tflite")
interpreter.allocate_tensors()
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

print("Interpreter input shapes:")
print("Input 0 shape:", input_details[0]['shape'])
print("Input 1 shape:", input_details[1]['shape'])

# 8. Create input arrays matching exactly the interpreter's expected shapes
input_a_fp32 = np.random.uniform(-1, 1, size=input_details[0]['shape']).astype(np.float32)
input_b_fp32 = np.random.uniform(-1, 1, size=input_details[1]['shape']).astype(np.float32)

# 9. Quantize input data
def quantize(fp32_data, detail):
    scale, zero_point = detail['quantization']
    return np.round(fp32_data / scale + zero_point).astype(np.int8)

qa = quantize(input_a_fp32, input_details[0])
qb = quantize(input_b_fp32, input_details[1])

# 10. Set tensors and invoke interpreter
interpreter.set_tensor(input_details[0]['index'], qa)
interpreter.set_tensor(input_details[1]['index'], qb)
interpreter.invoke()

# 11. Get output and dequantize
output_int8 = interpreter.get_tensor(output_details[0]['index'])
scale, zero_point = output_details[0]['quantization']
output_dequant = (output_int8.astype(np.float32) - zero_point) * scale

# 12. Compute expected output with float inputs (adjust dims accordingly)
expected_output = tf.matmul(
    input_a_fp32[0], tf.transpose(input_b_fp32[0])
)

print("Dequantized output:\n", output_dequant[0])
print("Expected output:\n", expected_output.numpy())
print("✅ Outputs close?", np.allclose(output_dequant[0], expected_output.numpy(), atol=0.1))
