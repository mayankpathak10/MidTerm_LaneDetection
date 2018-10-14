#include "../include/LaneDetector.hpp"

cv::Mat LaneDetector::roiMaskSelection(cv::Mat hsvThreshold) {
    cv::Mat roi;
    cv::Mat mask = cv::Mat::zeros(hsvThreshold.size(), hsvThreshold.type());
    cv::Point pts[4] = {cv::Point(73, 441), cv::Point(254, 341),
                        cv::Point(357, 341), cv::Point(500, 441)};
    // Create a binary polygon mask
    cv::fillConvexPoly(mask, pts, 4, cv::Scalar(255, 255, 255));
    // Multiply the edges image and the mask to get the output
    cv::bitwise_and(hsvThreshold, mask, roi);
    // imshow("Roied",roi);
    // hsvThreshold.copyTo(roi, mask);
    return roi;
}
