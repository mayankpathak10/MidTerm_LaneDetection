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
    cv::Vec4d lineFitting(std::vector<cv::Vec4i>);

    double slopeCalculation(std::vector<int>);
    std::string predictTurn(double, double);
    void plotResults(cv::Mat, std::string, std::vector<int>, std::vector<int>);
};

class LanePredictor : public LaneDetector {
 private:
    cv::Mat inputImageP;
    cv::Mat frameP;

 public:
    cv::Mat hsvThresholdY(cv::Mat frameP);
};
