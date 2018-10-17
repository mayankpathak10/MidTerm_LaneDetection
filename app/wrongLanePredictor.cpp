/**
 * @file    wrongLanePredictor.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This file is a library file to predict vehicle position
 *  based on yellow lane w.r.t. the frame size.
 *  (Assuming Right-Hand Drive System)
 *
 * @dependencies: This file depends on LaneDetector.hpp
 */

#include "../include/LaneDetector.hpp"

/**
 * @brief   [LanePredictor::wrongLanePredictor description]
 *          This file is a library file to predict vehicle position
 *          based on yellow lane w.r.t. the frame size.
 *          (Assuming Right-Hand Drive System)
 * @param[in]  yellow_line     [cv::Vec4d]
 * @return lane_indicator  [string]
 */
std::string LanePredictor::wrongLanePredictor(cv::Vec4d yellow_line) {
    cv::Vec4d yellow_lanes;
    cv::Vec4d white_lanes;
    // yellow lane y reference coordinate
    double ylower = 460;
    std::string lane_indicator = "No Lane Found :/";
    double x11 = yellow_line[0];
    double y11 = yellow_line[1];
    double x21 = yellow_line[2];
    double y21 = yellow_line[3];
    double slope1 = ((y21 - y11) / (x21 - x11));
    // to store x coordinate of yellow lane
    cv::Point lower_yellow;
    // to calculate x coordinate for the lower
    // y reference coordinate of yellow lane
    lower_yellow.x = x11 + (ylower - y11) / slope1;

    // applying threshold to determine lane
    if (lower_yellow.x > 320) {
        std::string lane_indicator = "Wrong Lane!!";
        return lane_indicator;
    } else {
        std::string lane_indicator = "Stay on this Lane!";
        return lane_indicator;
    }

    return lane_indicator;
}
