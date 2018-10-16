cmake_minimum_required(VERSION 2.6)
set(GTEST_SHUFFLE 1)
FIND_PACKAGE( OpenCV REQUIRED)
#find_package(GTest REQUIRED)
FIND_PACKAGE(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

add_executable(lane-test main.cpp test.cpp)

target_include_directories(lane-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(lane-test PUBLIC ${OpenCV_LIBS} ${GTEST_LIBRARIES} gtest)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIRS}
)
