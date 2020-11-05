#ifndef SERIAL_MCTS_HPP
#define SERIAL_MCTS_HPP

#include <functional>
#include "Node.hpp"
#include "../gameboard/common.hpp"

// Runs Monte Carlo Tree Search from a given start state for timeLimit seconds.
// Example use:
//      MCTS search = MCTS(currentState, timeToUse, ourColour);
//      State bestMove = search.getBestMove();
// See report for explanation of MCTS algorithm.
class MCTS {
private:
    std::vector<Node*> roots;
    int numThreads;

    double timeLimit;

    // 4 Steps of the MCTS algorithm
    Node* selectAndExpandNewNode(Node* root);
    void expandNode(Node* parent);
    GameStatus simulatePlayout(Node* node);
    void backPropagateResult(Node* node, GameStatus playoutResult);

    // Other supporting functions
    static double UCTValue(Node* node, int parentVisits);
    void cleanUpNodes(Node* root);
    double getReward(PlayerColour nodeColour, GameStatus result);
    State getBestMoveFromFinishedTree(Node* finalRoot);
    Node* combineTrees(int* finalVisits);
public:
    MCTS(const State& startState, double timeLimit, int numThreads);
    State getBestMove(int* finalVisits);
};


#endif //SERIAL_MCTS_HPP
