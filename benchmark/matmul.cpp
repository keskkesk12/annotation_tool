#include "matmul.hpp"
#include <iostream>
#include "kernels.hpp"
#include <assert.h>
NN_data getPixelVal(NN_data arr[], int w, int h, int x, int y)
{
    // if (x < 0 || x >= w || y < 0 || y >= h)
    //     return 0;
    return arr[y * w + x];
}

NN_data max(float a, float b, float c, float d)
{
    if (a > b && a > c && a > d)
        return a;

    else if (b > c && b > d)
        return b;

    else if (c > d)
        return c;

    return d;
}

void maxPooling(NN_data arr[], int w, int h, NN_data out[])
{
    int t = 0;
    for (int i = 0; i < h - 1; i += 2)
    {
        for (int j = 0; j < w - 1; j += 2)
        {
            out[t++] = max(getPixelVal(arr, w, h, j, i), getPixelVal(arr, w, h, j, i + 1), getPixelVal(arr, w, h, j + 1, i), getPixelVal(arr, w, h, j + 1, i + 1));
        }
    }
}

void applySingleKernel(NN_data arr[], NN_data kernel[], int w, int h, NN_data out[])
{
    int t = 0;
    NN_data sum;
    for (int i = 1; i < h - 1; i++)
    {
        for (int j = 1; j < w - 1; j++)
        {
            sum = 0;
            for (int m = 0; m < 3; m++)
            {
                for (int n = 0; n < 3; n++)
                {
                    sum += getPixelVal(arr, w, h, j - 1 + n, i - 1 + m) * kernel[m * 3 + n];
                }
            }
            out[t++] = sum;
        }
    }
}

void mat_mul(NN_data input[], int size_in, const NN_data weights[], int width_w, int height_w, NN_data output[])
{
    if (size_in != width_w)
    {
        std::cout << "error" << std::endl;
        return;
    }
    NN_data sum;
    for (int i = 0; i < height_w; i++)
    {
        sum = 0;
        for (int j = 0; j < width_w; j++)
        {
            sum += weights[i * width_w + j] * input[j];
        }
        output[i] = sum;
    }
}
void add_vec(NN_data vec[], NN_data bias[], int size)
{
    for (int i = 0; i < size; i++)
    {
        vec[i] += bias[i];
    }
}

bool isequal(NN_data a[], int width, int height, NN_data b[])
{
    for (int i = 0; i < width * height; i++)
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

void relu(NN_data input[], NN_data output[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (input[i] < 0)
            output[i] = 0;
    }
    return;
}

Point nn(NN_data input_img[])
{
    const int cols_1 = 54;
    const int rows_1 = 30;
    const int cols_1_conv = 52;
    const int rows_1_conv = 28;
    const int cols_2 = 26;
    const int rows_2 = 14;
    const int cols_2_conv = 24;
    const int rows_2_conv = 12;
    const int cols_3 = 12;
    const int rows_3 = 6;
    const int cols_3_conv = 10;
    const int rows_3_conv = 4;
    const int cols_out = 5;
    const int rows_out = 2;
    NN_data out_conv[cols_1 * rows_1];
    NN_data out_pool[cols_1 * rows_1];
    for (int i = 0; i < cols_1*rows_1; i++)
    {
        out_pool[i] = input_img[i];
    }
    
    applySingleKernel(out_pool, layer_0[0][0], cols_1, rows_1, out_conv);
    relu(out_conv, out_conv, cols_1_conv * rows_1_conv);
    maxPooling(out_conv, cols_1_conv, rows_1_conv, out_pool);

    applySingleKernel(out_pool, layer_1[0][0], cols_2, rows_2, out_conv);
    relu(out_conv, out_conv, cols_2_conv * rows_2_conv);
    maxPooling(out_conv, cols_2_conv, rows_2_conv, out_pool);

    applySingleKernel(out_pool, layer_2[0][0], cols_3, rows_3, out_conv);
    relu(out_conv, out_conv, cols_3_conv * rows_3_conv);
    maxPooling(out_conv, cols_3_conv, rows_3_conv, out_pool);

    mat_mul(out_pool, cols_out * rows_out, layer7_weights, cols_out * rows_out, n_layer7, out_conv);
    add_vec(out_conv, bias_layer7, n_layer7);
    relu(out_conv, out_conv, n_layer7);

    mat_mul(out_conv, n_layer7, layer8_weights, n_layer7, n_layer8, out_pool);
    add_vec(out_pool, bias_layer8, n_layer8);
    relu(out_pool, out_pool, n_layer8);

    mat_mul(out_pool, n_layer8, layer9_weights, n_layer8, n_layer9, out_conv);
    add_vec(out_conv, bias_layer9, n_layer9);
    relu(out_conv, out_conv, n_layer9);

    mat_mul(out_conv, n_layer9, layer10_weights, n_layer9, n_layer10, out_pool);
    add_vec(out_pool, bias_layer10, n_layer10);
    Point p;
    p.x = out_pool[0];
    p.y = out_pool[1];
    return p;
}