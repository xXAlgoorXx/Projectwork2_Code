import tensorflow as tf
import tensorflow_datasets as tfds
from keras import layers

# Load MNIST dataset
(ds_train, ds_test), ds_info = tfds.load(
    'mnist',
    split=['train', 'test'],
    shuffle_files=True,
    as_supervised=True,
    with_info=True,
)

# Normalize images: uint8 -> float32 [0, 1]
def normalize_img(image, label):
    return tf.cast(image, tf.float32) / 255.0, label

# Prepare training dataset
ds_train = ds_train.map(normalize_img, num_parallel_calls=tf.data.AUTOTUNE)
ds_train = ds_train.cache()
ds_train = ds_train.shuffle(ds_info.splits['train'].num_examples)
ds_train = ds_train.batch(128)
ds_train = ds_train.prefetch(tf.data.AUTOTUNE)

# Prepare test dataset
ds_test = ds_test.map(normalize_img, num_parallel_calls=tf.data.AUTOTUNE)
ds_test = ds_test.cache()
ds_test = ds_test.batch(128)
ds_test = ds_test.prefetch(tf.data.AUTOTUNE)

# Build a simple CNN model
model = tf.keras.models.Sequential([
    layers.Conv2D(2, input_shape=(28, 28, 1), kernel_size=(3, 3), activation='relu'),
    layers.Flatten(),
    layers.Dense(128, activation='relu'),
    layers.Dense(10)
])

model.compile(
    optimizer=tf.keras.optimizers.Adam(0.001),
    loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
    metrics=[tf.keras.metrics.SparseCategoricalAccuracy()],
)

# Train the model
model.fit(
    ds_train,
    epochs=6,
    validation_data=ds_test,
)

# Define representative dataset generator for quantization
def representative_data_gen():
    for image, _ in ds_train.unbatch().batch(1).take(100):
        yield [image]  # image is already [1, 28, 28, 1]

# Convert to fully quantized INT8 TFLite model
converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.representative_dataset = representative_data_gen
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
converter.inference_input_type = tf.int8
converter.inference_output_type = tf.int8

# Convert the model
tflite_quant_model = converter.convert()

# Save the model
with open("model_int8.tflite", "wb") as f:
    f.write(tflite_quant_model)

print("✅ INT8 quantized TFLite model saved as model_int8.tflite")
