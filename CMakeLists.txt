cmake_minimum_required(VERSION 2.8.3)
project(converter_velodyne)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  velodyne_msgs
  velodyne16
  nodelet
)

# Use C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp std_msgs velodyne_msgs velodyne16 nodelet
)

include_directories( include
  ${catkin_INCLUDE_DIRS}
)

add_executable(converter_velodyne_node src/converter_velodyne_node.cpp src/converter_velodyne.cpp)
add_dependencies(converter_velodyne_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(converter_velodyne_node ${catkin_LIBRARIES} )

# Nodelet
add_library(converter_velodyne_nodelet src/converter_velodyne_nodelet.cpp src/converter_velodyne.cpp)
add_dependencies(converter_velodyne_nodelet ${catkin_EXPORTED_TARGETS})
target_link_libraries(converter_velodyne_nodelet ${catkin_LIBRARIES})

# Installation

install(TARGETS converter_velodyne_node converter_velodyne_nodelet
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(FILES converter_velodyne_nodelet.xml
      DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
