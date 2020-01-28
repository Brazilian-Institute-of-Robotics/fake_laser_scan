#ifndef FAKE_LASER_SCAN_FAKE_LASER_SCAN_H_
#define FAKE_LASER_SCAN_FAKE_LASER_SCAN_H_

// Copyright (c) 2019 The MCCR Simulator Authors.
// All rights reserved.

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
  ~FakeLaserScan();

  void fakeScanPublisher();

  // ~FakeLaserScan();

 public:
  sensor_msgs::LaserScan scan;
  ros::Publisher scan_pub;
  float laser_frequency;
  float samples_per_revolution;
  float angular_size;
  float range_distance;
  float last_scan_time;
  float current_scan_time;
  int count;
};

#endif  // FAKE_LASER_SCAN_FAKE_LASER_SCAN_H_
