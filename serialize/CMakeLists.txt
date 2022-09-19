cmake_minimum_required(VERSION 3.5)
project(protobuf_demo)

set(CMAKE_CXX_STANDARD 11)

set(PROTOBUF_HOME /home/zhoukang/local/protobuf)
include_directories(${PROTOBUF_HOME}/include)
link_libraries(${PROTOBUF_HOME}/lib)

add_library(serialize serialize.cpp)
target_link_libraries(serialize classinfo)