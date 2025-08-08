import tensorflow as tf
import numpy as np

# Dummy input
X = np.random.rand(100, 10, 8).astype(np.float32)
y = np.random.rand(100, 1).astype(np.float32)

# Define model
model = tf.keras.Sequential([
    tf.keras.layers.SimpleRNN(16, input_shape=(10, 8), activation='tanh'),
    tf.keras.layers.Dense(1)
])

model.compile(optimizer='adam', loss='mse')
model.fit(X, y, epochs=5, batch_size=8)

# Convert using a concrete function
# Step 1: Create a tf.function with a fixed input shape
input_spec = tf.TensorSpec([1, 10, 8], tf.float32)
concrete_func = tf.function(model).get_concrete_function(input_spec)

# Step 2: Convert with TFLiteConverter
converter = tf.lite.TFLiteConverter.from_concrete_functions([concrete_func])
tflite_model = converter.convert()

# Step 3: Save to file
with open('rnn_model.tflite', 'wb') as f:
    f.write(tflite_model)

print("✅ TFLite model saved as 'rnn_model.tflite'")