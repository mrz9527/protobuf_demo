cmake_minimum_required(VERSION 3.5)
project(protobuf_demo)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(common)
add_subdirectory(serialize)
add_subdirectory(reflect)

# protobuf目录
set(PROTOBUF_HOME /home/zhoukang/local/protobuf)
include_directories(${PROTOBUF_HOME}/include)
link_libraries(${PROTOBUF_HOME}/lib)

include_directories(reflect
        common
        serialize)

add_executable(reflect_demo reflect_demo.cpp)
target_link_libraries(reflect_demo reflect serialize)

add_executable(serialize_demo serialize_demo.cpp)
target_link_libraries(serialize_demo serialize)


#add_executable(protobuf_demo main.cpp)
#target_link_libraries(protobuf_demo studentinfo)

include(ExternalProject)