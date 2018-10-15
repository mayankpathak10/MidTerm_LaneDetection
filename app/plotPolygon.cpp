#include "../include/LaneDetector.hpp"


cv::Mat LanePredictor::plotPolygon(cv::Mat inputImage, cv::Vec4d yellowLanes, cv::Vec4d whiteLanes) {

	cv::Mat output;
	inputImage.copyTo(output);
	double ylower = 480;
	double yupper = 360;
	double x11 = yellowLanes[0];
	double y11 = yellowLanes[1];
	double x21 = yellowLanes[2];
	double y21 = yellowLanes[3];
	double slope1 = ((y21-y11)/(x21-x11));
    double x12 = whiteLanes[0];
	double y12 = whiteLanes[1];
	double x22 = whiteLanes[2];
	double y22 = whiteLanes[3];
	double slope2 = ((y22-y12)/(x22-x12));
	cv::Point upperWhite;
	cv::Point lowerWhite;
	cv::Point upperYellow;
	cv::Point lowerYellow;

	upperWhite.y = upperYellow.y = yupper;
	lowerWhite.y = lowerYellow.y = ylower;

	upperYellow.x = x11 + (yupper-y11)/slope1;
	lowerYellow.x = x11 + (ylower-y11)/slope1;





	upperWhite.x = x12 + (yupper-y12)/slope2;
	lowerWhite.x = x12 + (ylower-y12)/slope2;


	cv::Point pts[4] = {lowerYellow,upperYellow,
                        upperWhite, lowerWhite};

    std::cout<<"pts"<<pts[2]<<","<<pts[3]<<std::endl;

    cv::fillConvexPoly(output,pts,4, cv::Scalar(0, 0, 255), CV_AA);
    cv::addWeighted(output, 0.3, inputImage, 1.0 - 0.3, 0, inputImage);




	return output;
}
