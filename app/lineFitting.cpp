/**
 * @file    lineFitting.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This file is a library file to fit lines over the
 *  detected lines on the input image.
 * @dependencies: This file depends on LaneDetector.hpp
 */

#include "../include/LaneDetector.hpp"

/**
 * @brief      fits a line over given input points
 *              This file is a library file to fit lines over the
 *             detected lines on the input image.
 * @param[in]  lineVector  The line vector
 * @param[in]  inputImage  The input image
 *
 * @return     { return two points based one fit line}
 */
cv::Vec4d LaneDetector::lineFitting(std::vector<cv::Vec4i> lineVector,
                                    cv::Mat inputImage) {
    std::vector<cv::Point> all_points;   // to store all points in a vector
    cv::Vec4d fit_line;                  // to  store output of the function
    cv::Point pt1, pt2;                  // end points of the fit line
    // looping over total number lines
    for (auto i : lineVector) {
        cv::Point initial_point = cv::Point(i[0], i[1]);
        cv::Point final_point = cv::Point(i[2], i[3]);

        all_points.push_back(initial_point);
        all_points.push_back(final_point);
    }
    // open cv function to fitline of all the segregated points
    cv::fitLine(all_points, fit_line, CV_DIST_L2, 0, 0.01, 0.01);

    // calculating initial and final points of the lines
    double d = sqrt(static_cast<double>(fit_line[0] * fit_line[0]) +
                    static_cast<double>(fit_line[1] * fit_line[1]));
    fit_line[0] /= d;
    fit_line[1] /= d;
    float t = (inputImage.cols + inputImage.rows);
    pt1.x = cvRound(fit_line[2] - fit_line[0] * t);
    pt1.y = cvRound(fit_line[3] - fit_line[1] * t);
    pt2.x = cvRound(fit_line[2] + fit_line[0] * t);
    pt2.y = cvRound(fit_line[3] + fit_line[1] * t);

    // storign all points in one array
    fit_line[0] = pt1.x;
    fit_line[1] = pt1.y;
    fit_line[2] = pt2.x;
    fit_line[3] = pt2.y;

    return fit_line;
}
