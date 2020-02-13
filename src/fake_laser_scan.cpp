// Copyright (c) 2019 Fake_Laser_Scan Authors.
// All rights reserved.

#include "fake_laser_scan/fake_laser_scan.h"

FakeLaserScan::FakeLaserScan() {
  ros::NodeHandle private_n("~");
  // Define laser scan_ parameters
  private_n.param<float>("laser_frequency", laser_frequency_, 10.0);
  private_n.param<float>("samples_per_revolution", samples_per_revolution_, 400.0);
  private_n.param<float>("range_distance", range_distance_, 3.0);
  private_n.param<float>("range_min", scan_.range_min, 0.0);
  private_n.param<float>("range_max", scan_.range_max, 20.0);
  private_n.param<float>("angular_size", angular_size_, M_PI);

  private_n.param<std::string>("frame_id", scan_.header.frame_id, std::string("odom"));

  scan_.angle_min = -angular_size_/2;
  scan_.angle_max =  angular_size_/2;
  scan_.angle_increment = angular_size_ / samples_per_revolution_;
  scan_.time_increment = (1 / laser_frequency_) / (samples_per_revolution_);
}

void FakeLaserScan::runFakeLaserScan() {
  ros::NodeHandle n;
  // scan_ Publisher.
  ros::Publisher scan_pub_ = n.advertise<sensor_msgs::LaserScan>("scan", 50);
  ros::Rate r(10);
  while (ros::ok()) {
    // Set Laser scan_ message.
    current_scan_time_ = ros::Time::now();
    scan_.header.stamp.sec = current_scan_time_.sec;
    scan_.header.stamp.nsec = current_scan_time_.nsec;
    scan_.scan_time = (current_scan_time_ - last_scan_time_).toSec();
    scan_.ranges.resize(samples_per_revolution_);
    scan_.intensities.resize(samples_per_revolution_);
    for (int i = 0; i < samples_per_revolution_ ; i++) {
      scan_.ranges[i] = range_distance_;
      scan_.intensities[i] = 2.0;
    }
    last_scan_time_ = current_scan_time_;
    scan_pub_.publish(scan_);
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
