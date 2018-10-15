#include "../include/LaneDetector.hpp"

cv::Vec4d LaneDetector::lineFitting(std::vector<cv::Vec4i> lineVector, cv::Mat inputImage) {
    std::vector<cv::Point> allPoints;
    cv::Vec4d fitLine;
    cv::Point pt1, pt2;
    // std::cout<<"lineVector Size: " << lineVector.size() << std::endl;

    for (auto i : lineVector) {
        cv::Point ini = cv::Point(i[0], i[1]);
        cv::Point fini = cv::Point(i[2], i[3]);

        // std::cout<<"adding 1st p :"<<ini<<std::endl;
        // std::cout<<"adding 2nd p :"<<fini<<std::endl;
        allPoints.push_back(ini);
        allPoints.push_back(fini);
    }
    cv::fitLine(allPoints, fitLine, CV_DIST_L2, 0, 0.01, 0.01);

    

    double d = sqrt((double)fitLine[0] * fitLine[0] + (double)fitLine[1] * fitLine[1]);
    fitLine[0] /= d;
    fitLine[1] /= d;
    float t = (inputImage.cols + inputImage.rows);
    pt1.x = cvRound(fitLine[2] - fitLine[0] * t);
    pt1.y = cvRound(fitLine[3] - fitLine[1] * t);
    pt2.x = cvRound(fitLine[2] + fitLine[0] * t);
    pt2.y = cvRound(fitLine[3] + fitLine[1] * t);

    fitLine[0] = pt1.x;
    fitLine[1] = pt1.y;
    fitLine[2] = pt2.x;
    fitLine[3] = pt2.y;

    return fitLine;
}


    // lineSlope = fitline[1] / fitline[0];
    // lineConst = cv::Point(fitline[2], fitline[3]);

    // int ini_y = inputImage.rows;
    // int fin_y = 470;

    // double right_ini_x = ((ini_y - right_b.y) / right_m) + right_b.x;
    // double right_fin_x = ((fin_y - right_b.y) / right_m) + right_b.x;

    // output[0] = cv::Point(right_ini_x, ini_y);
    // output[1] = cv::Point(right_fin_x, fin_y);


    // std::cout<<"fitLine Points"<< pt1.x<<","<<pt1.y<<
    		// ","<<pt2.x<<","<<pt2.y<<std::endl;

    // line(inputImage, pt1,pt2, cv::Scalar(255, 255, 51), 3,
             // CV_AA);
   	
   	// imshow("results", inputImage);

