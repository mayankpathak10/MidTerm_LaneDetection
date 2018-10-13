#include "../include/LaneDetector.hpp"

cv::Mat LaneDetector::roiMaskSelection(cv::Mat hsvThreshold) {
    cv::Mat roi;
    cv::Mat mask = cv::Mat::zeros(hsvThreshold.size(), hsvThreshold.type());
    cv::Point pts[4] = {cv::Point(15, 280), cv::Point(15, 440),
                        cv::Point(630, 440), cv::Point(630, 280)};
    // Create a binary polygon mask
    cv::fillConvexPoly(mask, pts, 4, cv::Scalar(255, 0, 0));
    // Multiply the edges image and the mask to get the output
    cv::bitwise_and(hsvThreshold, mask, roi);

    return roi;
}
