#include "matmul.hpp"
#include <iostream>
#include <assert.h>
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
    return;
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

void float_to_fixed(float input[n_inputs], NN_data output[n_inputs])
{
    for (int i = 0; i < n_inputs; i++)
    {
        output[i] = input[i];
    }
}

void mat_mul(NN_data input[], int size_in, NN_data weights[], int width_w, int height_w, NN_data output[])
{
    if (size_in != width_w)
    {
        std::cout << "error" << std::endl;
        return;
    }
    NN_data sum;
    for (int i = 0; i < width_w * height_w; i++)
    {
        sum = 0;
        for (int j = 0; j < size_in; j++)
        {
            sum += weights[i * width_w + j] * input[j];
        }
        output[i] = sum;
    }
    return;
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

void nn(float input_img[n_inputs], NN_data output[2])
{
    NN_data fp_input_img[n_inputs];
    float_to_fixed(input_img, fp_input_img);
    NN_data temp_output[n_layer1];
    NN_data temp_output2[n_layer2];
    NN_data temp_output3[n_layer3];
    NN_data temp_output4[n_layer4];
    NN_data temp_output5[n_layer5];
    NN_data temp_output6[n_layer6];
    mat_mul(fp_input_img, n_inputs, weights::layer1_weights, n_inputs, n_layer1, temp_output);
    add_vec(temp_output, bias_layer1, n_layer1);
    relu(temp_output, temp_output, n_layer1);

    mat_mul(temp_output, n_layer1, weights::layer2_weights, n_layer1, n_layer2, temp_output2);
    add_vec(temp_output2, bias_layer2, n_layer2);
    relu(temp_output2, temp_output2, n_layer2);

    mat_mul(temp_output2, n_layer2, weights::layer3_weights, n_layer2, n_layer3, temp_output3);
    add_vec(temp_output3, bias_layer3, n_layer3);
    relu(temp_output3, temp_output3, n_layer3);
    mat_mul(temp_output3, n_layer3, weights::layer4_weights, n_layer3, n_layer4, temp_output4);
    add_vec(temp_output4, bias_layer4, n_layer4);
    relu(temp_output4, temp_output4, n_layer4);

    mat_mul(temp_output4, n_layer4, weights::layer5_weights, n_layer4, n_layer5, temp_output5);
    add_vec(temp_output5, bias_layer5, n_layer5);
    relu(temp_output5, temp_output5, n_layer5);

    mat_mul(temp_output5, n_layer5, weights::layer6_weights, n_layer5, n_layer6, temp_output6);
    add_vec(temp_output6, bias_layer6, n_layer6);
    std::cout << temp_output6[0] << std::endl;
    std::cout << temp_output6[1] << std::endl;
}
int main()
{
    NN_data vec[3] = {1, 2, 3};
    NN_data weights[6] = {0.5, 1, 1.5, 2, 2.5, 3};
    NN_data output[3];
    NN_data result[] = {7, 16};
    mat_mul(vec, 3, weights, 3, 2, output);
    assert(isequal(output, 1, 2, result));
    for (int i = 0; i < 2; i++)
    {
        std::cout << output[i] << std::endl;
    }
    NN_data out[2];
    nn(input_img1, out);
    return 0;
}