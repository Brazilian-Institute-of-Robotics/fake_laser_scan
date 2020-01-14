cmake_minimum_required(VERSION 2.8.3)

project(fake_laser_scan)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  tf
)
catkin_package(
)
include_directories(include
                    ${catkin_INCLUDE_DIRS}
)

add_executable(fake_laser_scan 
                src/fake_laser_scan.cpp)
# install(TARGETS fake_laserscan
#         RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

# add_executable(fake_laserscan ${${PROJECT_NAME}_SOURCES})

target_link_libraries(fake_laser_scan ${catkin_LIBRARIES})

# install(TARGETS fake_laserscan
#         RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})