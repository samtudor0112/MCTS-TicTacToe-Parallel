#ifndef SERIAL_TICTACTOE_HPP
#define SERIAL_TICTACTOE_HPP

#include <string>
#include <array>
#include "common.hpp"

// Defines the rules of Tic Tac Toe
class TicTacToe {
private:
    // Our board is is actually 2 boards, the white and black boards. 1 corresponds to a taken square.
    int[] whiteBoard;
    int[] blackBoard;

    int n;
    int d;

    int numMoves;

    GameStatus status;

    void updateGameStatus(PlayerColour lastTurn, int lastPosition);
public:
    TicTacToe(int n, int d);
    TicTacToe(int n, int d, int[] _whiteBoard, int[] _blackBoard);
    std::vector<TicTacToe> getAllLegalMoveStates(PlayerColour turn);
    std::string boardToString();
    GameStatus getGameStatus();
};


#endif //SERIAL_TICTACTOE_HPP
