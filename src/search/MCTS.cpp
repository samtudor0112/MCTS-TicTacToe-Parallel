//
// Created by sam on 4/9/20.
//

#include "../../include/search/MCTS.hpp"
#include <chrono>
#include <algorithm>
#include <functional>
#include <iostream>

MCTS::MCTS(State startState, int timeLimit, PlayerColour colour) :
        timeLimit(timeLimit), ourColour(colour), root(Node(startState)) {}
/*
 * Executes the MCTS search. Takes slightly longer than timeLimit. Will return the approximately best Move object to
 * perform.
 */
State MCTS::getBestMove() {
    auto startTime = std::chrono::system_clock::now();
    auto endTime = startTime + std::chrono::seconds(timeLimit);

    while (std::chrono::system_clock::now() < endTime) {
        Node* newNode = selectAndExpandNewNode();
        GameStatus playoutResult = simulatePlayout(newNode);
        backPropagateResult(newNode, playoutResult);
    }

    return getBestMoveFromFinishedTree();
}

Node* MCTS::selectAndExpandNewNode() {
    // We start at the root
    Node* node = &this->root;

    // Traverse the tree, selecting the best UCT score each time, until we have a leaf node
    while (node->getChildNodes()->size() != 0) {
        int parentVisits = node->getVisits();
        double maxScore = -1;
        Node* newNode;
        // Find node with max UCT value
        for (Node* find_node: *(node->getChildNodes())) {
            double val = UCTValue(find_node, parentVisits);
            if (val > maxScore) {
                maxScore = val;
                newNode = find_node;
            }
        }
        node = newNode;
    }

    // Expand node if it's still in progress
    if (node->getState().getGameStatus() == inProgress) {
        expandNode(node);
        node = *select_randomly(node->getChildNodes()->begin(), node->getChildNodes()->end());
    }

    return node;
}

void MCTS::expandNode(Node* parent) {
    State boardState = parent->getState();
    std::vector<State> validMoves = boardState.getAllLegalMoveStates();
    for (State state: validMoves) {
        Node* newNode = new Node(state);
        newNode->setParent(parent);
        parent->addChildNode(newNode);
    }
}

GameStatus MCTS::simulatePlayout(Node* node) {
    // Random playout
    State boardState = node->getState();
    while (boardState.getGameStatus() == inProgress) {
        std::vector<State> validMoves = boardState.getAllLegalMoveStates();
        boardState = *select_randomly(validMoves.begin(), validMoves.end());
    }

    return boardState.getGameStatus();
}

// Reward function
double MCTS::getReward(PlayerColour nodeColour, GameStatus result) {
    // Note this function is actually reversed i.e. on white nodes, black is rewarded for winning.
    // This is so black node expand white child nodes which are most promising for it
    if (result == whiteWin) {
        return nodeColour == black ? 1 : 0;
    } else if (result == blackWin) {
        return nodeColour == white ? 1 : 0;
    } else {
        // Draw
        return 0.3; // We'd prefer to win once than draw 3 times.
    }
}

void MCTS::backPropagateResult(Node* node, GameStatus playoutResult) {
    while (node != nullptr) {
        double reward = getReward(node->getState().getTurn(), playoutResult);
        node->addVisit(reward);
        node = node->getParentNode();
    }
}

// Returns the approximately best move to make from the root. Will be null if starting at a won/lost/drawn position
State MCTS::getBestMoveFromFinishedTree() {
    // Find node with max visits value
    int maxVisits = -1;
    Node* bestNode;
    for (Node* find_node: *root.getChildNodes()) {
        int val = find_node->getVisits();
        if (val > maxVisits) {
            maxVisits = val;
            bestNode = find_node;
        }
    }
    return bestNode->getState();
}

double MCTS::UCTValue(Node* node, int parentVisits) {
    if (node->getVisits() == 0) {
        // Always visit each node once
        return std::numeric_limits<double>::max();
    }

    return node->getReward() / (double) node->getVisits()
            + sqrt(2.0 * log(parentVisits) / (double) node->getVisits());

}

