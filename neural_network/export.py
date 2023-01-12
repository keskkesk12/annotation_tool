import tensorflow as tf
keras = tf.keras
from math import *

header = """#include "ap_int.h"
#include <cstdint>
#include "ap_fixed.h"
#define NN_data float\n"""


def main():
    model = keras.models.load_model("keras_model")

    filename = "weights2.hpp"
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
        file.write('const NN_data layer'+str(w)+'_weights['+str(neurons[w-1]*neurons[w])+'] = ')
        file.write('{')
        for i in range(model.layers[w].weights[0].numpy().shape[1]):
            # file.write('{')
            for j in range(model.layers[w].weights[0].numpy().shape[0]):
                file.write(str(model.layers[w].weights[0].numpy()[j][i]))
                if (j == model.layers[w].weights[0].numpy().shape[0]-1) and (i == model.layers[w].weights[0].numpy().shape[1]-1):
                    continue
                else:
                    file.write(', ')
            # file.write('}')
        file.write('};\n\n')
    file.write('}')
    for i in range(1,len(model.layers)):
        bias = ", ".join(map(lambda e:str(e), model.layers[i].get_weights()[1]))
        file.write(f"NN_data bias_layer{i}[] = {{{bias}}};\n")
    file.close()

if __name__ == "__main__":
    main()