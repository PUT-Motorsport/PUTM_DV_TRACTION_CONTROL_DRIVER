#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Joy.h"

#include "PUTM_DV_CAN_LIBRARY_RAII/include/can_tx.hpp"

using namespace PUTM_CAN;

static Apps_main apps_main_frame = {0};

void joyCallback(const sensor_msgs::Joy::ConstPtr &joy)
{
  const uint16_t max_val = 100;
  apps_main_frame.pedal_position = -(max_val / 2) * (joy->axes[4] - 1);
  ROS_INFO("Pedal position: %d", apps_main_frame.pedal_position);
}

int main(int argc, char **argv)
{
  try
  {
    CanTx can("can0");
    ros::init(argc, argv, "putm_dv_traction_control_driver");
    ros::NodeHandle nh;
    ros::Subscriber joy_sub;
    joy_sub = nh.subscribe<sensor_msgs::Joy>("joy", 10, joyCallback);

    ros::Rate r(100);
    while (ros::ok)
    {
      can.transmit(apps_main_frame);
      apps_main_frame.counter++;
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
