import tensorflow as tf
print("TensorFlow version:", tf.__version__)
import keras
from keras import layers
from keras import Model
import numpy as np

class MyModel(Model):
    def __init__(self):
        super().__init__()
        self.d1 = layers.Dense(10, activation=None)

    def call(self, x):
        return self.d1(x)
    
# Create an instance of the model
model = MyModel()
# Build the model with an input shape
model.build(input_shape=(None, 10))  # Replace 10 with the actual input feature size

loss_object = keras.losses.SparseCategoricalCrossentropy(from_logits=True)

optimizer = keras.optimizers.Adam()

train_loss = keras.metrics.Mean(name='train_loss')
train_accuracy = keras.metrics.SparseCategoricalAccuracy(name='train_accuracy')

test_loss = keras.metrics.Mean(name='test_loss')
test_accuracy = keras.metrics.SparseCategoricalAccuracy(name='test_accuracy')

@tf.function
def train_step(images, labels):
    with tf.GradientTape() as tape:
        # training=True is only needed if there are layers with different
        # behavior during training versus inference (e.g. Dropout).
        predictions = model(images, training=True)
        loss = loss_object(labels, predictions)
    gradients = tape.gradient(loss, model.trainable_variables)
    optimizer.apply_gradients(zip(gradients, model.trainable_variables))

    train_loss(loss)
    train_accuracy(labels, predictions)

@tf.function
def test_step(images, labels):
    # training=False is only needed if there are layers with different
    # behavior during training versus inference (e.g. Dropout).
    predictions = model(images, training=False)
    t_loss = loss_object(labels, predictions)

    test_loss(t_loss)
    test_accuracy(labels, predictions)

# Convert the model with int8 quantization
converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.target_spec.supported_types = [tf.int8]
converter.inference_input_type = tf.int8  # Set input type to int8
converter.inference_output_type = tf.int8  # Set output type to int8

def representative_dataset():
    for _ in range(100):
        data = np.linspace(1, 10, 10).astype(np.float32).reshape(1, 10)
        yield [data]


converter.representative_dataset = representative_dataset

tflite_model = converter.convert()

# Save the model
name = "simpleDense_int8.tflite"
with open(name, 'wb') as f:
    f.write(tflite_model)
print("Model converted and saved as", name)

# ===== Test ======

# Load the TFLite model and allocate tensors.
interpreter = tf.lite.Interpreter(model_path=name)
interpreter.allocate_tensors()

# Get input and output tensor details
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# Define your specific test input
input_data = np.array([[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]], dtype=np.float32)

# Get original Keras model output
keras_output = model(input_data, training=False).numpy()

# Quantize the input_data to int8 using input quantization params
input_scale, input_zero_point = input_details[0]['quantization']
input_data_int8 = np.round(input_data / input_scale + input_zero_point).astype(np.int8)

# Set the tensor to the quantized input data
interpreter.set_tensor(input_details[0]['index'], input_data_int8)

# Run inference
interpreter.invoke()

# Get quantized output and dequantize it
output_data_int8 = interpreter.get_tensor(output_details[0]['index'])
output_scale, output_zero_point = output_details[0]['quantization']
output_data = (output_data_int8.astype(np.float32) - output_zero_point) * output_scale

# Print results
print("Input (float32):", input_data)
print("Keras model output:", keras_output)
print("TFLite model output (dequantized):", output_data)



weights = np.array([
    [123, 96, 80, -91, 127, -68, -55, 37, -118, -118],
    [-80, -120, -108, 82, 126, 85, 33, -9, 92, -127],
    [82, -11, 46, 127, -81, -86, -103, 13, -91, -50],
    [-67, -104, -5, 116, -127, 29, -81, -123, 121, -9],
    [-60, 104, 78, -112, -127, 107, 77, 6, -111, 9],
    [117, -49, -32, -127, 83, -125, 75, -53, 99, -91],
    [-66, -57, -80, 127, 97, -123, -57, 122, 81, -89],
    [-125, -33, 120, 99, 83, -107, 43, -11, -2, -127],
    [3, 62, -84, -98, 24, 7, -13, -127, 96, 16],
    [-127, -107, 21, 7, 73, -18, -50, 90, 106, -50]
])
data = np.linspace(1, 10, 10).astype(np.float32).reshape(1, 10)
print(f"Data: {data}")
# Matrix multiplication: (1, 10) @ (10, 10) -> (1, 10)
testoutput = np.matmul(data, weights)
print(testoutput)
