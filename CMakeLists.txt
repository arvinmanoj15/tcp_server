cmake_minimum_required(VERSION 3.15)
project(TCPServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(tcp_server src/main.cpp src/server.cpp)

target_include_directories(tcp_server PRIVATE include)

