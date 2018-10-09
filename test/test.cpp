#include <gtest/gtest.h>

/**
 * @brief To test if the lanes are detected in the given 
 * Frame.
 */
int LaneTesting(int framenumber) {


}

/**
 *@brief Test case to test if lane is detected.
 */
TEST(LaneTest, lane_detected) {
  EXPECT_EQ(testing_lanes(10), 0);
}

/**
 *@brief Test cases to test if lane is detected and if the lane is going straight.
 */
TEST(LaneTest, no_turn) {
  EXPECT_EQ(testing_lanes(600), 0);
}

/**
 *@brief Test cases to test if lane is detected and if the lane is turning right.
 */
TEST(LaneTest, right_turn) {
  EXPECT_EQ(testing_lanes(1500), 0);
}

/**
 *@brief Test cases to test if lane is detected and if the lane is turning left.
 */
TEST(LaneTest, right_left) {
  EXPECT_EQ(testing_lanes(2300), 0);
}