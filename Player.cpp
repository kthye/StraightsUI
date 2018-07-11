#include "Player.h"

Player::Player(PlayerType type)
    : score_{0}, type_{type} {}

const CardList & Player::hand() const {
    return hand_;
}

const CardList & Player::discard() const {
    return discard_;
}

size_t Player::score() const {
    return score_;
}

PlayerType Player::type() const {
    return type_;
}

void Player::setHand(CardList && hand) {
    hand_ = std::move(hand);
}

void Player::setType(PlayerType type) {
    type_ = type;
}

void Player::removeFromHand(const Card * c) {
    hand_.removeCard(*c);
}

void Player::addToDiscard(const Card * c) {
    discard_.addCard(c);
}
