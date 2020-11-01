#include "../../include/gameboard/TicTacToe.hpp"

TicTacToe::TicTacToe(int n, int d) {
    // The default (empty) starting board
    this->n = n;
    this->d = d;

    int size = pow(n, d);
    this->whiteBoard = calloc(size, sizeof(int));
    this->blackBoard = calloc(size, sizeof(int));

    this->numMoves = 0;

    this->gameStatus = inProgress;
}

TicTacToe::TicTacToe(int n, int d, int[] _whiteBoard, int[] _blackBoard, int _numMoves) {
    this->n = n;
    this->d = d;

    this->whiteBoard = _whiteBoard;
    this->blackBoard = _blackBoard;

    this->numMoves = _numMoves;
}

// Returns a vector of all TicTacToe boards possible after one legal move by the player whose turn it is.
std::vector<TicTacToe> TicTacToe::getAllLegalMoveStates(PlayerColour turn) {
    int size = pow(n, d);
    std::vector<TicTacToe> out = std::vector<TicTacToe>();
    int[] newBoard;
    int[] oldBoard = turn == white ? whiteBoard : blackBoard;

    for (int i = 0; i < size; i++) {
        if (oldBoard[i] == 0) {
            newBoard = malloc(sizeof(int)) * size;
            memcpy(newBord, oldBoard, sizeof(int) * size);
            newBoard[i] = 1;
            TicTacToe newGame;
            if (turn == white) {
                newGame = TicTacToe(n, d, newBoard, blackBoard, numMoves + 1);
            } else {
                newGame =  TicTacToe(n, d, whiteBoard, newBoard, numMoves + 1);
            }
            newGame.updateGameStatus(turn, i);
            out.push_back(newGame);
        }
    }
    return out;
}

// Determines whether the player of colour lastTurn has won, whether the game is drawn, or still ongoing. The last move was at position lastPosition.
void TicTacToe::updateGameStatus(PlayerColour lastTurn, int lastPosition) {
    int size = pow(n, d);
    // We only check this board for a win
    int[] board = lastTurn == white ? whiteBoard : blackBoard;
    gameStatus win = lastTurn == white ? whiteWin : blackWin;

    // Check every row, column, diagonal to see if someone has won
    int sum;
    // TODO
    for (int dimsChanged = 1; dimsChanged <= d; dimsChanged++) {
        // TODO
        this->status = win;
        return;
    }

    // Check if it's drawn or still going
    status = numMoves == size ? draw : inProgress;
}

// Returns a (crappy) string representation of the current board.
std::string TicTacToe::boardToString() {
    std::string out = "-------\n";
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
        out += "-------\n";
    }
    return out;
}

GameStatus TicTacToe::getGameStatus() {
    return this->status;
}
