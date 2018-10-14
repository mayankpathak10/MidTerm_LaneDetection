#include "../include/LaneDetector.hpp"

cv::Mat LaneDetector::morph(cv::Mat hsv) {
    cv::Mat src = hsv;
    int morph_size = 2;
    cv::Mat element = cv::getStructuringElement(
        cv::MORPH_RECT, cv::Size(2 * morph_size + 1, 2 * morph_size + 1),
        cv::Point(morph_size, morph_size));

    cv::Mat dst;
    cv::morphologyEx(src, dst, cv::MORPH_CLOSE, element);
    return dst;
}
