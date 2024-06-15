#include <stdio.h>
#include <stdlib.h>

#include "argparser.h"
#include "convolution.h"
#include "derivation.h"
#include "gaussian_kernel.h"
#include "image.h"

int main(int const argc, char **const argv) {
       parse_arguments(argc, argv);
       printf("Computing edges for image file %s with threshold %i\n", image_file_name, threshold);


       int w;
       int h;
       float* image = read_image_from_file(image_file_name, &w, &h);
       float* blur_img = array_init(w * h);
       float* derivation_x = array_init(w * h);
       float* derivation_y = array_init(w * h);
       float* blur_derivation_x = array_init(w * h);
       float* blur_derivation_y = array_init(w * h);
       float* gradient = array_init(w * h);
       float* scaled_gradient = array_init(w * h);


       convolve(blur_img, image, w, h, gaussian_k, gaussian_w, gaussian_h);
       write_image_to_file(blur_img, w, h, "out_blur.pgm");

       derivation_x_direction(derivation_x, blur_img, w, h);
       derivation_y_direction(derivation_y, blur_img, w, h);

       scale_image(blur_derivation_x, derivation_x, w, h);
       scale_image(blur_derivation_y, derivation_y, w, h);

       write_image_to_file(blur_derivation_x, w, h, "out_d_x.pgm");
       write_image_to_file(blur_derivation_y, w, h, "out_d_y.pgm");

       gradient_magnitude(gradient, derivation_x, derivation_y, w, h);

       scale_image(scaled_gradient, gradient, w, h);
       write_image_to_file(scaled_gradient, w, h, "out_gm.pgm");
       
       apply_threshold(gradient, w, h, threshold);
       write_image_to_file(gradient, w, h, "out_edges.pgm");


       array_destroy(blur_img);
       array_destroy(derivation_x);
       array_destroy(derivation_y);
       array_destroy(blur_derivation_x);
       array_destroy(blur_derivation_y);
       array_destroy(gradient);
       array_destroy(scaled_gradient);
       array_destroy(image);
}
