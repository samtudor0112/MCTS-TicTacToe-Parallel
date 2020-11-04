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
    int[] otherBoard = turn == white ? blackBoard : whiteBoard;

    for (int i = 0; i < size; i++) {
        if (oldBoard[i] == 0 && otherBoard[i] == 0) {
            newBoard = malloc(sizeof(int) * size);
            memcpy(newBoard, oldBoard, sizeof(int) * size);
            newBoard[i] = 1;
            TicTacToe newGame;
            if (turn == white) {
                newGame = TicTacToe(n, d, newBoard, otherBoard, numMoves + 1);
            } else {
                newGame =  TicTacToe(n, d, otherBoard, newBoard, numMoves + 1);
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
    // This only works for d=3. Solving the generalized problem for any d is nontrivially difficult, and is not the point of this project
    // Being able to vary to any n gives us sufficient scalability of the problem to test our program.
    int lastX = lastPosition % n;
    int lastY = (lastPosition / n) % n;
    int lastZ = lastPosition / (n * n);


    // Single direction lines
    int completed_line = 1;

    for (int i = 0; i < n; i++) {
        // X line
        if(board[i + lastY * n + lastZ * n * n] == 0) {
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
        if(board[lastX + i * n + lastZ * n * n] == 0) {
            // We could use a goto here but... yea
            completed_line = 0;
            break;
        }
    }
    if (completed_line) {
        this->status = win;
        return;
    }


    int completed_line = 1;

    for (int i = 0; i < n; i++) {
        // Z line
        if(board[lastX + lastY * n + i * n * n] == 0) {
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
            if(board[i + i * n + lastZ * n * n] == 0) {
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
            if(board[i + lastY * n + i * n * n] == 0) {
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
            if(board[lastX + i * n + i * n * n] == 0) {
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
            if(board[i + (n - i - 1) * n + lastZ * n * n] == 0) {
                // We could use a goto here but... yea
                completed_line = 0;
                break;
            }
        }
        if (completed_line) {
            this->status = win;
            return
        }
    } 

    if (lastX == n - lastZ - 1) {
        completed_line = 1;

        for (int i = 0; i < n; i++) {
            // Other X-Z diagonal
            if(board[i + lastY * n + (n - i - 1) * n * n] == 0) {
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
            if(board[lastX + i * n + (n - i - 1) * n * n] == 0) {
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
            if(board[i + i * n + i * n * n] == 0) {
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
            if(board[i + i * n + (n - i - 1) * n * n] == 0) {
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
            if(board[i + (n - i - 1) * n + i * n * n] == 0) {
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
            if(board[i + (n - i - 1) * n + (n - i - 1) * n * n] == 0) {
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
