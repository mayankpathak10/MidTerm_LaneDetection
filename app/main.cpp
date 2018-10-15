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
    cv::Vec4d dummyLanes;
    cv::Vec4d dummyLLanes;
    cv::VideoCapture frameCount("../Dataset/Dataset2.mp4");

    totalFrames = frameCount.get(CV_CAP_PROP_FRAME_COUNT);
    std::cout << "Total Frames" << totalFrames;
    for (int i = 1000; i < 4950; ++i) {
        std::cout << "reading Frame: " << i << std::endl;

        //        for (size_t i = 0; i < linesP.size(); i++) {
        //            cv::Vec4i l = linesP[i];
        //            line(frameP, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
        //                 cv::Scalar(0, 0, 255), 3, CV_AA);
        //        }
        //        imshow("yellow edges", frameP);

        cv::Mat testImage = LaneDetector.readFrame(i);
        cv::Mat copyTest = testImage.clone();
        cv::Vec4d rightLanes;
        cv::Vec4d leftLanes;
        cv::Mat edgedImage, coloredImage, coloredImageP;
        cv::Canny(testImage, edgedImage, 50, 200, 3);
        cv::Mat roiImage = LaneDetector.roiMaskSelection(edgedImage);
        // cvtColor(roiImage, coloredImage, CV_GRAY2BGR);

        std::vector<std::vector<cv::Vec4i> > allLanes =
            LaneDetector.houghTransform(roiImage);
        // cv::Vec4d leftLanes = allLanes[1];
        // cv::Vec4d leftLanes = LaneDetector.lineFitting(allLanes[1],
        // copyTest);
        std::cout << "right Lane size: " << allLanes[0].size() << std::endl;
        // cv::Vec4d rightLanes;
        if (allLanes[0].size() > 0) {
            rightLanes = LaneDetector.lineFitting(allLanes[0], copyTest);
            dummyLanes = rightLanes;
        } else {
            rightLanes = dummyLanes;
        }

        if (allLanes[1].size() > 0) {
            leftLanes = LaneDetector.lineFitting(allLanes[1], copyTest);
            dummyLLanes = leftLanes;
        } else {
            leftLanes = dummyLLanes;
        }

        // else {
        //     continue;
        // }
        cv::Vec4d yellowLanes = LanePredictor.detectYellow(copyTest);
        std::cout << "\n\nYellow LanePoints: " << yellowLanes[0] << ","
                  << yellowLanes[1] << ",and " << yellowLanes[2] << ","
                  << yellowLanes[3] << std::endl;

        // line(copyTest, cv::Point(yellowLanes[0], yellowLanes[1]),
        //      cv::Point(yellowLanes[2], yellowLanes[3]), cv::Scalar(255, 255,
        //      51), 3,
        //      CV_AA);
        // line(copyTest, cv::Point(rightLanes[0], rightLanes[1]),
        //     cv::Point(rightLanes[2], rightLanes[3]), cv::Scalar(0, 255, 51),
        //     3,
        //     CV_AA);
        //    line(copyTest, cv::Point(leftLanes[0], leftLanes[1]),
        //     cv::Point(leftLanes[2], leftLanes[3]), cv::Scalar(0, 255, 51), 3,
        //     CV_AA);

        cv::Mat output =
            LanePredictor.plotPolygon(copyTest, leftLanes, rightLanes);

        std::string laneIndicator =
            LanePredictor.wrongLanePredictor(yellowLanes);
        std::cout << laneIndicator << std::endl;
        if (laneIndicator == ("Wrong Lane!!")) {
            cv::putText(copyTest, laneIndicator,
                        cv::Point(120, 100),              // Coordinates
                        cv::FONT_HERSHEY_COMPLEX_SMALL,   // Font
                        2.0,                     // Scale. 2.0 = 2x bigger
                        cv::Scalar(0, 0, 255),   // BGR Color
                        1);
        } else {
            cv::putText(copyTest, laneIndicator,
                        cv::Point(120, 50),               // Coordinates
                        cv::FONT_HERSHEY_COMPLEX_SMALL,   // Font
                        2.0,                         // Scale. 2.0 = 2x bigger
                        cv::Scalar(255, 255, 255),   // BGR Color
                        1);

        }   // Anti-alias (Optional)

        // imshow("results", output);
        // imshow("edg",copyTest);

        cv::Mat finalOutput =
            LanePredictor.predictTurn(leftLanes, rightLanes, copyTest);

        imshow("Final ", finalOutput);
        cv::waitKey(-1);
    }
    cv::destroyAllWindows();

    return 0;
}
