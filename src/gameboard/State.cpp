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
    // We try this to improve the time spent in push_back
    out.reserve(boards.size());
    for(const TicTacToe& each_board: boards) {
        out.emplace_back(State(otherPlayer(turn), each_board));
    }
    return out;
}

// Default board of our current game (e.g. Tic Tac Toe), default white's turn
State::State(int n, int d) : turn(white), board(TicTacToe(n, d)) {}

State::State(PlayerColour turn, const TicTacToe& board) : turn(turn), board(board) {}

// A totally decorative wrapper for our current game's (e.g. Tic Tac Toe's) getStringBoard function.
std::string State::getStringBoard() {
    return board.boardToString();
}

PlayerColour State::getTurn() const {
    return turn;
}

TicTacToe State::getBoard() const {
    return board;
}

// I'm writing this like java because I don't know how overloading comparison operators works
bool State::operator==(const State& s2) const {
    return turn == s2.turn && board == s2.board;
}