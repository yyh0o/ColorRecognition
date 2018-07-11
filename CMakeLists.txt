cmake_minimum_required(VERSION 3.10)
project(ColorRecognition)

set(CMAKE_CXX_STANDARD 11)

add_executable(ColorRecognition main.cpp)

find_package(OpenCV)
#或者find_package(OpenCV3)
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)
target_link_libraries( ColorRecognition ${OpenCV_LIBS} )