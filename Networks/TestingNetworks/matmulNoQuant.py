import tensorflow as tf
import numpy as np

# Load your model (Keras, SavedModel, etc.)
model = tf.keras.models.load_model("your_model.h5")

# Define a representative dataset for calibration
def representative_data_gen():
    for _ in range(100):
        # Provide a real input sample here with shape [1, 16]
        yield [np.random.rand(1, 16).astype(np.float32)]

# TFLite converter setup
converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.representative_dataset = representative_data_gen

# Force full int8 quantization
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
converter.inference_input_type = tf.int8
converter.inference_output_type = tf.int8

# Convert the model
tflite_model = converter.convert()

# Save the model
with open("model_int8.tflite", "wb") as f:
    f.write(tflite_model)
