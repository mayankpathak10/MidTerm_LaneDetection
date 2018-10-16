/**
 * @file    main.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
 * @version 1.0
 * @copyright (c) MIT License 2018 Mayank Pathak, Bhargav Dandamudi
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This is the header file to declare all the class variables and
 *  functions that will be used for the Lane Detection Implementation.
 *
 * @dependencies: This program needs the following libraries in
 *                order to execute properly:
 *                OpenCV, String, IOstream, vector
 */

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>

/**
 * @brief      Class for lane detector.Carries all the functions
 *             related to detect the yellow and white lanes
 */
class LaneDetector {
  private:
    cv::Mat input_image;  // variable to store the frame
    cv::Mat roi_image;
    cv::Mat gray_image;
    cv::Mat test_image;
    cv::Mat edged_image;
    cv::Mat thresh_image;
    std::vector<int> lines;  // store all hough lines
    double rho = 1;         // hough transform parameter
    double theta = 1;       // hough transform parameter
    double threshold;
    double left_slope;
    double right_slope;
    double left_points;
    double right_points;


  public:
    // LaneDetector();     // Default constructor
    // ~LaneDetector(); // Default Destructor
    /**
     * @brief      Reads a frame.
     *
     * @param[in]  frame_number  The frame number
     *
     * @return     { frame of the given frame index}
     */
    cv::Mat readFrame(int frame_number);

    /**
     * @brief      { selects a trapezoidal region in given image}
     *
     * @param[in]  input_image  The input image
     *
     * @return     { retuns region of interest in given image }
     */
    cv::Mat roiMaskSelection(cv::Mat input_image);

    /**
     * @brief      { applies canny edge detections on given image }
     *
     * @param[in]  thresh_image  The thresh image
     *
     * @return     { image containing all the edges }
     */
    cv::Mat edgeDetector(cv::Mat thresh_image);

    /**
     * @brief      { Applies Hough Transform and classifies lanes
     *                based on slopes     }
     *
     * @param[in]  { cv::Mat edged Image }
     *
     * @return     { vector containing all points of
     *               left and right lanes }
     */
    std::vector<std::vector<cv::Vec4i> > houghTransform(cv::Mat);

    /**
     * @brief      { curve fits a line using multiple lines }
     *
     * @param[in] lines   {vector containing lines }
     * @param[in] cv::Mat { input_image }
     *
     * @return     { two ends of the fit line }
     */
    cv::Vec4d lineFitting(std::vector<cv::Vec4i>, cv::Mat);
};
/**
 * @brief      Class for lane predictor.
 */
class LanePredictor : public LaneDetector {
  private:
    std::string lane_indicator;
    cv::Mat inputImageP;
// std::vector<cv::Vec4i> lines_p;
    cv::Mat frameP;
    std::string turn_predict;    // variable stores the lane turn prediction
// cv::Vec4d yellow_lanes;
// cv::Vec4d white_lanes;
// double slope_thresh = 0.7;
// std::vector<double> slopes;
// std::vector<cv::Vec4i> selected_lines;

  public:
    // LanePredictor(); // default constructor
    // ~LanePredictor(); // default destructor

    /**
     * @brief      { to threshold the image to get only yellow lanes}
     *
     * @param[in]  frameP  The frame of the video
     *
     * @return     { thresholded image }
     */
    cv::Mat hsvThresholdY(cv::Mat frameP);

    /**
     * @brief      { It finds the yellow lane }
     *
     * @param[in]    { thresholded image }
     *
     * @return     { end points of the yellow lines  }
     */
    cv::Vec4d detectYellow(cv::Mat);

    /**
      * @brief      { to plot a polygon over detected lanes  }
     *
     * @param[in]  { image to plot lanes}
     * @param[in]  { left lanes }
     * @param[in]  { right lanes }
     *
     * @return     {Image with polygon plot }
     */
    cv::Mat plotPolygon(cv::Mat, cv::Vec4d, cv::Vec4d);

    /**
     * @brief      {predict if vehicle is on wrong lane }
     *
     * @param[in]  { yellow lane end points}
     *
     * @return     {string indicating the lane}
     */
    std::string wrongLanePredictor(cv::Vec4d);

    /**
     * @brief      {function which calculates vanishing points
     *               and predicts turn  }
     *
     * @param[in]  { left lanes end points}
     * @param[in]  { right lane end points }
     * @param[in]  { Output Image }
     *
     * @return     {Output Image with predicted turns text }
     */
    std::string predictTurn(cv::Vec4d, cv::Vec4d, cv::Mat);
};
