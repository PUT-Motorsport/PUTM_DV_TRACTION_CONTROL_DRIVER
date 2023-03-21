cmake_minimum_required(VERSION 3.0.2)
project(putm_dv_traction_control_driver)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

catkin_package(INCLUDE_DIRS include)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(main src/main.cpp src/putm_dv_traction_control_driver.cpp)

target_link_libraries(main ${catkin_LIBRARIES})