#include "../../include/gameboard/common.hpp"

PlayerColour otherPlayer(PlayerColour us) {
    return us == white ? black : white;
}
