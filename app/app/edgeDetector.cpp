#include "../include/LaneDetector.hpp"

cv::Mat LaneDetector::edgeDetector(cv::Mat morphImage) {
    cv::Mat edge, draw;
    Canny(morphImage, edge, 0, 255, 3);
    edge.convertTo(draw, CV_8U);

    return draw;
}
