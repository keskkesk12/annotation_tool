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
  camera = cv2.VideoCapture("../raw_data/aruco_test_3.mp4")
  # camera = cv2.VideoCapture(0)
  
  # Create named window
  cv2.namedWindow(name)
  
  model = keras.models.load_model("keras_model")

  # Constants for visualization
  p0 = (430, 200)
  l1 = 120
  l2 = 120
  
  a1 = 0
  a2 = 0
  
  while(True):
    # Read image, scale and gray scale
    ret, raw_frame = camera.read()
    
    color_frame = cv2.resize(raw_frame, (24, 12))
    frame = cv2.cvtColor(color_frame, cv2.COLOR_BGR2GRAY)
    
    # Convert image to array
    float_frame = np.asarray(frame).astype('float32')
    predict_frame = np.expand_dims(float_frame, axis=0)/255.0
    
    # Predict angle using model
    prediction = model.predict(predict_frame)
    
    # Draw lines from prediction
    canvas = cv2.resize(raw_frame, (640, 480))
    alpha = .5
    
    a1 = ((1-alpha)*prediction[0][0]) + a1*alpha
    a2 = ((1-alpha)*prediction[0][1]) + a2*alpha
    
    # Calculate points
    p1 = (int(cos(a1)*l1 + p0[0]), int(sin(a1)*l1 + p0[1]))
    p2 = (int(cos(a2)*l2 + p1[0]), int(sin(a2)*l2 + p1[1]))

    # Draw lines
    cv2.line(canvas, p0, p1, (255, 0, 0), 3)
    cv2.line(canvas, p1, p2, (0, 0, 255), 3)
    
    # Show image
    cv2.imshow(name, canvas)

    # End program
    key = cv2.waitKey(10)
    if key == 27:
      break
  
  camera.release()
  cv2.destroyAllWindows()

if __name__ == "__main__":
    main()