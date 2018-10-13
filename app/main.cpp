/**
 * @file    main.cpp
 * @author  Mayank Pathak
 * @version 1.0
 * @copyright GNU Public License
 *
 * @brief Mid-Term Project (with partner component)
 *
 * @section DESCRIPTION
 *
 *  This is the main file for the LaneDetection implementation.
 *
 */

#include "../include/LaneDetector.hpp"

int main() {
    LaneDetector LaneDetector;
    int totalFrames;
    cv::VideoCapture frameCount("../Dataset/Dataset2.mp4");
    totalFrames = frameCount.get(CV_CAP_PROP_FRAME_COUNT);
    std::cout << "Total Frames" << totalFrames;
    for (int i = 100; i < 110; ++i) {
        cv::Mat testImage = LaneDetector.readFrame(i);
        cv::Mat hsv = LaneDetector.hsvThreshold(testImage);

        cv::Mat roi = LaneDetector.roiMaskSelection(hsv);
        cv::namedWindow("DIsplay photos", CV_WINDOW_AUTOSIZE);
        cv::namedWindow("DIsplay", CV_WINDOW_AUTOSIZE);
        cv::imshow("DIsplay Photos", hsv);
        cv::imshow("DIsplay", roi);

        cv::waitKey(0);
    }

    cv::destroyAllWindows();
    return 0;
}
