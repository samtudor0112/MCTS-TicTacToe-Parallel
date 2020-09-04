//
// Created by sam on 4/9/20.
//

#ifndef SERIAL_NODE_HPP
#define SERIAL_NODE_HPP


#include <vector>
#include "State.hpp"

class Node {
private:
    Node parentNode;
    std::vector<Node> childNodes;
    int visits;
    double reward;
    State state;
public:
    Node(State state);
    void setParent(Node parentNode);
    void addVisit(double result);
    Node getParentNode();
    State getState();
    std::vector<Node> getChildNodes();
    int getVisits();
    double getReward();
};


#endif //SERIAL_NODE_HPP
