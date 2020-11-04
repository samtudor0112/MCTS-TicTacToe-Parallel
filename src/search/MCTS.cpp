#include "../../include/search/MCTS.hpp"
#include <chrono>
#include <algorithm>
#include <functional>
#include <iostream>
#include <stack>

// We assume that we are the player who's colour's turn it is in the startState.
MCTS::MCTS(State startState, double timeLimit) :
        timeLimit(timeLimit), root(Node(startState)) {}

// Executes the MCTS search. Takes slightly longer than timeLimit.
// Will return the approximately best State object which is the result of the best move.
State MCTS::getBestMove() {
    auto startTime = std::chrono::system_clock::now();
    auto endTime = startTime + std::chrono::duration<double>(timeLimit);

    while (std::chrono::system_clock::now() < endTime) {
        Node* newNode = selectAndExpandNewNode();
        GameStatus playoutResult = simulatePlayout(newNode);
        backPropagateResult(newNode, playoutResult);
    }

    return getBestMoveFromFinishedTree();
}

// The select component of the MCTS algorithm. Also calls the expand component of the MCTS algorithm if necessary.
// Iteratively selects the best node to playout based off the UCT formula.
Node* MCTS::selectAndExpandNewNode() {
    // We start at the root
    Node* node = &this->root;

    // Traverse the tree, selecting the best UCT score each time, until we have a leaf node
    while (node->getChildNodes()->size()) {
        int parentVisits = node->getVisits();
        double maxScore = -1;
        Node* newNode;
        // Find the node with max UCT value
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

// The expand component of the MCTS algorithm. Determines all children of a leaf node and adds them to the search tree.
void MCTS::expandNode(Node* parent) {
    State boardState = parent->getState();
    std::vector<State> validMoves = boardState.getAllLegalMoveStates();
    for (State state: validMoves) {
        Node* newNode = new Node(state);
        newNode->setParent(parent);
        parent->addChildNode(newNode);
    }
}

// The simulation component of the MCTS algorithm. Plays out a game from the state of a given node, then
// returns the result of the playout.
GameStatus MCTS::simulatePlayout(Node* node) {
    // Currently, the method of playout is random playout (both players select random moves)
    // This is the most general approach, and can be applied to any game.
    // The search can be tailored to a specific game by modifying the playout strategy (e.g. by increasing the
    // weighting of certain moves in the random selection).
    State boardState = node->getState();
    while (boardState.getGameStatus() == inProgress) {
        std::vector<State> validMoves = boardState.getAllLegalMoveStates();
        boardState = *select_randomly(validMoves.begin(), validMoves.end());
    }

    return boardState.getGameStatus();
}

// The reward function which we backpropagate. Returns how desirable a given outcome is (for nodes of a certain colour)
// between 0 and 1 inclusive.
double MCTS::getReward(PlayerColour nodeColour, GameStatus result) {
    // Note this function is actually reversed i.e. on white nodes, black is rewarded for winning.
    // This is so black nodes expand white child nodes which are most promising for it
    // I'm not sure if this inversion is algorithmically sound. I couldn't find anyone else mentioning it.
    if (result == whiteWin) {
        return nodeColour == black ? 1 : 0;
    } else if (result == blackWin) {
        return nodeColour == white ? 1 : 0;
    } else {
        // Draw
        return 0.3; // We'd prefer to win once than draw 3 times.
    }
}

// The backpropagation component of the MCTS algorithm. Propagates the result of a playout upwards through the
// search tree.
void MCTS::backPropagateResult(Node* node, GameStatus playoutResult) {
    while (node != nullptr) {
        double reward = getReward(node->getState().getTurn(), playoutResult);
        node->addVisit(reward);
        node = node->getParentNode();
    }
}

// Returns the approximately best State to move to from the root. Will be null if starting at a won/lost/drawn position
State MCTS::getBestMoveFromFinishedTree() {
    int maxVisits = -1;
    Node* bestNode;
    // Find the node with max visits value
    for (Node* find_node: *(root.getChildNodes())) {
        int val = find_node->getVisits();
        if (val > maxVisits) {
            maxVisits = val;
            bestNode = find_node;
        }
    }
    // Grab the best state before cleaning up our nodes
    State bestState = bestNode->getState();
    cleanUpNodes();

    return bestState;
}

// Manually clean up the pointers to all the nodes of the tree. Iteratively deletes every non-root node.
// Also cleans up all the boards of the boards of the states of all the nodes. What a mouthful.
void MCTS::cleanUpNodes() {
    std::deque<Node*> nodeStack;
    nodeStack.push_back(&root);

    while(!nodeStack.empty()) {
        Node* toDelete = nodeStack.back();
        nodeStack.pop_back();
        for (Node* child: *(toDelete->getChildNodes())) {
            nodeStack.push_back(child);
        }

        // We can't delete the root
        if (toDelete != &root) {
            delete toDelete;
        }
    }
}

// Returns the value of the UCT (Upper Confidence bounds applied to Trees) formula for a given node. Also dependent on
// how many times the node's parent has been visited. The higher the UCT value is, the more desirable it is to visit
// a node.
double MCTS::UCTValue(Node* node, int parentVisits) {
    if (node->getVisits() == 0) {
        // Always visit each node once
        return std::numeric_limits<double>::max();
    }

    return node->getReward() / (double) node->getVisits()
            + sqrt(2.0 * log(parentVisits) / (double) node->getVisits());
}

Node* MCTS::getRoot() {
    return &root;
}
