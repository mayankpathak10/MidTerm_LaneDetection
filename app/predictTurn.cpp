/**
 * @file    predictTurn.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This file is a library file to predict turns based on the
 *  concept of vanishing point.
 *
 * @dependencies: This file depends on LaneDetector.hpp
 */

#include "../include/LaneDetector.hpp"

/**
 * @brief   [LanePredictor::predictTurn]
 *          This file is a library file to predict turns based on the
 *          concept of vanishing point.
 *
 * @param[in]   left_lines  [cv::Vec4d]
 * @param[in]   right_lines [cv::Vec4d]
 * @param[in]   input_image [cv::Mat]
 * @return[in]  input_image [cv::Mat]
 */
std::string LanePredictor::predictTurn(cv::Vec4d left_lines,
                                       cv::Vec4d right_lines,
                                       cv::Mat input_image) {
    // finding intersection point between to lanes.
    cv::Point vanishingPoint;
    // extracting points from left_lines
    double x11 = left_lines[0];
    double y11 = left_lines[1];
    double x21 = left_lines[2];
    double y21 = left_lines[3];
    double slope1 = ((y21 - y11) / (x21 - x11));
    // extracting points from right_lines
    double x12 = right_lines[0];
    double y12 = right_lines[1];
    double x22 = right_lines[2];
    double y22 = right_lines[3];
    double slope2 = ((y22 - y12) / (x22 - x12));

    vanishingPoint.x =
        ((y22 - y11) + slope1 * x11 - slope2 * x22) / (slope1 - slope2);
    vanishingPoint.y =
        (slope1 * ((y22 - y11) - (slope2 * x22) + (slope2 * x11))) /
            (slope1 - slope2) +
        y11;

    // plotting vanishing point
    circle(input_image, vanishingPoint, 1, cv::Scalar(0, 255, 0), 3, 8, 0);

    // Thresholding to predict turns
    if (vanishingPoint.x < 287) {
        std::string turn_predict = "Left Turn Ahead!";

        return turn_predict;
    } else if (vanishingPoint.x > 317) {
        std::string turn_predict = "Right Turn Ahead!";

        return turn_predict;
    }

    return turn_predict;
}
