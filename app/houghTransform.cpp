#include "../include/LaneDetector.hpp"

std::vector<std::vector<cv::Vec4i> > LaneDetector::houghTransform(
    cv::Mat roiImage) {
    bool right_flag;
    bool left_flag;
    std::vector<std::vector<cv::Vec4i> > Lanes(2);
    size_t j = 0;
    cv::Point ini;
    cv::Point fini;
    double slope_thresh = 0.3;
    std::vector<double> slopes;
    cv::Vec4d right_line;
    cv::Vec4d left_line;
    std::vector<cv::Point> right_pts;
    std::vector<cv::Point> left_pts;
    std::vector<cv::Vec4i> selected_lines;
    std::vector<cv::Vec4i> right_lines, left_lines;
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
        if (std::abs(slope) > slope_thresh) {
            slopes.push_back(slope);
            selected_lines.push_back(i);
        }
    }

    // Split the lines into right and left lines
    imgCenterY = static_cast<double>((roiImage.cols / 2));
    while (j < selected_lines.size()) {
        ini = cv::Point(selected_lines[j][0], selected_lines[j][1]);
        fini = cv::Point(selected_lines[j][2], selected_lines[j][3]);

        // Condition to classify line as left side or right side
        if (slopes[j] > 0 && fini.x > imgCenterY && ini.x > imgCenterY) {
            right_lines.push_back(selected_lines[j]);
        } else if (slopes[j] < 0 && fini.x < imgCenterY && ini.x < imgCenterY) {
            left_lines.push_back(selected_lines[j]);
        }
        j++;
    }

    Lanes[0] = right_lines;
    Lanes[1] = left_lines;

    return Lanes;
}
