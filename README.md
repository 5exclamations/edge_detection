# edge_detection
In this project, I implemented a C program that can detect edges within images. The goal is to find the
borders between homogeneous areas of similar hues and grey-scale values. Detecting edges finds numerous
applications in object detection, such as in self-driving cars, artistic image filters, or image compression algorithms<br /><br /><br />




The foundation of the edge detection algorithm lies in computing the discrete derivatives of the image. 
The idea: the absolute value of the derivate measures how different nearby values are.
In the context of image processing, we are concerned with the difference of the grey-scale values of neighboring
pixels of the image. A difference of two neighboring pixels’ grey-scale values that exceeds some threshold indicates
an edge in the content of the image. In order to ignore less important edges of the image, we will initially blur
the image. Both computing the discrete derivative as well as blurring the image can be represented using the
mathematical operation convolution.<br /><br /><br />





The Algorithm<br /><br />


(1) reading the original image<br />
(2) blurring the image through convolution with a Gaussian kernel<br />
(3) computing the discrete derivative in x and y direction through convolution with Sobel kernels<br />
(4) computing the magnitude of the gradient vector at each pixel<br />
(5) determining edge pixels by comparing the grey-scale values against the threshold<br />
(6) outputting the image as black and white image<br /><br /><br />




Building, Running and Testing<br /><br />


Compiling the Project:<br />

You may build the project by executing the provided Makefile, e.g. by running make in your WSL, or terminal.
Upon successful build, a binary executable edgedetection will be created in the directory bin/. Alternatively,
you may compile and link the files in the src/ directory manually.<br />

Command-Line Arguments:<br />

The edgedetection application implements the following command-line syntax:<br /><br />

            edgedetection -T < threshold > < image file >
<br /><br />

where -T <treshold> sets the threshold value relevant for step (e) of the algorithm described in section 2 and
<image file> is the path to the input image. The file main.c documents where the (intermediate) output
images will be stored.<br />

To launch the application after successfully making the project from the root directory of your project with a
threshold value of 100 and the test image img_P.pgm, you should execute<br /><br />

            ./ bin / edgedetection -T 100 test / data / input / img_P . pgm
<br /><br />

Parsing the command-line arguments is already implemented in argparse.c of your project template and may
be ignored. After parsing the command-line arguments, the respective values are stored in the global variables
image_file_name and threshold, see argparser.h.
