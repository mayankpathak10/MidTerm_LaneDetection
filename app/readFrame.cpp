/**
 * @file    readFrame.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This file is a library file to read image frames
 *  from the input image as per the frame number given
 *  as argument.
 *
 * @dependencies: This file depends on LaneDetector.hpp
 */

#include "../include/LaneDetector.hpp"

/**
 * [LaneDetector::readFrame]
 * @param  frame_number [int]
 * @return frame        [cv::Mat]
 */
cv::Mat LaneDetector::readFrame(int frame_number) {
	cv::Mat frame;  // matrix to store input frame
	// Video Object to read frame
	cv::VideoCapture cap("../Dataset/Dataset2.mp4");
	cap.set(cv::CAP_PROP_POS_FRAMES, frame_number);
	cap >> frame;

	return frame;
}
