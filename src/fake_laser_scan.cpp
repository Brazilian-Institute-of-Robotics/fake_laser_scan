
// Copyright (c) 2019 Fake_Laser_Scan Authors.
// All rights reserved.

#include "fake_laser_scan/fake_laser_scan.h"


FakeLaserScan::FakeLaserScan() {
  n.param<float>("laser_frequency", laser_frequency, 10.0);
  n.param<float>("samples_per_revolution", samples_per_revolution, 400.0);
  n.param<float>("range_distance", range_distance, 3.0);
  n.param<float>("angular_size", angular_size, pi);
  n.param<float>("range_min", scan.range_min, 0.0);
  n.param<float>("range_max", scan.range_max, 20.0);
  n.param<float>("angular_size", angular_size, pi);

  n.param<std::string>("frame_id", scan.header.frame_id, "map");

  scan.angle_min = -angular_size/2;
  scan.angle_max =  angular_size/2;
  scan.angle_increment = angular_size / samples_per_revolution;
  scan.time_increment = (1 / laser_frequency) / (samples_per_revolution);

  current_scan_time = 0.0;
  count = 0;
}

void FakeLaserScan::fakeScanPublisher() {
  ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scan", 50);
  ros::Rate r(10);
  while (ros::ok()) {
    current_scan_time = ros::Time::now().sec;
    scan.header.stamp.sec = ros::Time::now().sec;
    scan.header.stamp.nsec = ros::Time::now().nsec;
    scan.header.seq = count;
    scan.scan_time = current_scan_time - last_scan_time;
    scan.ranges.resize(samples_per_revolution);
    scan.intensities.resize(samples_per_revolution);
    for (int i = 0; i <samples_per_revolution ; i++) {
      scan.ranges[i] = range_distance;
      scan.intensities[i] = 2.0;
    }
    last_scan_time = ros::Time::now().sec;
    scan_pub.publish(scan);
    ros::spinOnce();
    count++;
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
