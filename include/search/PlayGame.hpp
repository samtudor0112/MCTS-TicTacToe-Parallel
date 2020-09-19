#ifndef SERIAL_PLAYGAME_HPP
#define SERIAL_PLAYGAME_HPP

#include "../gameboard/common.hpp"
#include "../gameboard/State.hpp"

GameStatus play_game(State startState, double timeToUse, bool print);

double play_game_vps(State startState, double timeToUse, bool print);

#endif //SERIAL_PLAYGAME_HPP
