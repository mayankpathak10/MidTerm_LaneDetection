#include "../include/LaneDetector.hpp"

cv::Mat LaneDetector::readFrame(int frameNumber) {
    cv::Mat Frame;
    cv::VideoCapture cap("../Dataset/Dataset2.mp4");
    cap.set(cv::CAP_PROP_POS_FRAMES, frameNumber);
    cap >> Frame;

    return Frame;
}
