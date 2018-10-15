#include "../include/LaneDetector.hpp"

std::vector<std::vector<cv::Vec4i> > LaneDetector::houghTransform(
    cv::Mat roiImage) {
    // bool right_flag;
    // bool left_flag;
    std::vector<std::vector<cv::Vec4i> > Lanes(2);
    size_t j = 0;
    cv::Point ini;
    cv::Point fini;
    double slopeThresh = 0.3;
    std::vector<double> slopes;
    // cv::Vec4d right_line;
    // cv::Vec4d left_line;
    // std::vector<cv::Point> right_pts;
    // std::vector<cv::Point> left_pts;
    std::vector<cv::Vec4i> selectedLines;
    std::vector<cv::Vec4i> rightLines, leftLines;
    std::vector<cv::Vec4i> linesP;   // for Hough
    double imgCenterY;
    imgCenterY = static_cast<double>((roiImage.cols / 2));

    cv::HoughLinesP(roiImage, linesP, 1, CV_PI / 180, 20, 20, 30);   // HoughP

    // Calculate the slope of all the detected lines
    for (auto i : linesP) {
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

    // Split the lines into right and left lines
    imgCenterY = static_cast<double>((roiImage.cols / 2));
    while (j < selectedLines.size()) {
        ini = cv::Point(selectedLines[j][0], selectedLines[j][1]);
        fini = cv::Point(selectedLines[j][2], selectedLines[j][3]);

        // Condition to classify line as left side or right side
        if (slopes[j] > 0 && fini.x > imgCenterY && ini.x > imgCenterY) {
            rightLines.push_back(selectedLines[j]);
        } else if (slopes[j] < 0 && fini.x < imgCenterY && ini.x < imgCenterY) {
            leftLines.push_back(selectedLines[j]);
        }
        j++;
    }

    Lanes[0] = rightLines;
    Lanes[1] = leftLines;

    return Lanes;
}
