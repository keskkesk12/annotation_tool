import tensorflow as tf
import pandas as pd
import numpy as np
import cv2
import os
keras = tf.keras
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Flatten
import csv


def readImages(path):
    data = []
    # Read training data
    for filename in sorted(os.listdir(path)):
        img = cv2.imread(os.path.join(path, filename),
                         0)  # read img as grayscale
        data.append(img/255)

    data = np.asarray(data).astype('float32')
    
    return data


def readLabels(file):
    labels = pd.read_csv(file, header=None)
    labels = np.asarray(labels).astype('float32')

    return labels


def main():
    os.environ['CUDA_VISIBLE_DEVICES'] = '-1'
    
    # Read data
    training_data = readImages("../training_data")
    testing_data = readImages("../testing_data")

    # Read labels
    training_labels = readLabels("../labels/training_labels.csv")
    testing_labels = readLabels("../labels/testing_labels.csv")

    # Make model
    model = Sequential([
        Flatten(input_shape=(12, 24)),		# reshape 12x24 to 288, layer 0
        Dense(128, activation='relu', use_bias=True),
        Dense(64, activation='relu', use_bias=True),
        Dense(32, activation='relu', use_bias=True),
        # Dense(16, activation='relu', use_bias=True),
        # Dense(8, activation='relu', use_bias=True),
        Dense(2, activation='linear', use_bias=True),
    ])

    model.compile(optimizer='adam',
                  loss='mean_squared_error',
                  metrics=['accuracy'])

    # Train model
    model.fit(training_data, training_labels, epochs=2500,
              batch_size=64, validation_split=0.2, shuffle=True)
    
    model.summary()

    # Save model
    model.save('keras_model')

    results = model.evaluate(testing_data, testing_labels, verbose=0)
    print("test loss, test acc: ", results)


    # Save predictions to visualization
    predictions = model.predict(testing_data)
    file = open('../viz/output.csv', 'w+', newline='')
    with file:
        write = csv.writer(file)
        write.writerows(predictions)

if __name__ == "__main__":
    main()