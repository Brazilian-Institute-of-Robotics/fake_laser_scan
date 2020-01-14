#include "gtest/gtest.h"
#include "fake_laser_scan/fake_laser_scan.h"


FakeLaserScan::FakeLaserScan() {
  laser_frequency = 10;
  samples_per_revolution = 400;
  current_scan_time = 0.0;
  range_distance = 7.0;
}

sensor_msgs::LaserScan FakeLaserScan::fakeScanSet(int argc, char **argv) {
  ros::init(argc, argv, "laser_scan_publisher");
  ros::NodeHandle n;
  ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scan", 50);

  scan.header.frame_id = "map";
  scan.angle_min = 0.0;
  scan.angle_max = 2 * pi;
  scan.angle_increment = 2 * pi / samples_per_revolution;
  scan.time_increment = (1 / laser_frequency) / (samples_per_revolution);
  scan.range_min = 0.5;
  scan.range_max = 6.0;
  for (int i = 0; i < samples_per_revolution ; i++) {
    scan.ranges[i] = range_distance;
  }
  scan.intensities[samples_per_revolution] = 0.0;
  ros::Rate r(10);
  r.sleep();
  return scan;
}

void FakeLaserScan::fakeScanPublisher(ros::Publisher scan_pub, sensor_msgs::LaserScan scan) {
  current_scan_time = ros::Time::now().nsec;

  scan.scan_time = current_scan_time - last_scan_time;
  scan.ranges.resize(samples_per_revolution);
  scan.intensities.resize(samples_per_revolution);
  for (int i = 0; i <samples_per_revolution ; i++) {
    scan.ranges[i] = ranges[i];
    scan.intensities[i] = intensities[i];
  }
  last_scan_time = ros::Time::now().nsec;
  scan_pub.publish(scan);
}
