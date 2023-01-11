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

header = """#include "ap_int.h"
#include <cstdint>
#include "ap_fixed.h\n"""


def main():
    model = keras.models.load_model("keras_model")

    filename = "weights.hpp"
    open(filename,'w').close()
    file = open(filename,'a')
    file.write(header)
    neurons = []
    for i in range(1,len(model.layers)):
        n = len(model.layers[i].get_weights()[0])
        neurons.append(n)
    neurons.append(2)
    for i in range(0,len(neurons)):
        if(i==0):
            file.write("#define n_inputs "+str(neurons[i])+'\n')
        else:
            file.write("#define n_layer"+str(i)+" "+str(neurons[i])+'\n')
    file.write("namespace weights{\n")
         
  	## Retrieve network weights after training. Skip layer 0 (input layer)
    for w in range(1, len(model.layers)):
        print(w)
        file.write('const ap_fixed<32,24> layer'+str(w)+'_weights['+str(neurons[w-1])+']['+str(neurons[w])+'] = ')
        file.write('{')
        for i in range(model.layers[w].weights[0].numpy().shape[0]):
            file.write('{')
            for j in range(model.layers[w].weights[0].numpy().shape[1]):
                file.write(str(model.layers[w].weights[0].numpy()[i][j]))
                if j != model.layers[w].weights[0].numpy().shape[1]-1:
                    file.write(', ')
            file.write('}')
            if i != model.layers[w].weights[0].numpy().shape[0]-1:
                file.write(', \n')
        file.write('};\n\n')
    file.write('}')
    file.close()

if __name__ == "__main__":
    main()