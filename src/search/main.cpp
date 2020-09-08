#include <iostream>
#include "../../include/gameboard/common.hpp"
#include "../../include/gameboard/State.hpp"
#include "../../include/search/MCTS.hpp"

int main(int argc, char** argv) {
    // TEMPORARY
    PlayerColour ourColour = white;

    State currentState = State();

    while(true) {
        int timeToUse = 3;
        MCTS search = MCTS(currentState, timeToUse, ourColour);
        State bestMove = search.getBestMove();
        std::cout << bestMove.getStringBoard() << std::flush;
        // Temp
        break;
    }
}
