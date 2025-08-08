import tensorflow as tf
import numpy as np

# Define model with no bias and no activation
model = tf.keras.Sequential([
    tf.keras.Input(shape=(100,), name="input"),
    tf.keras.layers.Dense(100, use_bias=False, activation=None, name="matmul_only"),
])

model.compile(optimizer='adam', loss='mse')

# Generate dummy training data
x_train = np.random.rand(100, 100).astype(np.float32)
y_train = np.random.rand(100, 100).astype(np.float32)

# Train briefly
model.fit(x_train, y_train, epochs=3)

# Representative dataset generator
def representative_data_gen():
    for i in range(100):
        yield [x_train[i:i+1]]

# Convert to fully INT8 quantized TFLite model
converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.representative_dataset = representative_data_gen
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
converter.inference_input_type = tf.int8
converter.inference_output_type = tf.int8

tflite_model = converter.convert()

# Save the model
with open("TestingNetworks/output/quantized_model_big.tflite", "wb") as f:
    f.write(tflite_model)

print("Model saved as 'quantized_model_big.tflite'")

interpreter = tf.lite.Interpreter(model_content=tflite_model)
interpreter.allocate_tensors()
for detail in interpreter.get_tensor_details():
    print(detail['dtype'])
for op in interpreter.get_tensor_details():
    print(op['name'], op['dtype'])
for op in interpreter._get_ops_details():
    print(op['op_name'], op['inputs'], op['outputs'])


