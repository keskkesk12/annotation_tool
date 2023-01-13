from math import *
import tensorflow as tf
keras = tf.keras


def main():
    model = keras.models.load_model("keras_model_small")
    
    print(model.layers[7].get_weights())


if __name__ == "__main__":
    main()
