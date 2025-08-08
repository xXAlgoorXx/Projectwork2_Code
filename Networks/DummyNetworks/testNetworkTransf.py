import tensorflow as tf
import numpy as np
from keras import layers
from keras import Model

# Dummy input
X1 = np.random.rand(100, 18, 18, 1).astype(np.float32)  # Add a channel dimension
y = np.random.randint(0, 10, size=(100,)).astype(np.int32)  # Integer labels for classification

ds1 = tf.data.Dataset.from_tensor_slices((X1, y)).shuffle(10000).batch(32)

class MyModel(Model):
    def __init__(self):
        super().__init__()
        self.conv = layers.Conv2D(16, (3, 3), activation='relu')
        self.attention = layers.Attention()
        self.flatten = layers.Flatten()
        self.d1 = layers.Dense(128, activation='relu')
        self.d2 = layers.Dense(10)  # 10 classes for classification

    def call(self, x):
        x = self.conv(x)  # Apply convolution
        query, value = tf.split(x, num_or_size_splits=2, axis=-1)  # Split along the channel axis
        x = self.attention([query, value])
        x = self.flatten(x)
        x = self.d1(x)
        return self.d2(x)

# Create an instance of the model
model = MyModel()

loss_object = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True)
optimizer = tf.keras.optimizers.Adam()

train_loss = tf.keras.metrics.Mean(name='train_loss')
train_accuracy = tf.keras.metrics.SparseCategoricalAccuracy(name='train_accuracy')

@tf.function
def train_step(images, labels):
    with tf.GradientTape() as tape:
        predictions = model(images, training=True)
        loss = loss_object(labels, predictions)
    gradients = tape.gradient(loss, model.trainable_variables)
    optimizer.apply_gradients(zip(gradients, model.trainable_variables))

    train_loss(loss)
    train_accuracy(labels, predictions)

EPOCHS = 5

for epoch in range(EPOCHS):
    train_loss.reset_states()
    train_accuracy.reset_states()

    for images, labels in ds1:
        train_step(images, labels)

    print(
        f'Epoch {epoch + 1}, '
        f'Loss: {train_loss.result():.2f}, '
        f'Accuracy: {train_accuracy.result() * 100:.2f}%'
    )

# Convert using a concrete function
input_spec = tf.TensorSpec([1, 18, 18, 1], tf.float32)  # Match the model's input shape
concrete_func = tf.function(model).get_concrete_function(input_spec)

converter = tf.lite.TFLiteConverter.from_concrete_functions([concrete_func])
tflite_model = converter.convert()

with open('rnn_model.tflite', 'wb') as f:
    f.write(tflite_model)

print("✅ TFLite model saved as 'rnn_model.tflite'")
