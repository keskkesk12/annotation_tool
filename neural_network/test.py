from math import *
import tensorflow as tf
keras = tf.keras

def transform(e):
    pass

def flatten(l):
    return [item for sublist in l for item in sublist]

def main():
    model = keras.models.load_model("keras_model_small")
    print(model.summary())
    # filename = "kernels.hpp"
    # open(filename,'w').close()
    # file = open(filename,'a')
    # num_cnn = 3
    # shape = [1, 4, 4]
    # for i in range(3):
    #     layer = []
    #     for j in range(shape[i]):
    #         kernels = model.get_weights()[i*2][:,:,j,:].transpose((2,1,0))
            
    #         # if i==0:
    #         #     kernels = list(map(lambda e: [e], kernels))
    #         if shape[i] == 1:
    #             kernels = list(map(lambda e: [flatten(e)], kernels))
    #         elif shape[i] == 4: 
    #             kernels = list(map(lambda e: flatten(e), kernels))
    #         else:
    #             raise "error"
    #         layer.append(kernels)
    #         if shape[i] == 1:
    #             layer = layer[0]
    #         #print(kernels)
    #     layer = str(layer).replace("[", "{").replace("]", "}")
    #     s = f"NN_data layer_{i}[4][{shape[i]}][9] = {layer};\n"
    #     file.write(s)
    # for w in range(7,len(model.layers)):
    #     # print(model.layers[w].get_weights()[0])
    #     file.write('const NN_data layer'+str(w)+'_weights[] = ')
    #     file.write('{')
    #     for i in range(model.layers[w].weights[0].numpy().shape[1]):
    #         # file.write('{')
    #         for j in range(model.layers[w].weights[0].numpy().shape[0]):
    #             file.write(str(model.layers[w].weights[0].numpy()[j][i]))
    #             if (j == model.layers[w].weights[0].numpy().shape[0]-1) and (i == model.layers[w].weights[0].numpy().shape[1]-1):
    #                 continue
    #             else:
    #                 file.write(', ')
    #         # file.write('}')
    #     file.write('};\n\n')
    # file.write('}')
            

            # print("{")
            # for k in range(len(kernels)):
            #     if(j==0):
            #         print("{")
            #     print("{")
            #     for n in range(3):
            #         for m in range(3):
            #             print(kernels[k][n][m])
            #     # print(kernels[k])
            #     print("}")
            #     if j==(shape[i]-1):
            #         print("}")
            # # print(kernels[0])
            # print("}")
            # file.write("{")
            # for l in range(4):
            #     file.write("{")
            #     for n in range(3):
            #         for k in range(3):
            #             file.write(str(kernels[l][n][k]))
            #             if(n == 2) and (k==2):
            #                 continue
            #             else:
            #                 file.write(", ")
            #     file.write("}")
            #     if l <(4-1):
            #         file.write(" \n")
            # if j<(4-1):
            #     file.write(", ")
            # file.write("}")
            # file.write("\n")


    

        # file.write("}\n")
    # print(model.get_weights()[2][:, :, 3, :].transpose((2, 1, 0)))


if __name__ == "__main__":
    main()
