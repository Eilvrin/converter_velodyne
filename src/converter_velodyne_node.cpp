/*
 *  Copyright (C) 2017 University of Freiburg
 *  License: Modified BSD Software License Agreement
 */

#include <ros/ros.h>
#include "converter_velodyne/converter_velodyne.h"

/** Main node entry point. */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "converter_velodyne_node");
  ros::NodeHandle node;
  ros::NodeHandle private_nh("~");
  ConverterVelodyne conv(node, private_nh);
  // handle callbacks until shut down
  ros::spin();

  return 0;
}