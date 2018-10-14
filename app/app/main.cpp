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
		std::cout<<"reading Frame: "<< i << std::endl;
		cv::Mat testImage = LaneDetector.readFrame(i);
		cv::Mat copytest = testImage.clone();
		// std::vector<double> leftlines;
		// std::vector<double> rightlines;

		// cv::Mat hsvY = LaneDetector.hsvThresholdY(testImage);
		// cv::Mat hsvW = LaneDetector.hsvThresholdW(testImage);

		
		// cv::Mat roiW = LaneDetector.roiMaskSelection(hsvW);

		cv::Mat edgedImage, coloredImage, coloredImageP;
    	cv::Canny(testImage, edgedImage, 50, 200, 3);
    	cv::Mat roiImage = LaneDetector.roiMaskSelection(edgedImage);
		cvtColor(roiImage, coloredImage, CV_GRAY2BGR);

		coloredImageP = coloredImage.clone();

	// Probabilistic Hough Transform

		std::vector<cv::Vec4i> linesP;   // for HoughP
		cv::HoughLinesP(edgedImage, linesP, 1, CV_PI / 180, 20, 20, 30 );  // HoughP
		for ( size_t i = 0; i < linesP.size(); i++ ) {
			cv::Vec4i l = linesP[i];
			cv::line( copytest, cv::Point(l[0], l[1]), 
				cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 2, CV_AA);
		}


	// Standard Hough Line Transform

    // std::vector<cv::Vec2f> lines; // will hold the results of the detection
    // HoughLines(edgedImage, lines, 1, CV_PI/180, 30, 20, 10 ); // runs the actual detection
    // // Draw the lines
    // for( size_t i = 0; i < lines.size(); i++ )
    // {
    //     float theta = lines[i][1];

    //     // line( coloredImage, pt1, pt2, cv::Scalar(120,120,255), 3, CV_AA);


    //     if( CV_PI/180*110 < theta && CV_PI/180*130 > theta) { 
    //     	float rho = lines[i][0];
    //     	cv::Point pt1, pt2;
	   //      double a = cos(theta), b = sin(theta);
	   //      double x0 = a*rho, y0 = b*rho;
	   //      pt1.x = cvRound(x0 + 1000*(-b));
	   //      pt1.y = cvRound(y0 + 1000*(a));
	   //      pt2.x = cvRound(x0 - 1000*(-b));
	   //      pt2.y = cvRound(y0 - 1000*(a));
	   //      line( testImage, pt1, pt2, cv::Scalar(0,0,255), 3, CV_AA);

    // 	}


    // 	if( CV_PI/180*20 < theta && CV_PI/180*60 > theta) {
    // 		float rho = lines[i][0]; 
	   //      cv::Point pt1, pt2;
	   //      double a = cos(theta), b = sin(theta);
	   //      double x0 = a*rho, y0 = b*rho;
	   //      pt1.x = cvRound(x0 + 1000*(-b));
	   //      pt1.y = cvRound(y0 + 1000*(a));
	   //      pt2.x = cvRound(x0 - 1000*(-b));
	   //      pt2.y = cvRound(y0 - 1000*(a));
	   //      line( testImage, pt1, pt2, cv::Scalar(51,255,255), 3, CV_AA);
    // 	}
    // }



		cv::imshow("source", copytest);
		// cv::imshow("Hough lines", testImage);
		cv::imshow("Probabilistic Hough Lines", coloredImageP);



		// cv::Mat roi = roiW + roiY;
		// cv::putText(roi, std::to_string(i), cv::Point(5, 205),   // Coordinates
		//             cv::FONT_HERSHEY_COMPLEX_SMALL,		 // Font
		//             2.0,			 // Scale. 2.0 = 2x bigger
		//             cv::Scalar(255, 255, 255),   // BGR Color
		//             1);				 // Anti-alias (Optional)

		// cv::Mat morphImage = LaneDetector.morph(roi);
		// cv::Mat edgedImage = LaneDetector.edgeDetector(morphImage);
		// cv::Mat linedImage = LaneDetector.houghTransform(edgedImage);
		// cv::imshow("frame", testImage);
		// cv::imshow("edges", edgedImage);

		// cv::imshow("lined", linedImage);
		cv::waitKey(-1);

		// Press  ESC on keyboard to  exit
		// char c = (char)cv::waitKey(1);
		// if( c == 27 ) 
		//   break;

	}

	cv::destroyAllWindows();
	return 0;
}
