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
    Node root;
    double timeLimit;

    // 4 Steps of the MCTS algorithm
    Node* selectAndExpandNewNode();
    void expandNode(Node* parent);
    GameStatus simulatePlayout(Node* node);
    void backPropagateResult(Node* node, GameStatus playoutResult);

    // Other supporting functions
    static double UCTValue(Node* node, int parentVisits);
    void cleanUpNodes();
    double getReward(PlayerColour nodeColour, GameStatus result);
    State getBestMoveFromFinishedTree();
public:
    MCTS(State startState, double timeLimit);
    State getBestMove();
    Node* getRoot();
};


#endif //SERIAL_MCTS_HPP
