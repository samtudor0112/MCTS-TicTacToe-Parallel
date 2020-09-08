//
// Created by sam on 8/9/20.
//

#ifndef SERIAL_TICTACTOE_HPP
#define SERIAL_TICTACTOE_HPP


#include <string>
#include <array>
#include "common.hpp"

// Defines the rules of tic tac toe
class TicTacToe {
private:
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
