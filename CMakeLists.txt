cmake_minimum_required(VERSION 3.10)
project(high_performance_opencv)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(binaryImage test/binary.cpp cv_utils/binaryImage.hpp)
target_link_libraries(binaryImage ${OpenCV_LIBRARIES})

add_executable(connectedComponents test/connectedComponents.cpp cv_utils/connectedComponents.hpp)
target_link_libraries(connectedComponents ${OpenCV_LIBRARIES})