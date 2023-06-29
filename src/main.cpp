#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Joy.h"
#include <iostream>

#include "PUTM_DV_CAN_LIBRARY_MULTIPLE_SOCKETS/include/can_tx.hpp"

using namespace PUTM_CAN;

static Apps_main apps_main_frame = {0};

void joyCallback(const sensor_msgs::Joy::ConstPtr &joy)
{
  uint16_t max_val = 100;
  frame.pedal_position = -(max_val / 2) * (joy->axes[4] - 1);
  std::cout << frame.pedal_position << "\n";
}

int main(int argc, char **argv)
{
  CanTx can("slcan0");
  ros::init(argc, argv, "putm_dv_traction_control_driver");
  ros::NodeHandle nh;
  ros::Subscriber joy_sub;
  joy_sub = nh.subscribe<sensor_msgs::Joy>("joy", 10, joyCallback);
  
  ros::Rate r(100);
  while (ros::ok)
  {
    can.transmit(apps_main_frame);
    frame.counter++;
    ros::spinOnce();
    r.sleep();
  }
}
