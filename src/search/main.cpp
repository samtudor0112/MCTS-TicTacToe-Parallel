#include <iostream>
#include "../../include/gameboard/common.hpp"
#include "../../include/gameboard/State.hpp"
#include "../../include/search/MCTS.hpp"

// The main entry point of the program. Currently plays a game of Tic Tac Toe against itself, with each player having
// 3 seconds to play.
int main(int argc, char** argv) {
    State currentState = State();

    while(true) {
        double timeToUse = 3;
        MCTS search = MCTS(currentState, timeToUse);
        State bestMove = search.getBestMove();
        std::cout << bestMove.getStringBoard() << std::flush;
        if (bestMove.getGameStatus() != inProgress) {
            break;
        }
        currentState = bestMove;
    }
    std::cout << "Done!" <<std::flush;
}
