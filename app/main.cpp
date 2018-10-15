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
    LanePredictor LanePredictor;
    int totalFrames;
    cv::VideoCapture frameCount("../Dataset/Dataset2.mp4");

    totalFrames = frameCount.get(CV_CAP_PROP_FRAME_COUNT);
    std::cout << "Total Frames" << totalFrames;
    for (int i = 10; i < 49510; ++i) {
        std::cout << "reading Frame: " << i << std::endl;

        cv::Mat frameP = LanePredictor.readFrame(i);
        cv::Mat hsvThresholdImage = LanePredictor.hsvThresholdY(frameP);
        cv::Mat edgesP = LanePredictor.edgeDetector(hsvThresholdImage);
        cv::Mat roiP = LanePredictor.roiMaskSelection(edgesP);

        std::vector<cv::Vec4i> linesP;
        HoughLinesP(roiP, linesP, 1, CV_PI / 180, 50, 50, 10);
        //        for (size_t i = 0; i < linesP.size(); i++) {
        //            cv::Vec4i l = linesP[i];
        //            line(frameP, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
        //                 cv::Scalar(0, 0, 255), 3, CV_AA);
        //        }
        //        imshow("yellow edges", frameP);

        cv::Mat testImage = LaneDetector.readFrame(i);
        cv::Mat copyTest = testImage.clone();
        cv::Mat edgedImage, coloredImage, coloredImageP;
        cv::Canny(testImage, edgedImage, 50, 200, 3);
        cv::Mat roiImage = LaneDetector.roiMaskSelection(edgedImage);
        // cvtColor(roiImage, coloredImage, CV_GRAY2BGR);

        std::vector<std::vector<cv::Vec4i> > allLanes =
            LaneDetector.houghTransform(roiImage);
        // cv::Vec4d leftLanes = allLanes[1];
        cv::Vec4d leftLanes = LaneDetector.lineFitting(allLanes[1]);
        cv::Vec4d rightLanes = LaneDetector.lineFitting(allLanes[0]);
        // cv::Vec4d yellowLanes = LaneDetector.lineFitting(linesP);

        std::cout << "Left Lane Points : "
                  << cv::Point(leftLanes[0], leftLanes[1]) << std::endl;
        line(copyTest, cv::Point(leftLanes[0], leftLanes[1]),
             cv::Point(leftLanes[2], leftLanes[3]), cv::Scalar(255, 255, 51), 3,
             CV_AA);
        line(copyTest, cv::Point(rightLanes[0], rightLanes[1]),
             cv::Point(rightLanes[2], rightLanes[3]), cv::Scalar(0, 255, 51), 3,
             CV_AA);
        // line(copyTest, cv::Point(yellowLanes[0], yellowLanes[1]),
        //  cv::Point(yellowLanes[2], yellowLanes[3]),
        // cv::Scalar(55, 255, 251), 3, CV_AA);

        imshow("results", copyTest);
        cv::waitKey(-1);
    }
    cv::destroyAllWindows();

    return 0;
}
