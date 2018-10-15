FIND_PACKAGE( OpenCV REQUIRED )
add_executable(shell-app main.cpp LaneDetector.cpp readFrame.cpp
				 hsvThresholdY.cpp
                 houghTransform.cpp
                 lineFitting.cpp
                 roiMaskSelection.cpp
				 edgeDetector.cpp)
target_link_libraries( shell-app ${OpenCV_LIBS})
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
