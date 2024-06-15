#include "image.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apply_threshold(float *img, int w, int h, int T) {
    int current_w = 0;
    int current_h = 0;
    while (current_h < h){
        while (current_w < w){
            if (img[w * current_h + current_w] <= T){
                img[w * current_h + current_w] = 0.0f;
            }
            else img[w * current_h + current_w] = 255.0f;
            current_w++;
        }
        current_h++;
        current_w = 0;
    }
}

void scale_image(float *result, const float *img, int w, int h) {
    int current_w = 0;
    int current_h = 0;
    float max = img[0];
    float min = img[0];
    while (current_h < h){
        while (current_w < w){
            if (img[w * current_h + current_w] > max) {
                max = img[w * current_h + current_w];
            }
            if (img[w * current_h + current_w] < min) {
                min = img[w * current_h + current_w];
            }
            current_w++;
        }
        current_h++;
        current_w = 0;
        }
        current_h = 0;
    while (current_h < h){
        while (current_w < w){
           result[w * current_h + current_w] = ((img[w * current_h + current_w] - min) / (max - min)) * 255.0;
           current_w++;
        }
        current_w = 0;
        current_h++;
        }
}

float get_pixel_value(const float *img, int w, int h, int x, int y) {
    if (x < 0){
        x = abs(x + 1);
    }
    if (y < 0){
        y = abs(y + 1);
    }
    if (y >= h){
        y = abs(y - 2 * h + 1);
    }
    if (x >= w){
        x = abs(x - 2 * w + 1);
    }
    return (img[y * w + x]);
}

float *array_init(int size) {
    float *array = malloc(sizeof(array[0]) * size);
    return array;
}

void array_destroy(float *m) {
    free(m);
}

float *read_image_from_file(const char *filename, int *w, int *h) {
    FILE* file;
    float res;
    int i = 0;
    char t[2];
    file = fopen(filename, "r");
    if (file == NULL) {
        fclose(file);
        return NULL;
    }
    fscanf(file, "%2s", t);
    if(t[0] != 'P' || t[1] != '2'){
        fclose(file);
        return NULL;
    }
    fscanf(file, "%d", w);
    fscanf(file, "%d", h);
    int size = *w * *h;
    float *arr = array_init(size);
    fscanf(file, "%d", &i);
    if (i != 255){
        fclose(file);
        return NULL;
    }
    i = 0;
    while(fscanf(file, "%f", &res) != EOF){
        arr[i] = res;
        ++i;
    }
    int j = 0;
    int max = 0;
    int min = arr[0];
    while(j < size){
        if (arr[j] > max) {
            max = arr[j];
        }
        if (arr[j] < min){
            min = arr[j];
        }
        j++;
    }
    if (max > 255 || min < 0){
        fclose(file);
        array_destroy(arr);
        return NULL;
    }
    if(i != size){
        fclose(file);
        array_destroy(arr);
        return NULL;
    }
    fclose(file);
    return arr;
}

void write_image_to_file(const float *img, int w, int h, const char *filename) {
    FILE* f_output;
    f_output = fopen(filename, "w");
    int i = 0;
    fprintf(f_output, "P2\n");
    fprintf(f_output, "%d %d\n 255\n", w, h);
    while (i < h * w){
        fprintf(f_output, "%d ", (int)img[i]);
        i++;
    }
    fclose(f_output);
}
