#include <cstring>
#include <iterator>
#include <utility>
#include "../../include/gameboard/TicTacToe.hpp"

TicTacToe::TicTacToe(int n, int d) {
    // The default (empty) starting board
    this->n = n;
    this->d = d;

    int size = getSize();
    whiteBoard = std::vector<int>(size, 0);
    blackBoard = std::vector<int>(size, 0);

    this->numMoves = 0;

    this->status = inProgress;
}

TicTacToe::TicTacToe(int n, int d, std::vector<int> _whiteBoard, std::vector<int> _blackBoard, int _numMoves) {
    this->n = n;
    this->d = d;

    this->whiteBoard = std::move(_whiteBoard);
    this->blackBoard = std::move(_blackBoard);

    this->numMoves = _numMoves;
}

// Returns a vector of all TicTacToe boards possible after one legal move by the player whose turn it is.
std::vector<TicTacToe> TicTacToe::getAllLegalMoveStates(PlayerColour turn) {
    int size = getSize();
    std::vector<TicTacToe> out = std::vector<TicTacToe>();
    // We try this to improve the time spent in push_back
    out.reserve(size - numMoves);
    std::vector<int>* oldBoard = turn == white ? &whiteBoard : &blackBoard;
    std::vector<int> newBoard;

    std::vector<int>* otherBoard = turn == white ? &blackBoard : &whiteBoard;
    std::vector<int> otherBoardCopy;

    for (int i = 0; i < size; i++) {
        if ((*oldBoard)[i] == 0 && (*otherBoard)[i] == 0) {
            newBoard = *oldBoard;
            newBoard[i] = 1;
            otherBoardCopy = *otherBoard;

            if (turn == white) {
                TicTacToe newGame = TicTacToe(n, d, newBoard, otherBoardCopy, numMoves + 1);
                newGame.updateGameStatus(turn, i);
                out.push_back(newGame);
            } else {
                TicTacToe newGame = TicTacToe(n, d, otherBoardCopy, newBoard, numMoves + 1);
                newGame.updateGameStatus(turn, i);
                out.push_back(newGame);
            }

        }
    }
    return out;
}

// Determines whether the player of colour lastTurn has won, whether the game is drawn, or still ongoing.
// The last move was at index lastPosition in the board.
void TicTacToe::updateGameStatus(PlayerColour lastTurn, int lastPosition) {
    int size = getSize();
    // We only check this board for a win
    std::vector<int>* board = lastTurn == white ? &whiteBoard : &blackBoard;
    GameStatus win = lastTurn == white ? whiteWin : blackWin;

    // Check every row, column, diagonal to see if someone has won
    // This only works for d=3. Implementing a solution for the generalized problem for any d is nontrivially
    // difficult, and is not the point of this project
    // Being able to vary to any n gives us sufficient scalability of the problem to test our program.
    int lastX = lastPosition % n;
    int lastY = (lastPosition / n) % n;
    int lastZ = lastPosition / (n * n);

    // Single direction lines
    int completed_line = 1;

    for (int i = 0; i < n; i++) {
        // X line
        if((*board)[i + lastY * n + lastZ * n * n] == 0) {
            // We could use a goto here but... yea
            completed_line = 0;
            break;
        }
    }
    if (completed_line) {
        this->status = win;
        return;
    }

    completed_line = 1;

    for (int i = 0; i < n; i++) {
        // Y line
        if((*board)[lastX + i * n + lastZ * n * n] == 0) {
            // We could use a goto here but... yea
            completed_line = 0;
            break;
        }
    }
    if (completed_line) {
        this->status = win;
        return;
    }


    completed_line = 1;

    for (int i = 0; i < n; i++) {
        // Z line
        if((*board)[lastX + lastY * n + i * n * n] == 0) {
            // We could use a goto here but... yea
            completed_line = 0;
            break;
        }
    }
    if (completed_line) {
        this->status = win;
        return;
    }

    // 2 direction lines
    if (lastX == lastY) {
        completed_line = 1;

        for (int i = 0; i < n; i++) {
            // X-Y diagonal
            if((*board)[i + i * n + lastZ * n * n] == 0) {
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

    if (lastX == lastZ) {
        completed_line = 1;

        for (int i = 0; i < n; i++) {
            // X-Z diagonal
            if((*board)[i + lastY * n + i * n * n] == 0) {
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

    if (lastY == lastZ) {
        completed_line = 1;

        for (int i = 0; i < n; i++) {
            // Y-Z diagonal
            if((*board)[lastX + i * n + i * n * n] == 0) {
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

    if (lastX == n - lastY - 1) {
        completed_line = 1;

        for (int i = 0; i < n; i++) {
            // Other X-Y diagonal
            if((*board)[i + (n - i - 1) * n + lastZ * n * n] == 0) {
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

    if (lastX == n - lastZ - 1) {
        completed_line = 1;

        for (int i = 0; i < n; i++) {
            // Other X-Z diagonal
            if((*board)[i + lastY * n + (n - i - 1) * n * n] == 0) {
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

    if (lastY == n - lastZ - 1) {
        completed_line = 1;

        for (int i = 0; i < n; i++) {
            // Other Y-Z diagonal
            if((*board)[lastX + i * n + (n - i - 1) * n * n] == 0) {
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

    // 3 direction lines
    if (lastX == lastY && lastX == lastZ) {
        completed_line = 1;

        for (int i = 0; i < n; i++) {
            // X-Y-Z diagonal
            if((*board)[i + i * n + i * n * n] == 0) {
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

    if (lastX == lastY && lastX == n - lastZ - 1) {
        completed_line = 1;

        for (int i = 0; i < n; i++) {
            // Next X-Y-Z diagonal
            if((*board)[i + i * n + (n - i - 1) * n * n] == 0) {
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

    if (lastX == n - lastY - 1 && lastX == lastZ) {
        completed_line = 1;

        for (int i = 0; i < n; i++) {
            // Another X-Y-Z diagonal
            if((*board)[i + (n - i - 1) * n + i * n * n] == 0) {
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

    if (lastX == n - lastY - 1 && lastX == n - lastZ - 1) {
        completed_line = 1;

        for (int i = 0; i < n; i++) {
            // Last X-Y-Z diagonal
            if((*board)[i + (n - i - 1) * n + (n - i - 1) * n * n] == 0) {
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

    // Check if it's drawn or still going
    status = numMoves == size ? draw : inProgress;
}

// Returns a (crappy) string representation of the current board.
std::string TicTacToe::boardToString() {
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
    if (n != 3 || d != 3) {
        return "Woops!\n";
    }
    // This only works for n=3, d=3
    std::string out = "";
    for (int i = 0; i < 3; i++) {
        out += "Layer ";
        out += std::to_string(i + 1);
        out += "\n-------\n";
        for (int j = 0; j < 3; j++) {
            out += '|';
            for (int k = 0; k < 3; k++) {
                char c;
                if (whiteBoard[k + j * 3 + i * 9] == 1) {
                    c = 'O';
                } else if (blackBoard[k + j * 3 + i * 9] == 1) {
                    c = 'X';
                } else {
                    c = ' ';
                }
                out += c;
                out += '|';
            }
            out += '\n';
            out += "-------\n";
        }
    }
    return out + "\n";
}

GameStatus TicTacToe::getGameStatus() {
    return this->status;
}

// Returns the size of the board
int TicTacToe::getSize() const {
    return pow(n, d);
}

// Checks if two boards are the same, just check size and tokens
bool TicTacToe::operator==(const TicTacToe& t2) const {
    return n == t2.n && d == t2.d && whiteBoard == t2.whiteBoard && blackBoard == t2.blackBoard;
}

std::vector<int> TicTacToe::getWhiteBoard() const{
    return whiteBoard;
}

std::vector<int> TicTacToe::getBlackBoard() const{
    return blackBoard;
}

int TicTacToe::getNumMoves() const {
    return numMoves;
}


TicTacToe::~TicTacToe() {
//    delete[] whiteBoard;
//    delete[] blackBoard;
}
