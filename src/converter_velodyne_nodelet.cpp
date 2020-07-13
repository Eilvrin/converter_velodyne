/*
 *  Copyright (C) 2017 University of Freiburg
 *  License: Modified BSD Software License Agreement
 */

#include <ros/ros.h>
#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>

#include "converter_velodyne/converter_velodyne.h"

namespace converter_velodyne
{

  class ConverterVelodyneNodelet: public nodelet::Nodelet
  {
  public:

    ConverterVelodyneNodelet() {}
    ~ConverterVelodyneNodelet() {}

  private:

    virtual void onInit();
    boost::shared_ptr<ConverterVelodyne> conv_vel_;
  };

  /** @brief Nodelet initialization. */
  void ConverterVelodyneNodelet::onInit()
  {
    conv_vel_.reset(new ConverterVelodyne(getNodeHandle(), getPrivateNodeHandle()));
  }

} // converter_velodyne

// Register this plugin with pluginlib.
//
// parameters: package, class name, class type, base class type
PLUGINLIB_EXPORT_CLASS(converter_velodyne::ConverterVelodyneNodelet, nodelet::Nodelet)
