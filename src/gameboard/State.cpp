//
// Created by sam on 4/9/20.
//

#include "../../include/gameboard/State.hpp"

GameStatus State::getGameStatus() {
    return gameStatus;
}

std::vector<State> State::getAllLegalMoveStates() {
    // TODO
    return std::vector<State>{State()};
}
