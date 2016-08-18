cmake_minimum_required(VERSION 3.2)
project(text_on_image)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV REQUIRED)

include_directories(/home/ashok/Projects/tools/opencv-3.1.0/3rdparty/ippicv/unpack/ippicv_lnx/include)

set(SOURCE_FILES src/detection.cpp src/main.cpp src/cascadeObjectDetection.cpp src/haar.cpp src/config.cpp)
add_executable(detection_demo ${SOURCE_FILES})
target_link_libraries(detection_demo ${OpenCV_LIBS} glog gflags)
