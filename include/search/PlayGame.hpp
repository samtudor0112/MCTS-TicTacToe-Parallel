#ifndef SERIAL_PLAYGAME_HPP
#define SERIAL_PLAYGAME_HPP

#include "../gameboard/common.hpp"
#include "../gameboard/State.hpp"

GameStatus play_game(State startState, double timeToUse, bool print, int numThreads);

double play_game_vps(State startState, double timeToUse, bool print, int numThreads);

#endif //SERIAL_PLAYGAME_HPP
