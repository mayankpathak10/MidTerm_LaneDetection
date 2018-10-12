#include <math.h>
#include <iostream>
#include <vector>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;
int main() {
    Mat image;
    image = imread("0001.jpg", CV_LOAD_IMAGE_COLOR);

    if (!image.data) {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    // Create a new matrix to hold the HSV image
    Mat HSV;

    // convert RGB image to HSV
    cvtColor(image, HSV, CV_BGR2HSV);

    namedWindow("Display window", CV_WINDOW_AUTOSIZE);
    imshow("Display window", image);

    // namedWindow("Result window", CV_WINDOW_AUTOSIZE);
    // imshow("Result window", HSV);

    vector<Mat> hsv_planes;
    split(HSV, hsv_planes);
    Mat h = hsv_planes[0];   // H channel
    Mat s = hsv_planes[1];   // S channel
    Mat v = hsv_planes[2];   // V channel

    namedWindow("hue", CV_WINDOW_AUTOSIZE);
    imshow("hue", h);
    // namedWindow("saturation", CV_WINDOW_AUTOSIZE);
    // imshow("saturation", s);
    // namedWindow("value", CV_WINDOW_AUTOSIZE);
    // imshow("value", v);

    //// red color range
    Scalar hsv_l(1, 40, 133);
    Scalar hsv_h(90, 150, 255);
    Mat bw;
    inRange(HSV, hsv_l, hsv_h, bw);
    imshow("Specific Colour", bw);
    ////

    // hue value

    // define ranges

    waitKey(0);
    return 0;
}
