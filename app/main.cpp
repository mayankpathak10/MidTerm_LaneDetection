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

    int frame_width = frameCount.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = frameCount.get(CV_CAP_PROP_FRAME_HEIGHT);
    cv::VideoWriter video("../Output/LaneDetector.avi",
                          CV_FOURCC('M', 'J', 'P', 'G'), 10,
                          cv::Size(frame_width, frame_height));

    totalFrames = frameCount.get(CV_CAP_PROP_FRAME_COUNT);
    std::cout << "Total Frames" << totalFrames;
    for (int i = 1200; i < 4950; ++i) {
        std::cout << "reading Frame: " << i << std::endl;

        cv::Mat testImage = LaneDetector.readFrame(i);
        cv::Mat copyTest = testImage.clone();
        cv::Vec4d rightLanes;
        cv::Vec4d leftLanes;
        cv::Mat edgedImage, coloredImage, coloredImageP;
        cv::Canny(testImage, edgedImage, 50, 200, 3);
        cv::Mat roiImage = LaneDetector.roiMaskSelection(edgedImage);

        std::vector<std::vector<cv::Vec4i> > allLanes =
            LaneDetector.houghTransform(roiImage);
        std::cout << "right Lane size: " << allLanes[0].size() << std::endl;

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

        cv::Vec4d yellowLanes = LanePredictor.detectYellow(copyTest);
        std::cout << "\n\nYellow LanePoints: " << yellowLanes[0] << ","
                  << yellowLanes[1] << ",and " << yellowLanes[2] << ","
                  << yellowLanes[3] << std::endl;

        cv::Mat output =
            LanePredictor.plotPolygon(copyTest, leftLanes, rightLanes);

        std::string laneIndicator =
            LanePredictor.wrongLanePredictor(yellowLanes);
        std::cout << laneIndicator << std::endl;
        if (laneIndicator == ("Wrong Lane!!")) {
            cv::putText(copyTest, laneIndicator,
                        cv::Point(180, 200),      // Coordinates
                        cv::FONT_HERSHEY_PLAIN,   // Font
                        2,                        // Scale. 2.0 = 2x bigger
                        cv::Scalar(0, 0, 255),    // BGR Color
                        2);
        } else {
            cv::putText(copyTest, laneIndicator,
                        cv::Point(210, 430),        // Coordinates
                        cv::FONT_HERSHEY_SIMPLEX,   // Font
                        0.75,                       // Scale. 2.0 = 2x bigger
                        cv::Scalar(102, 50, 0),     // BGR Color
                        2);

        }   // Anti-alias (Optional)

        cv::Mat finalOutput =
            LanePredictor.predictTurn(leftLanes, rightLanes, copyTest);

        cv::imshow("Frame", finalOutput);
        video.write(finalOutput);
        cv::waitKey(1);
    }

    // When everything done, release the video capture and write object
    video.release();

    // Closes all the windows
    cv::destroyAllWindows();

    return 0;
}
