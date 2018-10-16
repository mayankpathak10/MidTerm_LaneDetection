/**
 * @file    edgeDetector.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This file is a library file to implement Canny edge detection
 *  algorithm on the input frame. The kernel size for the edge
 *  detection algorithm is chosen as 3.
 *
 *
 * @dependencies: This file depends on LaneDetector.hpp
 */


#include "../include/LaneDetector.hpp"

/**
 * @brief      reads image and applys canny edge detecting.
 * @param[in]  roi_image  cv::Mat
 * @return     edge_image cv::Mat
 */
cv::Mat LaneDetector::edgeDetector(cv::Mat roi_image) {
	cv::Mat edge, edge_image;
	Canny(roi_image, edge, 0, 255, 3);
	edge.convertTo(edge_image, CV_8U);

	return edge_image;
}
