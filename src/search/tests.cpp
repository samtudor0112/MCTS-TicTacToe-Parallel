#include <iostream>
#include "../../include/gameboard/State.hpp"
#include "../../include/search/PlayGame.hpp"

void testCorrectness(int numTrials, double timeToUse) {
    int numDraws = 0;
    for (int i = 0; i < numTrials; i++) {
        State currentState = State();
        GameStatus result = play_game(currentState, timeToUse, false);
        if (result == draw) {
            numDraws++;
        }
    }

    std::cout << "The engine drew " << (double)numDraws / numTrials * 100 << "% of the time with " << timeToUse \
            << "s per move over " << numTrials << " trials.\n" << std::flush;
}

void testVPS(int numTrials, double timeToUse) {
    double vps = 0;
    for (int i = 0; i < numTrials; i++) {
        State currentState = State();
        double vps_trial = play_game_vps(currentState, timeToUse, false);
        vps += vps_trial;
    }

    std::cout << "The engine had an average VPS of " << vps / numTrials << " with " << timeToUse \
            << "s per move over " << numTrials << " trials.\n" << std::flush;
}

// The main entry point of the program. Currently plays a game with 3 second time limit and prints the board
int main(int argc, char** argv) {
    std::cout << "Testing correctness:\n" << std::flush;
    testCorrectness(10, 0.1);
    std::cout << "Testing VPS:\n" << std::flush;
    testVPS(10, 0.1);
    std::cout << "Done!\n" << std::flush;
}