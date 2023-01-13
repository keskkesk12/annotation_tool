import tensorflow as tf
import pandas as pd
import numpy as np
import cv2
import os
keras = tf.keras
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Flatten
from math import *


def main():
  name = "Image"
  
  # Capture image from webcam
  # camera = cv2.VideoCapture("../testing_data/1.mp4")
  camera = cv2.VideoCapture(0)
  
  # Create named window
  cv2.namedWindow(name)
  
  model = keras.models.load_model("keras_model_small")

  # Constants for visualization
  width = 48
  height = 27
  x = 0
  y = 0
  alpha = .3
  
  while(True):
    # Read image, scale and gray scale
    ret, raw_frame = camera.read()
    
    color_frame = cv2.resize(raw_frame, (width, height))
    frame = cv2.cvtColor(color_frame, cv2.COLOR_BGR2GRAY)
    
    # Convert image to array
    float_frame = np.asarray(frame).astype('float32')
    predict_frame = np.expand_dims(float_frame, axis=0)/255.0
    
    # Predict angle using model
    prediction = model.predict(predict_frame)
    
    frame_height, frame_width, _ = raw_frame.shape
    x_new = int(prediction[0][0] * frame_width/width)
    y_new = int(prediction[0][1] * frame_height/height)
    x = alpha*x_new + (1-alpha) * x
    y = alpha*y_new + (1-alpha) * y

    cv2.circle(raw_frame, (int(x),int(y)), 50, (255, 0, 0), -1)
    
    # Show image
    cv2.imshow(name, raw_frame)

    # End program
    key = cv2.waitKey(10)
    if key == 27:
      break
  
  camera.release()
  cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
