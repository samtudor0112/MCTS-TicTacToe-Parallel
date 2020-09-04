//
// Created by sam on 4/9/20.
//

#include "../include/Node.hpp"

Node::Node(State state) : state(state) { }

void Node::setParent(Node parentNode) {
    this->parentNode = parentNode;
}

void Node::addVisit(double result) {
    this->visits += 1;
    this->reward += result;
}

Node Node::getParentNode() {
    return this->parentNode;
}

State Node::getState() {
    return this->state;
}

std::vector<Node> Node::getChildNodes() {
    return this->childNodes;
}

int Node::getVisits() {
    return this->visits;
}

double Node::getReward() {
    return this->reward;
}



