//
// Created by sam on 4/9/20.
//

#ifndef SERIAL_STATE_HPP
#define SERIAL_STATE_HPP


#include "common.hpp"
#include "Move.hpp"

class State {
private:
    GameStatus gameStatus;
public:
    GameStatus getGameStatus();
    std::vector<Move> getAllLegalMoves();
    State executeMove(Move move);
};


#endif //SERIAL_STATE_HPP
