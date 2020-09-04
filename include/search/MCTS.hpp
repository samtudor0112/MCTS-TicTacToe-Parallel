//
// Created by sam on 4/9/20.
//

#ifndef SERIAL_MCTS_HPP
#define SERIAL_MCTS_HPP

#include <functional>
#include "Node.hpp"
#include "../gameboard/common.hpp"
#include "../gameboard/Move.hpp"

/*
 * Runs MCTS search for a given root node.
 */
class MCTS {
private:
    Node root;
    int timeLimit;
    PlayerColour ourColour;
    Node selectAndExpandNewNode();
    void expandNode(Node parent);
    double simulatePlayout(Node node);
    void backPropagateResult(Node* node, double playoutResult);
    Move getBestMoveFromFinishedTree();
    static double UCTValue(Node node, int parentVisits);
public:
    MCTS(State startState, int timeLimit, PlayerColour colour);
    Move getBestMove();
};


#endif //SERIAL_MCTS_HPP
