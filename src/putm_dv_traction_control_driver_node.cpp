#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Joy.h"

#include "PUTM_DV_CAN_LIBRARY_RAII/include/can_tx.hpp"

using namespace PUTM_CAN;

static DV_TC_control dv_tc_control_frame = {0};

void joyCallback(const sensor_msgs::Joy::ConstPtr &joy)
{
  const uint16_t max_val = 500;
  dv_tc_control_frame.set_current = -(max_val / 2) * (joy->axes[5] - 1);
  ROS_INFO("Pedal position: %d", dv_tc_control_frame.set_current);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "putm_dv_traction_control_driver");
  ros::NodeHandle nh;
  ROS_INFO("Starting the traction control driver node...");

  ros::Subscriber joy_sub;
  joy_sub = nh.subscribe<sensor_msgs::Joy>("joy", 1, joyCallback);

  try
  {
    CanTx can("can0");
    ros::Rate r(10);
    while (ros::ok)
    {
      can.transmit(dv_tc_control_frame);
      ros::spinOnce();
      r.sleep();
    }
  }
  catch (const std::runtime_error &e)
  {
    ROS_ERROR("Failed to configure or transmit to the CAN device. Are you sure it's connected and configured?");
    throw;
  }
}
