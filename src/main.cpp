#include "ros/ros.h"
#include "std_msgs/String.h"
#include "PUTM_DV_CAN_LIBRARY/Inc/putm_can_interface.hpp"

using namespace PUTM_CAN;

int main(int argc, char **argv)
{
  Apps_main frame = {
    .pedal_position=0,
    .counter=0,
    .position_diff=0,
    .device_state = Apps_states::Normal_operation
  };

  CAN can;
  can.connect();
  can.transmit(frame);

  ros::init(argc, argv, "putm_dv_traction_control_driver");

  return 0;
}

