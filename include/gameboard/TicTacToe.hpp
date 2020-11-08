#ifndef SERIAL_TICTACTOE_HPP
#define SERIAL_TICTACTOE_HPP

#include <string>
#include <array>
#include "common.hpp"

// Defines the rules of Hypercube Tic Tac Toe
class TicTacToe {
private:
    // Our board is actually 2 boards, the white and black boards. 1 corresponds to a taken square.
    // These boards are of size n^d.
    std::vector<int> whiteBoard;
    std::vector<int> blackBoard;

    // The length of a single side of the board
    int n;
    // The number of dimensions of the board
    int d;

    // The number of moves occurring before this board
    int numMoves;

    // The status of the board
    GameStatus status;

    void updateGameStatus(PlayerColour lastTurn, int lastPosition);
public:
    TicTacToe(int n, int d);
    TicTacToe(int n, int d, std::vector<int> _whiteBoard, std::vector<int> _blackBoard, int numMoves);
    std::vector<TicTacToe> getAllLegalMoveStates(PlayerColour turn);
    std::string boardToString();
    GameStatus getGameStatus();
    void setGameStatus(GameStatus _status);
    int getSize() const;
    bool operator==(const TicTacToe& t2) const;
    std::vector<int> getWhiteBoard() const;
    std::vector<int> getBlackBoard() const;
    int getNumMoves() const;
    int getN() const;
    int getD() const;
};


#endif //SERIAL_TICTACTOE_HPP
