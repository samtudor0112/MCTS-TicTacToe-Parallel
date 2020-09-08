//
// Created by sam on 4/9/20.
//

#ifndef SERIAL_STATE_HPP
#define SERIAL_STATE_HPP


#include "common.hpp"

class State {
private:
    GameStatus gameStatus;
public:
    GameStatus getGameStatus();
    std::vector<State> getAllLegalMoveStates();
};


#endif //SERIAL_STATE_HPP
