#include "../../include/gameboard/State.hpp"

// A totally decorative wrapper for our current game's (e.g. Tic Tac Toe's) getGameStatus function.
GameStatus State::getGameStatus() {
    return board.getGameStatus();
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
State::State(int n, int d) : turn(white), board(TicTacToe(n, d)) {}

State::State(PlayerColour turn, TicTacToe board) : turn(turn), board(board) {}

// A totally decorative wrapper for our current game's (e.g. Tic Tac Toe's) getStringBoard function.
std::string State::getStringBoard() {
    return board.boardToString();
}

PlayerColour State::getTurn() {
    return turn;
}

// A totally decorative wrapper to free our board's boards
void State::freeBoards() {
    board.freeBoards();
}
 
