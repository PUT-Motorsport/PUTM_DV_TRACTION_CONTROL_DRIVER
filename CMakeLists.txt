cmake_minimum_required(VERSION 3.0.2)
project(putm_dv_traction_control_driver)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(putm_dv_traction_control_driver_node src/putm_dv_traction_control_driver_node.cpp)

target_link_libraries(putm_dv_traction_control_driver_node ${catkin_LIBRARIES})