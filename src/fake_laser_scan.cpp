// Copyright (c) 2019 Fake_Laser_Scan Authors.
// All rights reserved.

#include "fake_laser_scan/fake_laser_scan.h"

FakeLaserScan::FakeLaserScan() {
  ros::NodeHandle private_n("~");
  // Define laser scan parameters
  private_n.param<float>("laser_frequency", laser_frequency, 10.0);
  private_n.param<float>("samples_per_revolution", samples_per_revolution, 400.0);
  private_n.param<float>("range_distance", range_distance, 3.0);
  private_n.param<float>("angular_size", angular_size, M_PI);
  private_n.param<float>("range_min", scan.range_min, 0.0);
  private_n.param<float>("range_max", scan.range_max, 20.0);
  private_n.param<float>("angular_size", angular_size, M_PI);

  private_n.param<std::string>("frame_id", scan.header.frame_id, std::string("odom"));

  scan.angle_min = -angular_size/2;
  scan.angle_max =  angular_size/2;
  scan.angle_increment = angular_size / samples_per_revolution;
  scan.time_increment = (1 / laser_frequency) / (samples_per_revolution);
}

void FakeLaserScan::runFakeLaserScan() {
  ros::NodeHandle n;
  // Scan Publisher.
  ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scan", 50);
  ros::Rate r(10);
  while (ros::ok()) {
    // Set Laser scan message.
    current_scan_time = ros::Time::now();
    scan.header.stamp.sec = current_scan_time.sec;
    scan.header.stamp.nsec = current_scan_time.nsec;
    scan.scan_time = (current_scan_time - last_scan_time).toSec();
    scan.ranges.resize(samples_per_revolution);
    scan.intensities.resize(samples_per_revolution);
    for (int i = 0; i < samples_per_revolution ; i++) {
      scan.ranges[i] = range_distance;
      scan.intensities[i] = 2.0;
    }
    last_scan_time = current_scan_time;
    scan_pub.publish(scan);
    ros::spinOnce();
    r.sleep();
  }
}

FakeLaserScan::~FakeLaserScan() {
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "laser_scan_publisher");
  FakeLaserScan fakeLaserScan;
  fakeLaserScan.runFakeLaserScan();
  return 0;
}
