/**
 * @file    detectYellow.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This file is a library file to detect yellow lanes as per
 *  hsvthreshold output. This file inherits hsvThresholdY,
 *  edgeDetector, roiMaskSelection and lineFitting functions
 *  from LaneDetector Class.
 *
 * @dependencies: This file depends on LaneDetector.hpp
 */

#include "../include/LaneDetector.hpp"


/**
 * LanePredictor::detectYellow, returns end points of yellow lanes
 *         after curve fitting on points found from hough transform.
 * @param  frame [cv::Mat]
 * @return       [cv::Vect4d]
 */
cv::Vec4d LanePredictor::detectYellow(cv::Mat frame) {
    cv::Mat copy_fame;  // to store input image copy
    frame.copyTo(copy_fame);
    cv::Point pnt1;
    cv::Point pnt2;
    cv::Vec4d yellow_lanes;
    double slope_thresh = 0.7;
    std::vector<double> slopes;
    std::vector<cv::Vec4i> lines_p;
    std::vector<cv::Vec4i> selected_lines;

    cv::Mat hsvThresholdImage = LanePredictor::hsvThresholdY(frame);
    cv::Mat edgesP = LanePredictor::edgeDetector(hsvThresholdImage);
    cv::Mat roiP = LanePredictor::roiMaskSelection(edgesP);

    // finding hough lines from the edges found on the image
    // values of parameters found using trial and error.
    HoughLinesP(roiP,             // Source Image
                lines_p,           // output lines
                1,                // rho
                CV_PI / 180,      // theta
                10,               // threshold of intersections
                10,               // min Line Lengths
                10);              // max gap between two points

    // extracting points from all the detected lines
    for (auto i : lines_p) {
        pnt1 = cv::Point(i[0], i[1]);  // Point 1 of line vector
        pnt2 = cv::Point(i[2], i[3]);  // Point 2 of line vector

        // Calculating Slope
        double slope =
            (static_cast<double>(pnt2.y) - static_cast<double>(pnt1.y)) /
            (static_cast<double>(pnt2.x) - static_cast<double>(pnt1.x) +
             0.00001);

        // filtering lines as per the slope and
        // storing the selected lines and slopes
        if (std::abs(slope) > slope_thresh) {
            slopes.push_back(slope);
            selected_lines.push_back(i);
        }
    }

    // To fit line only if selected any
    if (selected_lines.size() > 0) {
        yellow_lanes = LanePredictor::lineFitting(selected_lines, copy_fame);
    }

    return yellow_lanes;
}
