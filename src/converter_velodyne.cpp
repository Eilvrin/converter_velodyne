#include "converter_velodyne/converter_velodyne.h"

 ConverterVelodyne::ConverterVelodyne(ros::NodeHandle node, ros::NodeHandle private_nh)
  {
    // The velodyne16 coordinate frame
    private_nh.param("frame_id", frame_id_, std::string("velodyne16"));
    // Whether to use frame_id for velodyne16 pkt from velodyne pkt 
    private_nh.param("use_velodyne_frame_id", velodyne_frame_id_, false);
    // Whether the timestame of velodyne packets is set to the end time of packet creation
    // Velodyne16 assumes another way - the beginning of packet creation
    private_nh.param("end_of_pkt_timestamp", end_of_pkt_timestamp_, false);
    //subscribe to Velodyne scans
    velodyne_scan_ =
      node.subscribe("velodyne_packets", 10,
                     &ConverterVelodyne::convertScan, (ConverterVelodyne *) this,
                     ros::TransportHints().tcpNoDelay(true));

    velodyne16_packet_ = node.advertise<converter_velodyne::Velodyne16Packet>("velodyne16/packets", 500);
  }

  /** @brief Callback for velodyne scan messages. */
  void ConverterVelodyne::convertScan(const converter_velodyne::VelodyneScan::ConstPtr &scanMsg)
  { 
    if (velodyne_frame_id_)
      frame_id_ =  scanMsg->header.frame_id;

    for (int i = 0; i < scanMsg->packets.size(); ++i)
    {
      converter_velodyne::Velodyne16PacketPtr pkt (new converter_velodyne::Velodyne16Packet);
      if (end_of_pkt_timestamp_)
        pkt->header.stamp = scanMsg->packets[i].stamp - ros::Duration(1327.104 * 1.0e-6);
      else
        pkt->header.stamp = scanMsg->packets[i].stamp;
      pkt->header.frame_id = frame_id_;
      pkt->data = scanMsg->packets[i].data;
      velodyne16_packet_.publish(pkt);
    }
  }