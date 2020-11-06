#include <iostream>
#include <utility>
#include <mpi.h>
#include "../../include/search/PlayGame.hpp"
#include "../../include/search/MCTS.hpp"
#include "../../include/gameboard/MPI_helpers.hpp"

// Plays a game of Tic Tac Toe against itself, with each player having timeToUse seconds to play each move
// Returns the result of the game
GameStatus play_game(State startState, double timeToUse, bool print, int numThreads) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    State currentState = std::move(startState);

    if (rank == MASTER_RANK) {
        // Master
        while(true) {
            MCTS search = MCTS(currentState, timeToUse, numThreads);
            State bestMove = search.getBestMove(nullptr);
            if (print) {
                std::cout << bestMove.getStringBoard() << std::flush;
            }
            if (bestMove.getGameStatus() != inProgress) {
                return bestMove.getGameStatus();
            }
            currentState = bestMove;
        }
    } else {
        // Slave
        // Same as the above loop but without printing or collecting data
        while(true) {
            MCTS search = MCTS(currentState, timeToUse, numThreads);
            State bestMove = search.getBestMove(nullptr);
            if (bestMove.getGameStatus() != inProgress) {
                return inProgress; // Doesn't matter
            }
            currentState = bestMove;
        }
    }

}
// Plays a game of Tic Tac Toe against itself, with each player having timeToUse seconds to play each move
// Returns the VPS averaged over every turn of the search
double play_game_vps(State startState, double timeToUse, bool print, int numThreads) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    State currentState = std::move(startState);

    if (rank == MASTER_RANK) {
        // Master
        int numVisits = 0;
        double sumVps = 0.0;
        int numMoves = 0;
        while(true) {
            MCTS search = MCTS(currentState, timeToUse, numThreads);
            State bestMove = search.getBestMove(&numVisits);

            sumVps += numVisits;
            numMoves++;

            if (print) {
                std::cout << bestMove.getStringBoard() << std::flush;
            }
            if (bestMove.getGameStatus() != inProgress) {
                return sumVps / (numMoves * timeToUse);
            }
            currentState = bestMove;
        }
    } else {
        // Slave
        // Same as the above loop but without printing or collecting data
        int numVisits = 0;
        while(true) {
            MCTS search = MCTS(currentState, timeToUse, numThreads);
            State bestMove = search.getBestMove(&numVisits);
            if (bestMove.getGameStatus() != inProgress) {
                return 0;
            }
            currentState = bestMove;
        }
    }

}