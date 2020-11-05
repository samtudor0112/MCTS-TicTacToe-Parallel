cmake_minimum_required(VERSION 3.9.1)
project(parallel)

set(CMAKE_CXX_STANDARD 17)

# We need to use this for compilation on getafix
# Comment so debug build actually works
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_FLAGS "-fopenmp")

add_executable(parallel src/search/main.cpp src/search/Node.cpp include/search/Node.hpp src/gameboard/State.cpp include/gameboard/State.hpp src/search/MCTS.cpp include/search/MCTS.hpp include/gameboard/common.hpp src/gameboard/TicTacToe.cpp include/gameboard/TicTacToe.hpp src/gameboard/common.cpp src/search/PlayGame.cpp include/search/PlayGame.hpp include/gameboard/hashes.hpp)

add_executable(tests src/search/tests.cpp src/search/Node.cpp include/search/Node.hpp src/gameboard/State.cpp include/gameboard/State.hpp src/search/MCTS.cpp include/search/MCTS.hpp include/gameboard/common.hpp src/gameboard/TicTacToe.cpp include/gameboard/TicTacToe.hpp src/gameboard/common.cpp src/search/PlayGame.cpp include/search/PlayGame.hpp)
