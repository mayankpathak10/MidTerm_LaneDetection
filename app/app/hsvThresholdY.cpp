#include "../include/LaneDetector.hpp"

cv::Mat LaneDetector::hsvThresholdY(cv::Mat roiImage) {
    cv::Mat HSV;

    // convert RGB roiImage to HSV
    cv::cvtColor(roiImage, HSV, CV_BGR2HSV);
    std::vector<cv::Mat> hsv_planes;
    cv::split(HSV, hsv_planes);
    cv::Mat h = hsv_planes[0];   // H channel
    cv::Mat s = hsv_planes[1];   // S channel
    cv::Mat v = hsv_planes[2];   // V channel

    //// yellow color range
    cv::Scalar hsv_ly(1, 40, 133);
    cv::Scalar hsv_hy(90, 150, 255);
    cv::Mat bw1;
    cv::inRange(HSV, hsv_ly, hsv_hy, bw1);

    return bw1;
}
