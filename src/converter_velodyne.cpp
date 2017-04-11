#include "converter_velodyne/converter_velodyne.h"
namespace converter_velodyne
{

 ConverterVelodyne::ConverterVelodyne(ros::NodeHandle node, ros::NodeHandle private_nh)
  {
    // The frame for velodyne16
    private_nh.param("frame_id", frame_id_, std::string(""));
    //subscribe to Velodyne scans
    velodyne_scan_ =
      node.subscribe("velodyne_packets", 10,
                     &ConverterVelodyne::convertScan, (ConverterVelodyne *) this,
                     ros::TransportHints().tcpNoDelay(true));

    velodyne16_packet_ = node.advertise<velodyne16::VelodynePacket>("velodyne16/packets", 500);
  }

  /** @brief Callback for velodyne scan messages. */
  void ConverterVelodyne::convertScan(const velodyne_msgs::VelodyneScan::ConstPtr &scanMsg)
  { 
    if (frame_id_ == "")
      frame_id_ =  scanMsg->header.frame_id;

    for (int i = 0; i < scanMsg->packets.size(); ++i)
    {
      velodyne16::VelodynePacketPtr pkt (new velodyne16::VelodynePacket);
      pkt->header.stamp = scanMsg->packets[i].stamp;
      pkt->header.frame_id = frame_id_;
      pkt->data = scanMsg->packets[i].data;
      velodyne16_packet_.publish(pkt);
    }
  }

} // converter_velodyne