// Author: Nicolas Gallardo
// Date:7/30/17
// This header file defines the classes and functions required to produce and publish fake laser scans
// a as ROS LaserScan message

#ifndef FAKE_LASER_SCAN_FAKE_SCAN_NODE_H_
#define FAKE_LASER_SCAN_FAKE_SCAN_NODE_H_

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

// Global variables
#define g_PI 3.14159265359
#define g_SAMPLES_PER_REV 400
#define g_LASER_FREQ 10

class FakeLaserScan {
 public:
  FakeLaserScan();
  void begin(int argc, char **argv);
  void fakeScanPublisher();

 private:
  sensor_msgs::LaserScan scan;
  float angle_min;
  float angle_max;
  float angle_increment;
  float time_increment;
  float scan_time;
  float range_min;
  float range_max;
  float ranges[];
  float intensities[];
  float last_scan_time;
  float current_scan_time;
};

#endif  // FAKE_LASER_SCAN_FAKE_SCAN_NODE_H_
