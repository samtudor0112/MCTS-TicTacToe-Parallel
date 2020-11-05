#ifndef SERIAL_COMMON_HPP
#define SERIAL_COMMON_HPP

#include <random>

// The two possible colours for players, nodes, and turns.
enum PlayerColour {white, black};

// The other player colour from us
PlayerColour otherPlayer(PlayerColour us);

// The four possible states/outcomes of the game
enum GameStatus {whiteWin, blackWin, inProgress, draw};

// Internet solution found to randomly select an element of a vector
// Source: https://stackoverflow.com/a/16421677
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}


#endif //SERIAL_COMMON_HPP
