#include "../include/LaneDetector.hpp"

cv::Vec4d LaneDetector::lineFitting(std::vector<cv::Vec4i> lineVector) {
    std::vector<cv::Point> allPoints;
    cv::Vec4d fitLine;
    for (auto i : lineVector) {
        cv::Point ini = cv::Point(i[0], i[1]);
        cv::Point fini = cv::Point(i[2], i[3]);

        allPoints.push_back(ini);
        allPoints.push_back(fini);
    }
    cv::fitLine(allPoints, fitLine, CV_DIST_L2, 0, 0.01, 0.01);

    return fitLine;
}
