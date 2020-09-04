cmake_minimum_required(VERSION 3.17)
project(serial)

set(CMAKE_CXX_STANDARD 17)

add_executable(serial src/main.cpp src/Node.cpp include/Node.hpp src/State.cpp include/State.hpp)