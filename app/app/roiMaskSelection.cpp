#include "../include/LaneDetector.hpp"

cv::Mat LaneDetector::roiMaskSelection(cv::Mat hsvThreshold) {
    cv::Mat roi;
    cv::Mat mask = cv::Mat::zeros(hsvThreshold.size(), hsvThreshold.type());
    cv::Point pts[4] = {cv::Point(218, 331), cv::Point(376, 331),
                        cv::Point(513, 437), cv::Point(40, 437)};
        // cv::Point pts[4] = {cv::Point(218, 331), cv::Point(376, 331),
        //                 cv::Point(513, 437), cv::Point(40, 437)};
    // Create a binary polygon mask
    cv::fillConvexPoly(mask, pts, 4, cv::Scalar(255, 255, 255));
    // Multiply the edges image and the mask to get the output
    cv::bitwise_and(hsvThreshold, mask, roi);
    // imshow("Roied",roi);
    // hsvThreshold.copyTo(roi, mask);
    return roi;
}
