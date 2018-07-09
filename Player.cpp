#include "Player.h"

Player::Player()
    : score_{0} {}

const CardList & Player::hand() const {
    return hand_;
}

const CardList & Player::discard() const {
    return discard_;
}

size_t Player::score() const {
    return score_;
}
