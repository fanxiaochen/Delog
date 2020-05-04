cmake_minimum_required(VERSION 3.0)
project(example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Eigen3 QUIET)
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(OpenCV QUIET)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(example example.cpp)
target_link_libraries(example ${OpenCV_LIBS})
