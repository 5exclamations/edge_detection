#include "convolution.h"

#include <stdlib.h>

#include "image.h"

void convolve(float *result, const float *img, int w, int h,
              const float *matrix, int w_m, int h_m) {
    int current_width = 0;
    int current_height = 0;
    int current_width_matrix = 0;
    int current_height_matrix = 0;
    float val = 0.0;
    while(current_height < h){
        while(current_width < w){
            while (current_height_matrix < h_m){
                while (current_width_matrix < w_m){
                    val += (matrix[(current_height_matrix * w_m) + current_width_matrix] * get_pixel_value(img, w, h, (current_width + current_width_matrix - (w_m / 2)), (current_height + current_height_matrix - (h_m / 2))));
                    current_width_matrix++;
                }
                current_width_matrix = 0;
                current_height_matrix++;
            }
            result [(current_height * w) + current_width] = val;
            val = 0.0;
            current_height_matrix = 0;
            current_width_matrix = 0;
            current_width++;
        }
        current_height++;
        current_width = 0;
    }
}