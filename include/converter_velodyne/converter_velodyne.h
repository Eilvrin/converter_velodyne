#ifndef CONVERTER_VELODYNE_H
#define CONVERTER_VELODYNE_H

#include <string>

// ROS headers
#include <ros/ros.h>
#include <converter_velodyne/VelodynePacket.h>
#include <converter_velodyne/VelodyneScan.h>
#include <converter_velodyne/Velodyne16Packet.h>


class ConverterVelodyne
{

public:

  ConverterVelodyne(ros::NodeHandle node, ros::NodeHandle private_nh);

private:
  void convertScan(const converter_velodyne::VelodyneScan::ConstPtr &scanMsg);
  ros::Subscriber velodyne_scan_;
  ros::Publisher velodyne16_packet_;

  std::string frame_id_;   // Frame_id for output velodyne16 packets
  bool velodyne_frame_id_; // Whether to use the initial velodyne frame for the velodyne16 packets
  bool end_of_pkt_timestamp_; //whether or not for the velodyne the timestamp was set to the end of packet collection
};

#endif // CONVERTER_VELODYNE_H