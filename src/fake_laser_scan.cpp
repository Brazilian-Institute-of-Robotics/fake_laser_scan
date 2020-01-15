
// Copyright (c) 2019 Fake_Laser_Scan Authors.
// All rights reserved.

#include "gtest/gtest.h"
#include "fake_laser_scan/fake_laser_scan.h"


FakeLaserScan::FakeLaserScan() {
  laser_frequency = 10;
  samples_per_revolution = 400;
  current_scan_time = 0.0;
  range_distance = 2.0;
  scan.header.frame_id = "map";
  scan.angle_min = 0.0;
  scan.angle_max = 2 * pi;
  scan.angle_increment = 2 * pi / samples_per_revolution;
  scan.time_increment = (1 / laser_frequency) / (samples_per_revolution);
  scan.range_min = 0.5;
  scan.range_max = 6.0;
  count = 0;
}

void FakeLaserScan::fakeScanPublisher() {
  ros::NodeHandle n;
  ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scan", 50);
  while (ros::ok()) {
    current_scan_time = ros::Time::now().nsec;
    scan.header.stamp.sec = ros::Time::now().sec;
    scan.header.stamp.nsec = current_scan_time;
    scan.header.seq = count;
    scan.scan_time = current_scan_time - last_scan_time;
    scan.ranges.resize(samples_per_revolution);
    scan.intensities.resize(samples_per_revolution);
    for (int i = 0; i <samples_per_revolution ; i++) {
      scan.ranges[i] = range_distance;
      scan.intensities[i] = 20.0;
    }
    last_scan_time = ros::Time::now().nsec;
    scan_pub.publish(scan);
    ros::spinOnce();
    count++;
    ros::Rate r(10);
    r.sleep();
  }
}

FakeLaserScan::~FakeLaserScan() {
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "laser_scan_publisher");
  FakeLaserScan fakeLaserScan;
  fakeLaserScan.fakeScanPublisher();
  return 0;
}
