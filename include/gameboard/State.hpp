//
// Created by sam on 4/9/20.
//

#ifndef SERIAL_STATE_HPP
#define SERIAL_STATE_HPP


#include "common.hpp"
#include "TicTacToe.hpp"

// Basically just a wrapper for whatever board I'm using
class State {
private:
    GameStatus gameStatus;
    TicTacToe board;
    PlayerColour turn;

    void updateGameStatus();
public:
    State();
    State(PlayerColour turn, TicTacToe board);
    GameStatus getGameStatus();
    std::vector<State> getAllLegalMoveStates();
    std::string getStringBoard();
};


#endif //SERIAL_STATE_HPP
