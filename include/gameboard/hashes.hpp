#ifndef PARALLEL_HASHES_HPP
#define PARALLEL_HASHES_HPP

#include <vector>
#include "TicTacToe.hpp"
#include "State.hpp"

// Hash for vectors
// Source: https://stackoverflow.com/a/27216842
struct vector_hash {
    std::size_t operator()(std::vector<int> const& vec) const {
        std::size_t seed = vec.size();
        for(auto& i : vec) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    };
};

// Hash for boards
// Gets the white and black board hashes and adds them
struct board_hash {
    std::size_t operator()(const TicTacToe& tic) const {
        return vector_hash()(tic.getWhiteBoard()) + vector_hash()(tic.getBlackBoard());
    }
};

// Hash for state
// Gets the board hash and just adds the turn
struct state_hash {
    std::size_t operator()(const State& state) const {
        return board_hash()(state.getBoard()) + (int)state.getTurn();
    }
};

#endif //PARALLEL_HASHES_HPP
