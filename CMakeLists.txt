cmake_minimum_required(VERSION 3.9.1)
project(parallel)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

# We need to use this for compilation on getafix
# Comment so debug build actually works
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_FLAGS "-fopenmp")

add_executable(parallel src/search/main.cpp src/search/Node.cpp include/search/Node.hpp src/gameboard/State.cpp include/gameboard/State.hpp src/search/MCTS.cpp include/search/MCTS.hpp include/gameboard/common.hpp src/gameboard/TicTacToe.cpp include/gameboard/TicTacToe.hpp src/gameboard/common.cpp src/search/PlayGame.cpp include/search/PlayGame.hpp include/gameboard/hashes.hpp src/gameboard/MPI_helpers.cpp include/gameboard/MPI_helpers.hpp)

add_executable(tests src/search/tests.cpp src/search/Node.cpp include/search/Node.hpp src/gameboard/State.cpp include/gameboard/State.hpp src/search/MCTS.cpp include/search/MCTS.hpp include/gameboard/common.hpp src/gameboard/TicTacToe.cpp include/gameboard/TicTacToe.hpp src/gameboard/common.cpp src/search/PlayGame.cpp include/search/PlayGame.hpp include/gameboard/hashes.hpp src/gameboard/MPI_helpers.cpp include/gameboard/MPI_helpers.hpp)

target_link_libraries(parallel ${MPI_LIBRARIES})

target_link_libraries(tests ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
    set_target_properties(parallel PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
    set_target_properties(tests PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(parallel PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
    set_target_properties(tests PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()