/**
 * @file    roiMaskSelection.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This file is a library file to mask the input image
 *  with region of interest.
 *
 * @dependencies: This file depends on LaneDetector.hpp
 */

#include "../include/LaneDetector.hpp"

/**
 * @brief      LaneDetector::roiMaskSelection
 *             This file is a library file to mask the input image
 *             with region of interest.
 *
 * @param[in]  hsv_threshold  cv::Mat
 * @return     roi           cv::Mat
 */
cv::Mat LaneDetector::roiMaskSelection(cv::Mat hsv_threshold) {
    cv::Mat roi;   // Matrix to save image
    // creating empty mask image
    cv::Mat mask = cv::Mat::zeros(hsv_threshold.size(), hsv_threshold.type());
    // determining polygon vertices for roi
    cv::Point pts[4] = {cv::Point(73, 441), cv::Point(254, 341),
                        cv::Point(357, 341), cv::Point(500, 441)};
    // Create a binary polygon mask
    cv::fillConvexPoly(mask, pts, 4, cv::Scalar(255, 255, 255));
    // Multiply the edges image and the mask to get the output
    cv::bitwise_and(hsv_threshold, mask, roi);

    return roi;
}
