import tensorflow as tf

# 1. Custom layer that multiplies two matrices
class MatMulLayer(tf.keras.layers.Layer):
    def call(self, inputs):
        a, b = inputs
        return tf.matmul(a, b)

# 2. Build the model with two inputs
def build_model():
    input_a = tf.keras.Input(shape=(3, 4), name="matrix_a")
    input_b = tf.keras.Input(shape=(4, 2), name="matrix_b")
    output = MatMulLayer()([input_a, input_b])
    return tf.keras.Model(inputs=[input_a, input_b], outputs=output)

# 3. Build and summarize the model
model = build_model()
model.summary()

# 4. Save using the updated SavedModel API
tf.saved_model.save(model, "matmul_two_inputs_model")

# 5. Convert to TFLite
converter = tf.lite.TFLiteConverter.from_saved_model("matmul_two_inputs_model")
converter.target_spec.supported_ops = [
    tf.lite.OpsSet.TFLITE_BUILTINS,
    tf.lite.OpsSet.SELECT_TF_OPS  # Just in case TF ops are used
]
tflite_model = converter.convert()

# 6. Save the TFLite model
with open("matmul_two_inputs_model.tflite", "wb") as f:
    f.write(tflite_model)

print("✅ Model exported to TFLite without using deprecated functions.")

# 7. Load the TFLite model and run inference
interpreter = tf.lite.Interpreter(model_path="matmul_two_inputs_model.tflite")
interpreter.allocate_tensors()
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()
input_shape_a = input_details[0]['shape']
input_shape_b = input_details[1]['shape']
input_a = tf.random.uniform(input_shape_a, dtype=tf.float32)
input_b = tf.random.uniform(input_shape_b, dtype=tf.float32)
interpreter.set_tensor(input_details[0]['index'], input_a)
interpreter.set_tensor(input_details[1]['index'], input_b)
interpreter.invoke()
output_data = interpreter.get_tensor(output_details[0]['index'])
print("Output shape:", output_data.shape)
print("Output data:", output_data)

# 8. Verify the output
input_a = input_a[-1,:,:]
input_b = input_b[-1,:,:]
expected_output = tf.matmul(input_b, input_a)
print("Expected output shape:", expected_output.shape)
print("Expected output data:", expected_output.numpy())

# 9. Check if the outputs are close
assert tf.reduce_all(tf.abs(output_data - expected_output) < 1e-5), "Outputs are not close!"
print("✅ Outputs are close!")
