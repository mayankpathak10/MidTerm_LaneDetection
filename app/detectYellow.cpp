#include "../include/LaneDetector.hpp"

cv::Vec4d LanePredictor::detectYellow(cv::Mat frame) {
    cv::Point ini;
    cv::Point fini;
    cv::Vec4d yellowLanes;
    cv::Mat copyFrame;
    frame.copyTo(copyFrame);
    LanePredictor LanePredictor;
    // LanePredictor LanePredictor;
    double slopeThresh = 0.7;
    std::vector<double> slopes;
    std::vector<cv::Vec4i> selectedLines;
    // cv::Mat frame = LanePredictor.readFrame(i);
    cv::Mat hsvThresholdImage = LanePredictor.hsvThresholdY(frame);
    cv::Mat edgesP = LanePredictor.edgeDetector(hsvThresholdImage);
    cv::Mat roiP = LanePredictor.roiMaskSelection(edgesP);

    std::vector<cv::Vec4i> linesP;
    HoughLinesP(roiP, linesP, 1, CV_PI / 180, 10, 10, 10);
    // std::cout<<"Size of LineP: "<<linesP.size()<<std::endl;
    for (auto i : linesP) {
        // std::cout<<"Entering for loop"<<std::endl;
        ini = cv::Point(i[0], i[1]);
        fini = cv::Point(i[2], i[3]);

        double slope =
            (static_cast<double>(fini.y) - static_cast<double>(ini.y)) /
            (static_cast<double>(fini.x) - static_cast<double>(ini.x) +
             0.00001);

        // If the slope is too horizontal, discard the line
        // If not, save them  and their respective slope
        if (std::abs(slope) > slopeThresh) {
            slopes.push_back(slope);
            selectedLines.push_back(i);
        }
    }

    if (selectedLines.size() > 0) {
        yellowLanes = LanePredictor.lineFitting(selectedLines, copyFrame);
        line(copyFrame, cv::Point(yellowLanes[0], yellowLanes[1]),
             cv::Point(yellowLanes[2], yellowLanes[3]),
             cv::Scalar(55, 255, 251), 3, CV_AA);
    }

    return yellowLanes;
}
