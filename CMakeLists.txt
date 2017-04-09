cmake_minimum_required(VERSION 2.8.3)
project(converter_velodyne)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

# Use C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_message_files(
  FILES
  Velodyne16Packet.msg
  VelodynePacket.msg
  VelodyneScan.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp std_msgs message_runtime
)

include_directories( include
  ${catkin_INCLUDE_DIRS}
)

add_executable(converter_velodyne_node src/converter_velodyne_node.cpp src/converter_velodyne.cpp)
target_link_libraries(converter_velodyne_node ${catkin_LIBRARIES} )


# Installation

install(TARGETS converter_velodyne_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
