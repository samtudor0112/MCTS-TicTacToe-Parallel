cmake_minimum_required(VERSION 3.17)
project(serial)

set(CMAKE_CXX_STANDARD 17)

add_executable(serial src/search/main.cpp src/search/Node.cpp include/search/Node.hpp src/gameboard/State.cpp include/gameboard/State.hpp src/search/MCTS.cpp include/search/MCTS.hpp include/gameboard/common.hpp src/gameboard/TicTacToe.cpp include/gameboard/TicTacToe.hpp src/gameboard/common.cpp)