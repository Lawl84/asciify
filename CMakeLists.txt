cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
project(asciify)

find_package(OpenCV CONFIG REQUIRED)

add_executable(asciify
  src/asciify.cpp
)

target_link_libraries(asciify PRIVATE opencv_ml opencv_dnn opencv_core opencv_flann opencv_highgui)

set_property(TARGET asciify PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})