#include <iostream>
#include <utility>
#include "../../include/search/PlayGame.hpp"
#include "../../include/search/MCTS.hpp"

// Plays a game of Tic Tac Toe against itself, with each player having timeToUse seconds to play each move
// Returns the result of the game
GameStatus play_game(State startState, double timeToUse, bool print, int numThreads) {
    State currentState = std::move(startState);
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
}
// Plays a game of Tic Tac Toe against itself, with each player having timeToUse seconds to play each move
// Returns the VPS averaged over every turn of the search
double play_game_vps(State startState, double timeToUse, bool print, int numThreads) {
    State currentState = std::move(startState);
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
}