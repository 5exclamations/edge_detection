#include "derivation.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "convolution.h"
#include "image.h"

void gradient_magnitude(float *result, const float *d_x, const float *d_y, int w, int h) {
    int current_w = 0;
    int current_h = 0;
    while (current_h < h){
        while (current_w < w){
            result[w * current_h + current_w] = sqrt(d_x[w * current_h + current_w] * d_x[w * current_h + current_w] + d_y[w * current_h + current_w] * d_y[w * current_h + current_w]);
            current_w++;
        }
        current_h++;
        current_w = 0;
    }
}

const float sobel_x[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};

const float sobel_y[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

void derivation_x_direction(float *result, const float *img, int w, int h) {
    convolve(result, img, w, h, sobel_x, 3, 3);
}

void derivation_y_direction(float *result, const float *img, int w, int h) {
    convolve(result, img, w, h, sobel_y, 3, 3);
}
