#include "matmul.hpp"
#include <iostream>
#include "kernels.hpp"
#include <assert.h>

NN_data getPixelVal(NN_data arr[], int w, int h, int x, int y)
{
    if (x < 0 || x >= w || y < 0 || y >= h)
        return 0;
    return arr[y * w + x];
}

float max(float a, float b, float c, float d)
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
    for (int i = 0; i < h; i += 2)
    {
        for (int j = 0; j < w; j += 2)
        {
            out[t] = max(getPixelVal(arr, w, h, j, i), getPixelVal(arr, w, h, j, i + 1), getPixelVal(arr, w, h, j + 1, i), getPixelVal(arr, w, h, j + 1, i + 1));
            t++;
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
            out[t] = sum;
            t++;
        }
    }
}

// void applyFullKernel(NN_data arr[][],NN_data kernel[][], int w, int h, NN_data out[][], int kernel_num, int input_depth){

//     for (int i = 0; i < kernel_num; i++)
//     {
//         NN_data temp[27*48];
//         for (int j = 0; j < input_depth; j++)
//         {
//             applySingleKernel(arr[i],kernel[i][j],w,h,temp);
//             add_vec(out[i],temp,);
//         }
//     }
// }

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
    // NN_data vec[3] = {1, 2, 3};
    // NN_data weights[6] = {0.5, 1, 1.5, 2, 2.5, 3};
    // NN_data output[3];
    // NN_data result[] = {7, 16};
    // mat_mul(vec, 3, weights, 3, 2, output);
    // assert(isequal(output, 1, 2, result));
    // for (int i = 0; i < 2; i++)
    // {
    //     std::cout << output[i] << std::endl;
    // }
    // NN_data out[2];
    // nn(input_img1, out);
    // for (int i = 0; i < 3; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         std::cout << img[i * cols + j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    const int cols_1 = 27;
    const int rows_1 = 48;
    const int cols_1_conv = 46;
    const int rows_1_conv = 25;
    const int cols_2 = 23;
    const int rows_2 = 13;
    const int cols_2_conv = 21;
    const int rows_2_conv = 11;
    const int cols_3 = 11;
    const int rows_3 = 6;
    const int cols_3_conv = 9;
    const int rows_3_conv = 4;
    const int cols_out = 5;
    const int rows_out = 2;
    NN_data out_conv[4][cols_1 * rows_1];
    NN_data out_pool[4][cols_1 * rows_1];
    NN_data input_img[cols_1 * rows_1];
    NN_data temp[cols_1 * rows_1] = {0};
    for (int i = 0; i < cols_1 * rows_1; i++)
    {
        input_img[i] = img[i];
    }


    for (int i = 0; i < 4; i++)
    {
        applySingleKernel(input_img, layer_0[i][0], cols_1, rows_1, out_conv[i]);

        maxPooling(out_conv[i], cols_1_conv, rows_1_conv, out_pool[i]);

        relu(out_pool[i], out_pool[i], cols_2 * rows_2);
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            applySingleKernel(out_pool[i], layer_1[j][i], cols_2, rows_2, temp);
            add_vec(out_conv[i], temp, cols_2_conv * rows_2_conv);
        }
        maxPooling(out_conv[i], cols_2_conv, rows_2_conv, out_pool[i]);
        relu(out_pool[i], out_pool[i], cols_3 * cols_3);
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            applySingleKernel(out_pool[i], layer_2[j][i], cols_3, rows_3, temp);
            add_vec(out_conv[i], temp, cols_3_conv * rows_3_conv);
        }
        maxPooling(out_conv[i], cols_3_conv, rows_3_conv, out_pool[i]);
        relu(out_pool[i], out_pool[i], cols_out * rows_out);
    }

    NN_data fully_connected_in[cols_out*rows_out];
    int t = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < j; j++)
        {
            fully_connected_in[t++] = out_pool[i][j];
        }
        
    }
    mat_mul(fully_connected_in, cols_out*rows_out, layer7_weights, cols_out*rows_out, n_layer1, out_conv[0]);
    add_vec(temp_output, bias_layer1, n_layer1);
    relu(temp_output, temp_output, n_layer1);

    
    // for (int i = 0; i < 4; i++)
    // {
    //     applySingleKernel(out_pool[i], layer_0[0][i], cols_2, rows_2, out_conv1);
    //     add_vec(out_conv1_sum, out_conv1);
    // }

    // for (int i = 0; i < 1150; i++)
    // {
    //     std::cout << out[i] << std::endl;
    // }
    return 0;
}