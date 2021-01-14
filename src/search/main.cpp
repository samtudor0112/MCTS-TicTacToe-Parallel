#include <iostream>
#include "../../include/gameboard/common.hpp"
#include "../../include/gameboard/State.hpp"
#include "../../include/search/MCTS.hpp"
#include "../../include/search/PlayGame.hpp"

// The main entry point of the program. Currently plays a game with 3 second time limit and prints the board
int main(int argc, char** argv) {
    std::cout << "Start\n" << std::flush;
    State currentState = State(7, 6);
    play_game(currentState, 3, true);
    std::cout << "Done!\n" << std::flush;
}

