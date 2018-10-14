#include "../include/LaneDetector.hpp"

cv::Mat LaneDetector::hsvThresholdW(cv::Mat roiImage) {
    cv::Mat HSV;

    // convert RGB roiImage to HSV
    cv::cvtColor(roiImage, HSV, CV_BGR2HSV);
    std::vector<cv::Mat> hsv_planes;
    cv::split(HSV, hsv_planes);
    cv::Mat h = hsv_planes[0];   // H channel
    cv::Mat s = hsv_planes[1];   // S channel
    cv::Mat v = hsv_planes[2];   // V channel

    //// White   color range
    cv::Scalar hsv_lw(0, 0, 240);
    cv::Scalar hsv_hw(255, 15, 255);
    cv::Mat bw2;
    cv::Mat bwImage;
    cv::inRange(HSV, hsv_lw, hsv_hw, bw2);

    // imshow("Specific Colour", bw);

    return bw2;
}
