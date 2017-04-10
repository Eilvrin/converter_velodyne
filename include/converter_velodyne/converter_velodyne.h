#ifndef CONVERTER_VELODYNE_H
#define CONVERTER_VELODYNE_H

#include <string>

// ROS headers
#include <ros/ros.h>
#include <velodyne_msgs/VelodynePacket.h>
#include <velodyne_msgs/VelodyneScan.h>
#include <velodyne16/VelodynePacket.h>


class ConverterVelodyne
{

public:

  ConverterVelodyne(ros::NodeHandle node, ros::NodeHandle private_nh);

private:
  void convertScan(const velodyne_msgs::VelodyneScan::ConstPtr &scanMsg);
  ros::Subscriber velodyne_scan_;
  ros::Publisher velodyne16_packet_;

  std::string frame_id_;   // Frame_id for output velodyne16 packets
};

#endif // CONVERTER_VELODYNE_H