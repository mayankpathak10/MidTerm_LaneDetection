/**
 * @file    hsvThresholdY.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  Split BGR image into HSV planes and apply threshold
 *  on each plane to detect Yellow Lanes.
 *
 * @dependencies: This file depends on LaneDetector.hpp
 */

#include "../include/LaneDetector.hpp"

/**
 * @brief  LanePredictor::hsvThresholdY
 *         Split BGR image into HSV planes and apply threshold
 *         on each plane to detect Yellow Lanes.
 *
 * @param[in]  frame [cv::Mat]
 * @return threshold_image [cv::Mat]
 */
cv::Mat LanePredictor::hsvThresholdY(cv::Mat frame) {
    cv::Mat hsv, threshold_image;
    cv::Scalar hsv_low_y(1, 40, 133);
    cv::Scalar hsv_high_y(90, 150, 255);
    // convert RGB roiImage to hsv
    cv::cvtColor(frame, hsv, CV_BGR2HSV);
    std::vector<cv::Mat> hsv_planes;
    cv::split(hsv, hsv_planes);
    cv::Mat h = hsv_planes[0];   // H channel
    cv::Mat s = hsv_planes[1];   // S channel
    cv::Mat v = hsv_planes[2];   // V channel

    //// yellow color range, found by trial and error

    cv::inRange(hsv, hsv_low_y, hsv_high_y, threshold_image);

    return threshold_image;
}
