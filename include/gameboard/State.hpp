#ifndef SERIAL_STATE_HPP
#define SERIAL_STATE_HPP

#include "common.hpp"
#include "TicTacToe.hpp"

// A wrapper class for the board object.
// This means we only have to modify this class to change the game the engine works on
// (from tic tac toe to checkers, say).
// Functionally, represents the current state of a given game, including the game board, who's turn it is, and the
// result of a game
class State {
private:
    // The rules of the board are mostly independent of this class and entirely independent of the rest of the program.
    // i.e. to change the game / rules (to checkers) only the class of this member variable and a few function
    // declarations would need to be changed
    TicTacToe board;

    PlayerColour turn;

public:
    State(int n, int d);
    State(PlayerColour turn, const TicTacToe& board);
    GameStatus getGameStatus();
    std::vector<State> getAllLegalMoveStates();
    std::string getStringBoard();
    PlayerColour getTurn();
};


#endif //SERIAL_STATE_HPP
