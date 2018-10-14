#include "../include/LaneDetector.hpp"

cv::Mat LaneDetector::houghTransform(cv::Mat edgeImage) {
	cv::Mat cdst;
	std::vector<cv::Vec4i> lines;
	// Detect Lines
	// cvtColor(edgeImage, cdst, CV_GRAY2BG);
	cdst = edgeImage;

	// cv::HoughLines(edgeImage, lines, 1, CV_PI / 180, 20, 1, 1);
	/*   std::cout << lines.size() << std::endl;
	 for (size_t i = 0; i < lines.size(); i++) {
	  float rho = lines[i][0], theta = lines[i][1];
	    cv::Point pt1, pt2;
	    double a = cos(theta), b = sin(theta);
	    double x0 = a * rho, y0 = b * rho;
	    pt1.x = cvRound(x0 + 1000 * (-b));
	    pt1.y = cvRound(y0 + 1000 * (a));
	    pt2.x = cvRound(x0 - 1000 * (-b));
	    pt2.y = cvRound(y0 - 1000 * (a));
	    line(cdst, pt1, pt2, cvScalar(0, 0, 255), 3, CV_AA);
	    //	std::cout << lines[i][0] << " and " << lines[i][1] << std::endl;
	}
	*/
	HoughLinesP(edgeImage, lines, 1, CV_PI / 180, 1, 10, 5);
	for (size_t i = 0; i < lines.size(); i++) {
		cv::Vec4i l = lines[i];
		line(cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
		     cv::Scalar(120, 120, 255), 2, CV_AA);
	}

	// imshow("source",edgeImage );
	imshow("detected lines", cdst);
	return cdst;
}
