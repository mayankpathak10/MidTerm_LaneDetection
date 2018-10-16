/**
 * @file    plotPolygon.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This file is a library file to plot a polygon over
 *  detected lanes on the output frame.
 *
 * @dependencies: This file depends on LaneDetector.hpp
 */

#include "../include/LaneDetector.hpp"

/**
 * LanePredictor::plotPolygon
 * @param  input_image  [cv::Mat]
 * @param  yellow_lanes [cv::Vec4d]
 * @param  white_lanes  [cv::Vec4d]
 * @return output      [cv::Mat]
 */
cv::Mat LanePredictor::plotPolygon(cv::Mat input_image, cv::Vec4d yellow_lanes,
                                   cv::Vec4d white_lanes) {
    cv::Mat output;
    input_image.copyTo(output);
    cv::Point upper_yellow;
    cv::Point lower_yellow;
    cv::Point upper_white;
    cv::Point lower_white;
    double ylower = 480;  // horizontal lower side of polygon
    double yupper = 360;  // horizontal upper side of polygon
    // Splitting points from yellow lane
    double x11 = yellow_lanes[0];
    double y11 = yellow_lanes[1];
    double x21 = yellow_lanes[2];
    double y21 = yellow_lanes[3];
    double slope1 = ((y21 - y11) / (x21 - x11));
    // Splitting points from white lane
    double x12 = white_lanes[0];
    double y12 = white_lanes[1];
    double x22 = white_lanes[2];
    double y22 = white_lanes[3];
    double slope2 = ((y22 - y12) / (x22 - x12));

    // setting upper and lower y coordinate limits
    upper_white.y = upper_yellow.y = yupper;
    lower_white.y = lower_yellow.y = ylower;

    // calculating x coordinates for the polygon edges
    upper_yellow.x = x11 + (yupper - y11) / slope1;
    lower_yellow.x = x11 + (ylower - y11) / slope1;
    upper_white.x = x12 + (yupper - y12) / slope2;
    lower_white.x = x12 + (ylower - y12) / slope2;

    // Storing all points as vector, for plotting
    cv::Point pts[4] = {lower_yellow, upper_yellow, upper_white, lower_white};
    // drawing polygon using in-built opencv function
    cv::fillConvexPoly(output,                  // output image
                       pts,                     // vertices
                       4,                       // number of vertices
                       cv::Scalar(0, 0, 255),   // color of polygon
                       CV_AA);                  // Anti-Aliasing

    // plotting polygon boundary lines
    line(input_image, lower_yellow, upper_yellow,
         cv::Scalar(25, 0, 51), 2, CV_AA);
    line(input_image, lower_white, upper_white,
         cv::Scalar(25, 0, 51), 2, CV_AA);
    line(input_image, upper_yellow, upper_white,
         cv::Scalar(25, 0, 51), 2, CV_AA);
    // adding transparency to the polygon
    cv::addWeighted(output, 0.3, input_image, 1.0 - 0.3, 0, input_image);

    return output;
}
