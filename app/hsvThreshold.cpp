#include "../include/LaneDetector.hpp"

cv::Mat LaneDetector::hsvThreshold(cv::Mat roiImage) {
    cv::Mat HSV;

    // convert RGB roiImage to HSV
    cv::cvtColor(roiImage, HSV, CV_BGR2HSV);
    std::vector<cv::Mat> hsv_planes;
    cv::split(HSV, hsv_planes);
    cv::Mat h = hsv_planes[0];   // H channel
    cv::Mat s = hsv_planes[1];   // S channel
    cv::Mat v = hsv_planes[2];   // V channel

    //// red color range
    cv::Scalar hsv_l(1, 40, 133);
    cv::Scalar hsv_h(90, 150, 255);
    cv::Mat bw;
    cv::inRange(HSV, hsv_l, hsv_h, bw);
    // imshow("Specific Colour", bw);

    return bw;
}
