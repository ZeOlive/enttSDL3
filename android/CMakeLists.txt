cmake_minimum_required(VERSION 3.16)
project(MySDLAndroid)


add_library(MySDLApp SHARED ../src/main.cpp)
add_subdirectory(../vendor/SDL3 SDL3)

target_link_libraries(MySDLApp PRIVATE SDL3::SDL3)