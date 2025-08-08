import tensorflow as tf

# Size of the input and output dimensions (non-quadratic weight matrix)
input_size = 128  # Input dimension
output_size = 64  # Output dimension

quanttype = tf.float32  # Can be tf.float32, tf.int16, tf.int8

class MatrixMultiplyModel(tf.keras.Model):
    def __init__(self, W):
        super().__init__()
        self.dense = tf.keras.layers.Dense(
            units=W.shape[1],  # Output size should match W's second dimension (number of units)
            use_bias=False,
            dtype='float32'
        )
        self.dense.build((None, W.shape[0]))  # Input size should match W's first dimension (number of input features)
        self.dense.set_weights([W])

    def call(self, x):
        return self.dense(x)

# Create weight matrix W (17x10), matching input and output dimensions
W = tf.random.uniform((input_size, output_size), dtype=tf.float32)  # Now W has shape (17, 10)

# Build model and force tracing
model = MatrixMultiplyModel(W)
_ = model(tf.zeros((1, input_size)))  # Force tracing

# ✅ Save in SavedModel format (for TFLite use)
model.export("TestingNetworks/output/matrix_mul_model")

def representative_data_gen():
    for _ in range(input_size):
        # Generate random input in the same shape and range as training data
        data = tf.random.uniform([1, input_size], minval=-1, maxval=1, dtype=tf.float32)
        yield [data]

# ✅ Convert to .tflite (float model, no quantization)
converter = tf.lite.TFLiteConverter.from_saved_model("TestingNetworks/output/matrix_mul_model")
# converter.optimizations = [tf.lite.Optimize.OPTIMIZE_FOR_SIZE]
# converter.representative_dataset = representative_data_gen
# converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
# converter.experimental_new_converter = True

# converter.target_spec.supported_types = [tf.int8]
# converter.inference_input_type = quanttype  # or tf.uint8
# converter.inference_output_type = quanttype  # or tf.uint8
tflite_model = converter.convert()

quant = "float"
if quanttype == tf.int8:
    quant = "int8"
elif quanttype == tf.int16:
    quant = "int16"

outpath = "TestingNetworks/output/models/Testing"
# Save .tflite to file
with open(f"{outpath}/matmulModel_{input_size}_{output_size}_{quant}.tflite", "wb") as f:
    f.write(tflite_model)

print("Model saved as 'matrix_mul_model_big.tflite'")

interpreter = tf.lite.Interpreter(model_content=tflite_model)
interpreter.allocate_tensors()
for detail in interpreter.get_tensor_details():
    print(detail['dtype'])
for op in interpreter.get_tensor_details():
    print(op['name'], op['dtype'])
for op in interpreter._get_ops_details():
    print(op['op_name'], op['inputs'], op['outputs'])
