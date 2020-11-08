#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
#include "../../include/search/MCTS.hpp"
#include "../../include/gameboard/hashes.hpp"
#include <chrono>
#include <functional>
#include <stack>
#include <utility>
#include <omp.h>
#include <unordered_set>

// We assume that we are the player who's colour's turn it is in the startState.
MCTS::MCTS(const State& startState, double timeLimit, int numThreads) :
        timeLimit(timeLimit), numThreads(numThreads) {
    for (int i = 0; i < numThreads; i++) {
        roots.emplace_back(new Node(startState));
    }
}

// Executes the MCTS search. Takes slightly longer than timeLimit.
// Will return the approximately best State object which is the result of the best move.
// Will assign finalVisits to the number of visits of the combined root node if it isn't nullptr.
State MCTS::getBestMove(int* finalVisits) {
    auto startTime = std::chrono::system_clock::now();
    auto endTime = startTime + std::chrono::duration<double>(timeLimit);
    Node* finalRoot;

#pragma omp parallel num_threads(numThreads)
    {
        Node* root = roots[omp_get_thread_num()];
        while (std::chrono::system_clock::now() < endTime) {
            Node* newNode = selectAndExpandNewNode(root);
            GameStatus playoutResult = simulatePlayout(newNode);
            backPropagateResult(newNode, playoutResult);
        }
#pragma omp barrier
#pragma omp master
        {
            finalRoot = combineTrees(finalVisits);
        }
#pragma omp barrier
        // We make our own finalRoot so we can clean up all the other roots' trees
        cleanUpNodes(root);
    }
    return getBestMoveFromFinishedTree(finalRoot);

}

// The select component of the MCTS algorithm. Also calls the expand component of the MCTS algorithm if necessary.
// Iteratively selects the best node to playout based off the UCT formula.
Node* MCTS::selectAndExpandNewNode(Node* root) {
    // We start at the root
    Node* node = root;

    // Traverse the tree, selecting the best UCT score each time, until we have a leaf node
    while (!node->getChildNodes()->empty()) {
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
    for (const State& state: validMoves) {
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

// Combines all the trees of each thread into one tree to determine the best move.
// We assign to the value of finalVisits since we're lazy
Node* MCTS::combineTrees(int* finalVisits) {
    // All we need is the root Node, and it's children, which only need the correct number of visits. Anything else can
    // be undefined
    Node* finalRoot = new Node(roots[0]->getState());

    // Only stores 1 copy of each state
    std::unordered_map<State, int, state_hash> childStates;
    for (Node* root: roots) {
        for (Node* child: *(root->getChildNodes())) {
            if (childStates.find(child->getState()) == childStates.end()) {
                childStates[child->getState()] = child->getVisits();
            } else {
                childStates[child->getState()] += child->getVisits();
            }
        }
    }

    for (const auto& stateVistsPair: childStates) {
        Node* newChild = new Node(stateVistsPair.first);
        newChild->setVisits(stateVistsPair.second);
        finalRoot->addChildNode(newChild);
    }

    if (finalVisits != nullptr) {
        *finalVisits = 0;
        // We actually have to manually calculate the final visits since what finalRoot reports will be 0.
        for (Node* child: *(finalRoot->getChildNodes())) {
            *finalVisits += child->getVisits();
        }
    }

    return finalRoot;
}

// Returns the approximately best State to move to from the root. Will be null if starting at a won/lost/drawn position
State MCTS::getBestMoveFromFinishedTree(Node* finalRoot) {
    int maxVisits = -1;
    Node* bestNode;
    // Find the node with max visits value
    for (Node* find_node: *(finalRoot->getChildNodes())) {
        int val = find_node->getVisits();
        if (val > maxVisits) {
            maxVisits = val;
            bestNode = find_node;
        }
    }
    // Grab the best state before cleaning up our nodes
    State bestState = bestNode->getState();

    cleanUpNodes(finalRoot);

    return bestState;
}

// Manually clean up the pointers to all the nodes of the tree. Iteratively deletes every non-root node.
// Also cleans up all the boards of the boards of the states of all the nodes. What a mouthful.
void MCTS::cleanUpNodes(Node* root) {
    std::deque<Node*> nodeStack;
    nodeStack.push_back(root);

    while(!nodeStack.empty()) {
        Node* toDelete = nodeStack.back();
        nodeStack.pop_back();
        for (Node* child: *(toDelete->getChildNodes())) {
            nodeStack.push_back(child);
        }

        // We can delete it even if it's the root now
        delete toDelete;

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

#pragma clang diagnostic pop