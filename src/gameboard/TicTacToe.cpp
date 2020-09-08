#include "../../include/gameboard/TicTacToe.hpp"

TicTacToe::TicTacToe() {
    // The default (empty) starting board
    this->board = {0, 0, 0, 0, 0, 0, 0, 0, 0};
}

TicTacToe::TicTacToe(std::array<int, 9> _board) {
    this->board = _board;
}

// Returns a vector of all TicTacToe boards possible after one legal move by the player whose turn it is.
std::vector<TicTacToe> TicTacToe::getAllLegalMoveStates(PlayerColour turn) {
    std::vector<TicTacToe> out = std::vector<TicTacToe>();
    std::array<int, 9> newBoard = board;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            newBoard[i] = turn == white ? 1 : -1;
            out.push_back(TicTacToe(newBoard));
            newBoard = board;
        }
    }
    return out;
}

// Determines whether either player has won, whether the game is drawn, or still ongoing.
GameStatus TicTacToe::getGameStatus() {
    // Check every row, column, diagonal to see if someone has won
    int sum;
    for (int i = 0; i < 3; i++) {
        // Rows
        sum = board[0 + 3*i] + board[1 + 3*i] + board[2 + 3*i];
        if (sum == 3) {
            return whiteWin;
        } else if (sum == -3) {
            return blackWin;
        }

        // Columns
        sum = board[0 + i] + board[3 + i] + board[6 + i];
        if (sum == 3) {
            return whiteWin;
        } else if (sum == -3) {
            return blackWin;
        }
    }
    // Diagonals
    sum = board[0] + board[4] + board[8];
    if (sum == 3) {
        return whiteWin;
    } else if (sum == -3) {
        return blackWin;
    }

    sum = board[2] + board[4] + board[6];
    if (sum == 3) {
        return whiteWin;
    } else if (sum == -3) {
        return blackWin;
    }

    // Check if its drawn or still going
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            return inProgress;
        }
    }
    return draw;
}

// Returns a (crappy) string representation of the current board.
std::string TicTacToe::boardToString() {
    std::string out = "---\n";
    for (int i = 0; i < 3; i++) {
        out += '|';
        for (int j = 0; j < 3; j++) {
            char c;
            if (board[j + i * 3] == 0) {
                c = ' ';
            } else if (board[j + i * 3] == 1) {
                c = 'O';
            } else {
                c = 'X';
            }
            out += c;
            out += '|';
        }
        out += '\n';
        out += "---\n";
    }
    return out;
}

