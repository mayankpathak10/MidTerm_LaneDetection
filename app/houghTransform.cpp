/**
 * @file    houghTransform.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This file is a library file to implement hough tranform to find
 *  lines in the edged image then classify detected lines into left
 *  and right lanes
 *
 * @dependencies: This file depends on LaneDetector.hpp
 */

#include "../include/LaneDetector.hpp"

/**
 * @brief      reads image and return lane points
 *             This file is a library file to implement hough tranform to find
 *             lines in the edged image then classify detected lines into left
 *             and right lane
 * @param[in]  roi_image cv::Mat
 * @return     lanes std::vector<std::vector<cv::Vec4i> >
 */
std::vector<std::vector<cv::Vec4i> > LaneDetector::houghTransform(
    cv::Mat roi_image) {
    // vector to store left and right lane points
    std::vector<std::vector<cv::Vec4i> > lanes(2);
    // variable to iterate over lines
    size_t iter_size = 0;
    // variable to store line end points
    cv::Point pnt1;
    cv::Point pnt2;
    // slope threshold to filter lines
    double slope_thresh = 0.3;
    std::vector<double> slopes;
    std::vector<cv::Vec4i> selected_lines;
    std::vector<cv::Vec4i> right_lines, left_lines;
    std::vector<cv::Vec4i> lines_p;   // to store hough lines
    // center axis to classify left and right lanes
    double imgCenterY;
    imgCenterY = static_cast<double>((roi_image.cols / 2));

    // finding hough lines
    cv::HoughLinesP(roi_image, lines_p, 1, CV_PI / 180, 20, 20, 30);   // HoughP

    // Calculate the slope of all the detected lines
    for (auto i : lines_p) {
        pnt1 = cv::Point(i[0], i[1]);
        pnt2 = cv::Point(i[2], i[3]);

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

    // Split the lines into right and left lines
    imgCenterY = static_cast<double>((roi_image.cols / 2));
    while (iter_size < selected_lines.size()) {
        pnt1 = cv::Point(selected_lines[iter_size][0],
                         selected_lines[iter_size][1]);
        pnt2 = cv::Point(selected_lines[iter_size][2],
                         selected_lines[iter_size][3]);

        // Condition to classify line as left side or right side
        if (slopes[iter_size] > 0 && pnt2.x > imgCenterY &&
            pnt1.x > imgCenterY) {
            right_lines.push_back(selected_lines[iter_size]);
        } else if (slopes[iter_size] < 0 && pnt2.x < imgCenterY &&
                   pnt1.x < imgCenterY) {
            left_lines.push_back(selected_lines[iter_size]);
        }
        iter_size++;
    }

    // storing left and righ lane points in an array
    lanes[0] = right_lines;
    lanes[1] = left_lines;

    return lanes;
}
