// Copyright (c) 2019 The MCCR Simulator Authors.
// All rights reserved.

#include <gtest/gtest.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>


class FakeLaserScan {
 /**
 * @brief Publish FakeLaserScan Topic for testing
 *
 */
 public:
   /**
   * @brief Constructor fakeLaserScan
   */
  FakeLaserScan();
  /**
   * @brief Destructor fakeLaserScan
   */
  sensor_msgs::LaserScan fakeScanSet(int argc, char **argv);

  void fakeScanPublisher(ros::Publisher scan_pub, sensor_msgs::LaserScan scan);

  ~FakeLaserScan();

 private:
  sensor_msgs::LaserScan scan;
  const float pi = 3.14159265359;
  float laser_frequency;
  float samples_per_revolution;
  float angle_min;
  float angle_max;
  float angle_increment;
  float time_increment;
  float scan_time;
  float range_min;
  float range_max;
  float ranges[];
  float range_distance;
  float intensities[];
  float last_scan_time;
  float current_scan_time;
};
