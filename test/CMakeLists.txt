cmake_minimum_required(VERSION 2.6)
set(GTEST_SHUFFLE 1)
FIND_PACKAGE( OpenCV REQUIRED)
#find_package(GTest REQUIRED)
#FIND_PACKAGE(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

add_executable( lane-test 
		mainTest.cpp 
		test.cpp 
#		../include/LaneDetector.hpp
                ../app/readFrame.cpp 
		../app/main.cpp 
		../app/hsvThresholdY.cpp
                ../app/houghTransform.cpp
                ../app/lineFitting.cpp
                ../app/roiMaskSelection.cpp
	        ../app/detectYellow.cpp
		../app/plotPolygon.cpp
	        ../app/wrongLanePredictor.cpp
		../app/predictTurn.cpp
		../app/edgeDetector.cpp

)

target_include_directories(lane-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(lane-test PUBLIC gtest ${OpenCV_LIBS}) # ${GTEST_LIBRARIES}

include_directories(
    ${CMAKE_SOURCE_DIR}/include
 #   ${GTEST_INCLUDE_DIRS}
)
