##          Copyright Emil Fresk 2017.
## Distributed under the Boost Software License, Version 1.0.
##    (See accompanying file LICENSE.md or copy at
##          http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 2.8.3)
project(image_throttle)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/image_throttle_node.cpp)
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)
