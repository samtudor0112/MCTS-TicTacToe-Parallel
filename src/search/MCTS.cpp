//
// Created by sam on 4/9/20.
//

#include "../../include/search/MCTS.hpp"
#include <chrono>
#include <algorithm>
#include <functional>

MCTS::MCTS(State startState, int timeLimit, PlayerColour colour) :
        timeLimit(timeLimit), ourColour(colour), root(Node(startState)) {
}
/*
 * Executes the MCTS search. Takes slightly longer than timeLimit. Will return the approximately best Move object to
 * perform.
 */
State MCTS::getBestMove() {
    auto startTime = std::chrono::system_clock::now();
    auto endTime = startTime + std::chrono::seconds(timeLimit);

    while (std::chrono::system_clock::now() < endTime) {
        Node newNode = selectAndExpandNewNode();
        double playoutResult = simulatePlayout(newNode);
        backPropagateResult(&newNode, playoutResult);
    }

    return getBestMoveFromFinishedTree();
}

Node MCTS::selectAndExpandNewNode() {
    // We start at the root
    Node node = this->root;

    // Traverse the tree, selecting the best UCT score each time, until we have a leaf node
    while (node.getChildNodes().size() != 0) {
        int parentVisits = node.getVisits();
        node = *std::max_element(node.getChildNodes().begin(), node.getChildNodes().end(), \
                [&](const Node& a, const Node& b) {
                    return UCTValue(a, parentVisits) < UCTValue(b, parentVisits);
                }
        );
    }

    // Expand node if it's still in progress
    if (node.getState().getGameStatus() == inProgress) {
        expandNode(node);
        node = *select_randomly(node.getChildNodes().begin(), node.getChildNodes().end());
    }

    return node;
}

void MCTS::expandNode(Node parent) {
    State boardState = parent.getState();
    std::vector<State> validMoves = boardState.getAllLegalMoveStates();
    for (State state: validMoves) {
        Node newNode = Node(state);
        newNode.setParent(&parent);
        parent.getChildNodes().push_back(newNode);
    }
}

double MCTS::simulatePlayout(Node node) {
    // Random playout
    State boardState = node.getState();
    while (boardState.getGameStatus() == inProgress) {
        std::vector<State> validMoves = boardState.getAllLegalMoveStates();
        boardState = *select_randomly(validMoves.begin(), validMoves.end());
    }

    // Reward function
    if (boardState.getGameStatus() == whiteWin) {
        return ourColour == white ? 1 : 0;
    } else if (boardState.getGameStatus() == blackWin) {
        return ourColour == black ? 1 : 0;
    } else {
        // Draw
        return 0.3; // We'd prefer to win once than draw 3 times.
    }
}

void MCTS::backPropagateResult(Node* node, double playoutResult) {
    while (node) {
        node->addVisit(playoutResult);
        node = node->getParentNode();
    }
}

// Returns the approximately best move to make from the root. Will be null if starting at a won/lost/drawn position
State MCTS::getBestMoveFromFinishedTree() {
    Node bestNode = *std::max_element(root.getChildNodes().begin(), root.getChildNodes().end(), \
                    [&](Node a, Node b) {
                                          return a.getVisits() < b.getVisits();
                    }
    );
    return bestNode.getState();
}

double MCTS::UCTValue(Node node, int parentVisits) {
    if (node.getVisits() == 0) {
        // Always visit each node once
        return std::numeric_limits<double>::max();
    }

    return node.getReward() / (double) node.getVisits() + sqrt(2.0 * log(parentVisits)) / (double) node.getVisits();

}

