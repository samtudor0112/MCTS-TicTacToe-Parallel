#include <iostream>
#include <mpi.h>
#include "../../include/gameboard/common.hpp"
#include "../../include/gameboard/State.hpp"
#include "../../include/search/MCTS.hpp"
#include "../../include/search/PlayGame.hpp"
#include "../../include/gameboard/MPI_helpers.hpp"

// The main entry point of the program. Currently plays a game with 3 second time limit and prints the board
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    State currentState = State(3, 3);

    if (rank == MASTER_RANK) {
        // master
        std::cout << "Start\n" << std::flush;
        play_game(currentState, 3, true, 2);
        std::cout << "Done!\n" << std::flush;
    } else {
        // slave
        play_game(currentState, 3, true, 2);
    }

    MPI_Finalize();
}

