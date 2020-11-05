#include <iostream>
#include "../../include/gameboard/State.hpp"
#include "../../include/search/PlayGame.hpp"

void testCorrectness(int numTrials, double timeToUse, int n, int d) {
    int numWhiteWins = 0;
    int numDraws = 0;
    for (int i = 0; i < numTrials; i++) {
        State currentState = State(n, d);
        GameStatus result = play_game(currentState, timeToUse, false, 1);
        if (result == draw) {
            numDraws++;
        } else if (result == whiteWin) {
            numWhiteWins++;
        }
    }

    std::cout << "The engine had a white win percentage of " << (double)numWhiteWins / numTrials * 100
            << "% and a draw percentage of " << (double)numDraws / numTrials * 100 << "% with " << timeToUse \
            << "s per move over " << numTrials << " trials.\n" << std::flush;
}

void testVPS(int numTrials, double timeToUse, int n, int d) {
    double vps = 0;
    for (int i = 0; i < numTrials; i++) {
        State currentState = State(n,d);
        double vps_trial = play_game_vps(currentState, timeToUse, false, 1);
        vps += vps_trial;
    }

    std::cout << "The engine had an average VPS of " << vps / numTrials << " with " << timeToUse \
            << "s per move over " << numTrials << " trials.\n" << std::flush;
}

// Tests the engine for correctness and VPS (visits/second).
int main(int argc, char** argv) {
    int n = 3;
    int d = 3;
    std::cout << "Conducting tests with n=" << n << ", d=" << d << ".\n" << std::flush;
    std::cout << "Testing correctness:\n" << std::flush;
    testCorrectness(5, 1, n, d);
    std::cout << "Testing VPS:\n" << std::flush;
    testVPS(5, 1, n, d);
    std::cout << "Done!\n" << std::flush;
}