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
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"

class LaneDetector {
  private:
    cv::Mat inputImage;
    cv::Mat roiImage;
    cv::Mat grayImage;
    cv::Mat bwImage;
    cv::Mat testImage;
    cv::Mat edgedImage;
    cv::Mat threshImage;
    std::vector<int> lines;
    double rho = 1;
    double theta = 1;
    double threshold;
    double leftSlope;
    double rightSlope;
    double leftPoints;
    double rightPoints;
    double meanLeftSlope;
    double meanRightSlope;
    std::string turnPredict;

  public:
    cv::Mat readFrame(int frameNumber);
    cv::Mat roiMaskSelection(cv::Mat inputImage);
    // cv::Mat hsvThresholdY(cv::Mat roiImage);
    //    cv::Mat hsvThresholdW(cv::Mat roiImage);
    //    cv::Mat morph(cv::Mat hsv);
    cv::Mat edgeDetector(cv::Mat threshImage);
    std::vector<std::vector<cv::Vec4i> > houghTransform(cv::Mat);
    cv::Vec4d lineFitting(std::vector<cv::Vec4i>, cv::Mat);
    double slopeCalculation(std::vector<int>);
    std::string predictTurn(double, double);
    void plotResults(cv::Mat, std::string, std::vector<int>, std::vector<int>);
};

class LanePredictor : public LaneDetector {
  private:
    cv::Point pnt1;
    cv::Point pnt2;
    cv::Mat inputImageP;
    std::vector<cv::Vec4i> lines_p;
    cv::Mat frameP;
    cv::Vec4d yellow_lanes;
    double slope_thresh = 0.7;
    std::vector<double> slopes;
    std::vector<cv::Vec4i> selected_lines;

  public:
    cv::Mat hsvThresholdY(cv::Mat frameP);
    cv::Vec4d detectYellow(cv::Mat);
    cv::Mat plotPolygon(cv::Mat, cv::Vec4d, cv::Vec4d);
    std::string wrongLanePredictor(cv::Vec4d);
    cv::Mat predictTurn(cv::Vec4d, cv::Vec4d, cv::Mat);
};
