cmake_minimum_required(VERSION 3.5)
project(protobuf_demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")

set(PROTOBUF_HOME /home/zhoukang/local/protobuf)
include_directories(${PROTOBUF_HOME}/include)
link_libraries(${PROTOBUF_HOME}/lib)

add_library(classinfo SHARED ClassInfo.pb.cc ClassOperator.cpp)
target_link_libraries(classinfo ${PROTOBUF_HOME}/lib/libprotobuf.so pthread)