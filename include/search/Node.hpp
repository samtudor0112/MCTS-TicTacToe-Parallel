#ifndef SERIAL_NODE_HPP
#define SERIAL_NODE_HPP

#include <vector>
#include "../gameboard/State.hpp"

// A single node in the MCTS search tree. The whole tree can be represented simply by the root node, and the remaining
// nodes accessed through the childNodes vector.
class Node {
private:
    // parentNode is a nullptr if this is the root
    Node* parentNode;

    // ChildNodes is an empty vector if there are no children
    std::vector<Node*> childNodes;

    int visits;

    // The total reward for this node and it's children's playouts, taking into account it's colour
    double reward;

    // The colour (i.e. which player can choose which child becomes the new game state)
    // of this node is stored in the state.
    State state;
public:
    Node(State state);

    // Adds the result of a playout, with the colour of this node already accounted for
    void addVisit(double result);

    // Getters and setters/adders (?)
    void setParent(Node* parentNode);
    Node* getParentNode();
    State getState();
    std::vector<Node*>* getChildNodes();
    int getVisits();
    double getReward();
    void addChildNode(Node* node);
};


#endif //SERIAL_NODE_HPP
