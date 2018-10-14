/**
 * @file    main.cpp
 * @authors  Mayank Pathak and Bhargav Dandamudi
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
    for (int i = 10; i < 1010; ++i) {
	std::cout << "reading Frame: " << i << std::endl;
	cv::Mat testImage = LaneDetector.readFrame(i);
	cv::Mat copyTest = testImage.clone();

	// cv::Mat roiW = LaneDetector.roiMaskSelection(hsvW);

	cv::Mat edgedImage, coloredImage, coloredImageP;
	cv::Canny(testImage, edgedImage, 50, 200, 3);
	cv::Mat roiImage = LaneDetector.roiMaskSelection(edgedImage);
	cvtColor(roiImage, coloredImage, CV_GRAY2BGR);

	coloredImageP = coloredImage.clone();

	/*	// Probabilistic Hough Transform

		std::vector<cv::Vec4i> linesP;   // for HoughP
		cv::HoughLinesP(roiImage, linesP, 1, CV_PI / 180, 20, 20,
				30);   // HoughP
		for (size_t i = 0; i < linesP.size(); i++) {
		    cv::Vec4i l = linesP[i];
		    cv::line(copyTest, cv::Point(l[0], l[1]), cv::Point(l[2],
	   l[3]),
			     cv::Scalar(0, 0, 255), 2, CV_AA);
		}

		cv::imshow("source", copyTest);
		// cv::imshow("Hough lines", testImage);
		cv::imshow("Probabilistic Hough Lines", coloredImageP);
	*/
	cv::waitKey(-1);
    }

    cv::destroyAllWindows();
    return 0;
}
