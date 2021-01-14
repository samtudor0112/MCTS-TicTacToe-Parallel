#ifndef SERIAL_TICTACTOE_HPP
#define SERIAL_TICTACTOE_HPP

#include <string>
#include <array>
#include "common.hpp"

// Defines the rules of Hypercube Tic Tac Toe
class ConnectFour {
private:
    // Our board is actually 2 boards, the white and black boards. 1 corresponds to a taken square.
    // These boards are of size n^d.
    std::vector<int> whiteBoard;
    std::vector<int> blackBoard;

    // The width of the board
    int w;
    // The height of the board
    int h;

    // The number of moves occurring before this board
    int numMoves;

    // The status of the board
    GameStatus status;

    void updateGameStatus(PlayerColour lastTurn, int lastPosition);
public:
    ConnectFour(int w, int h);
    ConnectFour(int w, int h, std::vector<int> _whiteBoard, std::vector<int> _blackBoard, int numMoves);
    std::vector<ConnectFour> getAllLegalMoveStates(PlayerColour turn);
    std::string boardToString();
    GameStatus getGameStatus();
    int getSize() const;
    int getPos(int x, int y);
    ConnectFour textToMove(PlayerColour turn, int x);
};


#endif //SERIAL_TICTACTOE_HPP
