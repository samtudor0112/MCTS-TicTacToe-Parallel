#include <iostream>
#include "../../include/gameboard/common.hpp"
#include "../../include/gameboard/State.hpp"
#include "../../include/search/MCTS.hpp"
#include "../../include/search/PlayGame.hpp"

// The main entry point of the program. Currently plays a game with 3 second time limit and prints the board
int main(int argc, char** argv) {
//    std::cout << "Start\n" << std::flush;
//    State currentState = State(7, 6);
//    play_game(currentState, 3, true);
//    std::cout << "Done!\n" << std::flush;
    std::cout << "Start\n" << std::flush;
    State currentState = State(7, 6);
    bool ourTurn = true;
    while(true) {
        // Perform 1 move
        if (ourTurn) {
            MCTS search = MCTS(currentState, 3);
            State bestMove = search.getBestMove();
            std::cout << bestMove.getStringBoard() << std::flush;
            if (bestMove.getGameStatus() != inProgress) {
                return bestMove.getGameStatus();
            }
            currentState = bestMove;
        }
        else {
            std::string in;
            std::getline(std::cin, in);
            int x = std::stoi(in);
            currentState = currentState.textToMove(x);
        }
        ourTurn = !ourTurn;
    }
}

