#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Joy.h"
#include <iostream>

#include "PUTM_DV_CAN_LIBRARY/Inc/putm_can_interface.hpp"

using namespace PUTM_CAN;

CAN can;

Apps_main frame = {
  .pedal_position=0,
  .counter=0,
  .position_diff=0,
  .device_state = Apps_states::Normal_operation
};

void joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  uint16_t max_val = 100;
  frame.pedal_position = -(max_val/2)*(joy->axes[4]-1);
  std::cout<<frame.pedal_position<<"\n";
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "putm_dv_traction_control_driver");

  ros::NodeHandle nh;
  ros::Subscriber joy_sub;
  joy_sub = nh.subscribe<sensor_msgs::Joy>("joy", 10, joyCallback);

  can.connect();
  ros::Rate r(100);
  while (ros::ok)
  {
    can.transmit(frame);
    frame.counter++;
    ros::spinOnce();
    r.sleep();
  }

}

