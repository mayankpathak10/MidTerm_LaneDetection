#include "../include/LaneDetector.hpp"


cv::Mat LanePredictor::predictTurn( cv::Vec4d leftLines, cv::Vec4d rightLines, cv::Mat inputImage) {
	std::string output;	
	cv::Point vanishingPoint;
	double x11 = leftLines[0];
	double y11 = leftLines[1];
	double x21 = leftLines[2];
	double y21 = leftLines[3];
	double m1 = ((y21-y11)/(x21-x11));
    double x12 = rightLines[0];
	double y12 = rightLines[1];
	double x22 = rightLines[2];
	double y22 = rightLines[3];
	double m2 = ((y22-y12)/(x22-x12));


    vanishingPoint.x = ((y22-y11)+m1*x11-m2*x22)/(m1-m2);
    vanishingPoint.y = (m1*((y22-y11)-(m2*x22)+(m2*x11)))/(m1-m2) + y11;


    // std::cout<<"vanishing Point: "<<vanishingPoint.x<<","<<vanishingPoint.y<<std::endl;

    circle(inputImage, vanishingPoint, 1, cv::Scalar(0, 255, 0), 3, 8, 0);

    // imshow("Final Output",inputImage);

// inputImage.copyTo(output);
    if (vanishingPoint.x<288) {
    	std::string output = "Left Turn Ahead!";
    	cv::putText(inputImage, output, cv::Point(120, 200),   // Coordinates
        cv::FONT_HERSHEY_COMPLEX_SMALL,       // Font
        2.0,          // Scale. 2.0 = 2x bigger
        cv::Scalar(255, 0, 0),   // BGR Color
        1);  

    	return inputImage;
    }
    else if (vanishingPoint.x>315) {
    	std::string output = "Right Turn Ahead!";

        cv::putText(inputImage, output, cv::Point(120, 200),   // Coordinates
        cv::FONT_HERSHEY_COMPLEX_SMALL,       // Font
        2.0,          // Scale. 2.0 = 2x bigger
        cv::Scalar(255, 0, 0),   // BGR Color
        1);  


    	return inputImage;
    }


return inputImage;
}