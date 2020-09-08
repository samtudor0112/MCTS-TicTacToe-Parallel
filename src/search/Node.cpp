#include "../../include/search/Node.hpp"

Node::Node(State state) : state(state), parentNode(nullptr), visits(0), reward(0), childNodes(std::vector<Node*>()) {}

void Node::setParent(Node* _parentNode) {
    this->parentNode = _parentNode;
}

void Node::addVisit(double result) {
    this->visits += 1;
    this->reward += result;
}

Node* Node::getParentNode() {
    return this->parentNode;
}

State Node::getState() {
    return this->state;
}

std::vector<Node*>* Node::getChildNodes() {
    return &(this->childNodes);
}

int Node::getVisits() {
    return this->visits;
}

double Node::getReward() {
    return this->reward;
}

void Node::addChildNode(Node* node) {
    this->childNodes.push_back(node);
}



