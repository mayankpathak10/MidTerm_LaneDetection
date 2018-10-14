#include "../include/LaneDetector.hpp"

// Probabilistic Hough Transform

std::vector<cv::Vec4i> linesP;					 // for HoughP
cv::HoughLinesP(roiImage, linesP, 1, CV_PI / 180, 20, 20, 30);   // HoughP
for (size_t i = 0; i < linesP.size(); i++) {
    cv::Vec4i l = linesP[i];
    cv::line(copyTest, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
	     cv::Scalar(0, 0, 255), 2, CV_AA);
}

cv::imshow("source", copyTest);
// cv::imshow("Hough lines", testImage);
cv::imshow("Probabilistic Hough Lines", coloredImageP);
