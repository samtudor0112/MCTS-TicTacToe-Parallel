#include <iostream>
#include "../../include/gameboard/common.hpp"
#include "../../include/gameboard/State.hpp"
#include "../../include/search/MCTS.hpp"

// Plays a game of Tic Tac Toe against itself, with each playing having timeToUse seconds to play each move
GameStatus play_game(State startState, double timeToUse, bool print) {
    State currentState = startState;
    while(true) {
        MCTS search = MCTS(currentState, timeToUse);
        State bestMove = search.getBestMove();
        if (print) {
            std::cout << bestMove.getStringBoard() << std::flush;
        }
        if (bestMove.getGameStatus() != inProgress) {
            return bestMove.getGameStatus();
        }
        currentState = bestMove;
    }
}

// The main entry point of the program. Currently plays a game with 3 second time limit and prints the board
int main(int argc, char** argv) {
    std::cout << "Start\n" << std::flush;
    State currentState = State();
    play_game(currentState, 3, true);
    std::cout << "Done!\n" << std::flush;
}


