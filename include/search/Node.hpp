//
// Created by sam on 4/9/20.
//

#ifndef SERIAL_NODE_HPP
#define SERIAL_NODE_HPP


#include <vector>
#include "../gameboard/State.hpp"
#include "../gameboard/Move.hpp"

/*
 * A node in the MCTS search tree
 */
class Node {
private:
    Node* parentNode;
    std::vector<Node> childNodes;
    int visits;
    double reward;
    State state;
    Move move;
public:
    Node(State state);
    void setParentAndMove(Node* parentNode, Move move);
    void addVisit(double result);
    Node* getParentNode();
    State getState();
    std::vector<Node> getChildNodes();
    int getVisits();
    double getReward();
    Move getMove();
};


#endif //SERIAL_NODE_HPP
