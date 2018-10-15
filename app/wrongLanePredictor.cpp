#include "../include/LaneDetector.hpp"

std::string LanePredictor::wrongLanePredictor(cv::Vec4d yellowLine) {

	double ylower = 460;
	std::string output = "x";
	double x11 = yellowLine[0];
	double y11 = yellowLine[1];
	double x21 = yellowLine[2];
	double y21 = yellowLine[3];
    double slope1 = ((y21-y11)/(x21-x11));

   	cv::Point lowerYellow;
	lowerYellow.x = x11 + (ylower-y11)/slope1;

	if (lowerYellow.x > 320) {
		std::string output = "Wrong Lane!!";
		return output;
	}
	else {
		std::string output = "Stay on this Lane!";
		return output;
	}

std::cout<<"Predicted Lane :"<< output<<std::endl;
std::cout<<"LowerX was : "<< lowerYellow.x<<std::endl;
return output;
}