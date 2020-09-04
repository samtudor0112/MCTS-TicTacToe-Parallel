//
// Created by sam on 4/9/20.
//

#include "../../include/gameboard/State.hpp"

GameStatus State::getGameStatus() {
    return gameStatus;
}

std::vector<Move> State::getAllLegalMoves() {
    // TODO
    return std::vector<Move>{Move()};
}

State State::executeMove(Move move) {
    // TODO
    return State();
}
