//
// Created by sam on 4/9/20.
//

#include "../../include/gameboard/State.hpp"

GameStatus State::getGameStatus() {
    return gameStatus;
}

std::vector<State> State::getAllLegalMoveStates() {
    std::vector<State> out = std::vector<State>();
    std::vector<TicTacToe> boards = board.getAllLegalMoveStates(turn);
    for(TicTacToe board: boards) {
        out.push_back(State(otherPlayer(turn), board));
    }
    return out;
}

State::State() : turn(white), board(TicTacToe()) {
    updateGameStatus();
}

State::State(PlayerColour turn, TicTacToe board) : turn(turn), board(board) {
    updateGameStatus();
}

void State::updateGameStatus() {
    gameStatus = board.getGameStatus();
}

std::string State::getStringBoard() {
    return board.boardToString();
}
