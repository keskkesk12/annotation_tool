#pragma once
// #include "weights2.hpp"
#include "kernels.hpp"
#define rows 30
#define cols 54
#define n_layer7 32
#define n_layer8 32
#define n_layer9 8
#define n_layer10 2
void mat_mul(NN_data input[], int size_in, const NN_data weights[], int width_w, int height_w, NN_data output[]);
void applySingleKernel(NN_data arr[], NN_data kernel[], int &w, int &h,NN_data out[]);

struct Point{
    float x;
    float y;
};
Point nn(NN_data input_img[]);