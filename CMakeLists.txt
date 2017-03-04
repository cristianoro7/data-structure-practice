cmake_minimum_required(VERSION 3.6)
project(datastruct)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp adtlist/ds_list.cpp)
add_executable(datastruct ${SOURCE_FILES} adtlist/list.h adtlist/ds_list.cpp)