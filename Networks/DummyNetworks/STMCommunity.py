import tensorflow as tf
import numpy as np

# Define the model
hidden_states = tf.keras.layers.Input(shape=(1,384), dtype=tf.float32)
output_embeddings = tf.keras.layers.Input(shape=(384, 400), dtype=tf.float32)
result = tf.keras.layers.Lambda(lambda x: tf.matmul(x[0], x[1]))([hidden_states, output_embeddings])
matmul_model = tf.keras.Model(inputs=[hidden_states, output_embeddings], outputs=result)

def representative_data_gen():
    for _ in range(10):  # 10 samples for calibration
        hidden_states = np.random.normal(size=(1, 384)).astype(np.float32)
        output_embeddings = np.random.normal(size=(384, 400)).astype(np.float32)
        yield [hidden_states, output_embeddings]

# Function to convert and quantize models to .tflite
def convert_and_quantize_to_tflite(model, output_tflite_path, representative_data_gen):
    converter = tf.lite.TFLiteConverter.from_keras_model(model)

    # Enable post-training quantization
    converter.optimizations = [tf.lite.Optimize.DEFAULT]

    # Provide the representative dataset for proper scaling
    converter.representative_dataset = representative_data_gen

    # Ensure we use 8-bit asymmetric quantization
    converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]

    # Keep input and output in float32 for compatibility
    converter.inference_input_type = tf.int8
    converter.inference_output_type = tf.int8

    # Convert and save the TFLite model
    tflite_model = converter.convert()
    with open(output_tflite_path, "wb") as f:
        f.write(tflite_model)
    
    print(f"{output_tflite_path} saved successfully.")

# Convert the model with quantization
convert_and_quantize_to_tflite(matmul_model, "matmul_int8.tflite", representative_data_gen)
