#include "LaneDetector.hpp"

cv::Mat readFrame(int frameNumber) {
    cv::Mat Frame;
    VideoCapture cap("Dataset2.mp4");
    cap.set(cv::CAP_PROP_POS_FRAMES, frameNumber);
    cv::cap >> Frame;

    return Frame;
}
