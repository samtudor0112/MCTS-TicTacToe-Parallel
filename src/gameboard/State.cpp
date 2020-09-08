#include "../../include/gameboard/State.hpp"

GameStatus State::getGameStatus() {
    return gameStatus;
}

// Returns a vector of all States possible after one legal move by the player whose turn it is
// Mostly a decorative wrapper for the current game's (e.g. Tic Tac Toe's) getAllLegalMoveStates function,
// though we do change the turn here.
std::vector<State> State::getAllLegalMoveStates() {
    std::vector<State> out = std::vector<State>();
    std::vector<TicTacToe> boards = board.getAllLegalMoveStates(turn);
    for(TicTacToe board: boards) {
        out.push_back(State(otherPlayer(turn), board));
    }
    return out;
}

// Default board of our current game (e.g. Tic Tac Toe), default white's turn
State::State() : turn(white), board(TicTacToe()) {
    updateGameStatus();
}

State::State(PlayerColour turn, TicTacToe board) : turn(turn), board(board) {
    updateGameStatus();
}

// A totally decorative wrapper for our current game's (e.g. Tic Tac Toe's) getGameStatus function.
void State::updateGameStatus() {
    gameStatus = board.getGameStatus();
}

// A totally decorative wrapper for our current game's (e.g. Tic Tac Toe's) getStringBoard function.
std::string State::getStringBoard() {
    return board.boardToString();
}

PlayerColour State::getTurn() {
    return turn;
}
