#include <iostream>
#include "../../include/gameboard/State.hpp"
#include "../../include/search/PlayGame.hpp"

// Tests the engine for correctness and print the result
void testCorrectness(int numTrials, double timeToUse, int n, int d, int numThreads) {
    int numWhiteWins = 0;
    int numDraws = 0;
    for (int i = 0; i < numTrials; i++) {
        State currentState = State(n, d);
        GameStatus result = play_game(currentState, timeToUse, false, numThreads);
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

// Test the engine's VPS and print the result
void testVPS(int numTrials, double timeToUse, int n, int d, int numThreads) {
    double vps = 0;
    for (int i = 0; i < numTrials; i++) {
        State currentState = State(n,d);
        double vps_trial = play_game_vps(currentState, timeToUse, false, numThreads);
        vps += vps_trial;
    }

    std::cout << "The engine had an average VPS of " << vps / numTrials << " with " << timeToUse \
            << "s per move over " << numTrials << " trials.\n" << std::flush;
}

// Tests the engine for correctness and VPS (visits/second). Requires the following command line arguments:
// ./tests n d numTrials timePerMove numThreads
int main(int argc, char** argv) {
    if (argc != 6) {
        std::cout << "Invalid arguments" << std::flush;
        return 1;
    }
    int n = std::stoi(argv[1]);
    int d = std::stoi(argv[2]);
    int numTrials = std::stoi(argv[3]);
    double timeToUse = std::stod(argv[4]);
    int numThreads = std::stoi(argv[5]);
    std::cout << "Program version: OpenMP parallelisation. Number of threads: " << numThreads << ".\n" << std::flush;
    std::cout << "Conducting tests with n=" << n << ", d=" << d << ".\n" << std::flush;
    std::cout << "Testing correctness:\n" << std::flush;
    testCorrectness(numTrials, timeToUse, n, d, numThreads);
    std::cout << "Testing VPS:\n" << std::flush;
    testVPS(numTrials, timeToUse, n, d, numThreads);
    std::cout << "Done!\n" << std::flush;
}