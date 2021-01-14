#include <cstring>
#include <iterator>
#include <utility>
#include <iostream>
#include "../../include/gameboard/ConnectFour.hpp"

ConnectFour::ConnectFour(int w, int h) {
    // The default (empty) starting board
    this->w = w;
    this->h = h;

    int size = getSize();
    whiteBoard = std::vector<int>(size, 0);
    blackBoard = std::vector<int>(size, 0);

    this->numMoves = 0;

    this->status = inProgress;
}

ConnectFour::ConnectFour(int w, int h, std::vector<int> _whiteBoard, std::vector<int> _blackBoard, int _numMoves) {
    this->w = w;
    this->h = h;

    this->whiteBoard = std::move(_whiteBoard);
    this->blackBoard = std::move(_blackBoard);

    this->numMoves = _numMoves;
}

// Returns a vector of all ConnectFour boards possible after one legal move by the player whose turn it is.
std::vector<ConnectFour> ConnectFour::getAllLegalMoveStates(PlayerColour turn) {
//    int size = getSize();
    std::vector<ConnectFour> out = std::vector<ConnectFour>();
    // We try this to improve the time spent in push_back
    out.reserve(w);
    std::vector<int>* oldBoard = turn == white ? &whiteBoard : &blackBoard;
    std::vector<int> newBoard;

    std::vector<int>* otherBoard = turn == white ? &blackBoard : &whiteBoard;
    std::vector<int> otherBoardCopy;

    for (int i = 0; i < w; i++) {
        if ((*oldBoard)[getPos(i, h - 1)] == 0 && (*otherBoard)[getPos(i, h - 1)] == 0) {
            // This row has at least one space
            newBoard = *oldBoard;
            otherBoardCopy = *otherBoard;

            int pos;
            for (int j = 0; j < h; j++) {
                pos = getPos(i, j);
                if ((*oldBoard)[pos] == 0 && (*otherBoard)[pos] == 0) {
                    newBoard[pos] = 1;
                    break;
                }
            }

            if (turn == white) {
                ConnectFour newGame = ConnectFour(w, h, newBoard, otherBoardCopy, numMoves + 1);
                newGame.updateGameStatus(turn, pos);
                out.push_back(newGame);
            } else {
                ConnectFour newGame = ConnectFour(w, h, otherBoardCopy, newBoard, numMoves + 1);
                newGame.updateGameStatus(turn, pos);
                out.push_back(newGame);
            }
        }
    }
    return out;
}

// Determines whether the player of colour lastTurn has won, whether the game is drawn, or still ongoing.
// The last move was at index lastPosition in the board.
void ConnectFour::updateGameStatus(PlayerColour lastTurn, int lastPosition) {
    int size = getSize();
    // We only check this board for a win
    std::vector<int>* board = lastTurn == white ? &whiteBoard : &blackBoard;
    GameStatus win = lastTurn == white ? whiteWin : blackWin;

    // Check every row, column, diagonal to see if someone has won
    int lastX = lastPosition / h;
    int lastY = lastPosition % h;

    // Single direction lines


    for (int i = 0; i < 4; i++) {

        if (lastX - i < 0 || lastX - i + 3 >= w) {
            continue;
        }

        int completed_line = 1;

        for (int j = 0; j < 4; j++) {
            // X line
            if ((*board)[getPos(lastX - i + j, lastY)] == 0) {
                // We could use a goto here but... yea
                completed_line = 0;
                break;
            }
        }

        if (completed_line) {
            this->status = win;
            return;
        }
    }

    for (int i = 0; i < 4; i++) {

        if (lastY - i < 0 || lastY - i + 3 >= h) {
            continue;
        }

        int completed_line = 1;

        for (int j = 0; j < 4; j++) {
            // Y line
            if ((*board)[getPos(lastX, lastY - i + j)] == 0) {
                // We could use a goto here but... yea
                completed_line = 0;
                break;
            }
        }

        if (completed_line) {
            this->status = win;
            return;
        }
    }

    // Diagonals

    for (int i = 0; i < 4; i++) {

        if (lastX - i < 0 || lastX - i + 3 >= w || lastY + i - 3 < 0 || lastY + i >= h) {
            continue;
        }

        int completed_line = 1;

        for (int j = 0; j < 4; j++) {
            // Negative gradient line
            if ((*board)[getPos(lastX - i + j, lastY + i - j)] == 0) {
                // We could use a goto here but... yea
                completed_line = 0;
                break;
            }
        }

        if (completed_line) {
            this->status = win;
            return;
        }
    }

    for (int i = 0; i < 4; i++) {

        if (lastX - i < 0 || lastX - i + 3 >= w || lastY - i < 0 || lastY - i + 3 >= h) {
            continue;
        }

        int completed_line = 1;

        for (int j = 0; j < 4; j++) {
            // Positive gradient line
            if ((*board)[getPos(lastX - i + j, lastY - i + j)] == 0) {
                // We could use a goto here but... yea
                completed_line = 0;
                break;
            }
        }

        if (completed_line) {
            this->status = win;
            return;
        }
    }

//    int completed_line = 1;
//
//    for (int i = 0; i < n; i++) {
//        // X line
//        if((*board)[i + lastY * n + lastZ * n * n] == 0) {
//            // We could use a goto here but... yea
//            completed_line = 0;
//            break;
//        }
//    }
//    if (completed_line) {
//        this->status = win;
//        return;
//    }

    // Check if it's drawn or still going
    status = numMoves == size ? draw : inProgress;
}

// Returns a (crappy) string representation of the current board. Only works for n=3, d=3
std::string ConnectFour::boardToString() {
//    std::string out = "-------\n";
//    for (int i = 0; i < 3; i++) {
//        out += '|';
//        for (int j = 0; j < 3; j++) {
//            char c;
//            if (board[j + i * 3] == 0) {
//                c = ' ';
//            } else if (board[j + i * 3] == 1) {
//                c = 'O';
//            } else {
//                c = 'X';
//            }
//            out += c;
//            out += '|';
//        }
//        out += '\n';
//        out += "-------\n";
//    }
//    return out;
    std::string out = "";
    for (int j = h - 1; j >= 0; j--) {
        out += '|';
        for (int k = 0; k < w; k++) {
            char c;
            if (whiteBoard[getPos(k, j)] == 1) {
                c = 'O';
            } else if (blackBoard[getPos(k, j)] == 1) {
                c = 'X';
            } else {
                c = ' ';
            }
            out += c;
            out += '|';
        }
        out += '\n';
        for (int i = 0; i < w * 2 + 1; i++) {
            out += "-";
        }
        out += "\n";
    }
    return out + "\n";
}

GameStatus ConnectFour::getGameStatus() {
    return this->status;
}

// Returns the size of the board
int ConnectFour::getSize() const {
    return w * h;
}

int ConnectFour::getPos(int x, int y) {
    return x * h + y;
}

ConnectFour ConnectFour::textToMove(PlayerColour turn, int x) {
    std::vector<int>* oldBoard = turn == white ? &whiteBoard : &blackBoard;
    std::vector<int> newBoard;

    std::vector<int>* otherBoard = turn == white ? &blackBoard : &whiteBoard;
    std::vector<int> otherBoardCopy;

    if ((*oldBoard)[getPos(x, h - 1)] == 0 && (*otherBoard)[getPos(x, h - 1)] == 0) {
        // This row has at least one space
        newBoard = *oldBoard;
        otherBoardCopy = *otherBoard;

        int pos;
        for (int j = 0; j < h; j++) {
            pos = getPos(x, j);
            if ((*oldBoard)[pos] == 0 && (*otherBoard)[pos] == 0) {
                newBoard[pos] = 1;
                break;
            }
        }

        if (turn == white) {
            ConnectFour newGame = ConnectFour(w, h, newBoard, otherBoardCopy, numMoves + 1);
            newGame.updateGameStatus(turn, pos);
            return newGame;
        } else {
            ConnectFour newGame = ConnectFour(w, h, otherBoardCopy, newBoard, numMoves + 1);
            newGame.updateGameStatus(turn, pos);
            return newGame;
        }
    } else {
        std::cout << "Uh Oh!\n" << std::flush;
        return *this;
    }
}