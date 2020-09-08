#ifndef SERIAL_TICTACTOE_HPP
#define SERIAL_TICTACTOE_HPP

#include <string>
#include <array>
#include "common.hpp"

// Defines the rules of Tic Tac Toe
class TicTacToe {
private:
    // Our board is a 9 element array, left to right then top to bottom
    // We represent empty with 0, white/naughts with 1, black/crosses with -1
    std::array<int, 9> board;
public:
    TicTacToe();
    TicTacToe(std::array<int, 9> board);
    std::vector<TicTacToe> getAllLegalMoveStates(PlayerColour turn);
    std::string boardToString();
    GameStatus getGameStatus();
};


#endif //SERIAL_TICTACTOE_HPP
