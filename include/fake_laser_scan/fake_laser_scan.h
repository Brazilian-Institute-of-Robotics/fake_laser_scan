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

  void runFakeLaserScan();

  // ~FakeLaserScan();

 private:
  sensor_msgs::LaserScan scan_;
  ros::Time current_scan_time_;
  ros::Time last_scan_time_;

  float laser_frequency_;
  float samples_per_revolution_;
  float angular_size_;
  float range_distance_;
};

#endif  // FAKE_LASER_SCAN_FAKE_LASER_SCAN_H_
