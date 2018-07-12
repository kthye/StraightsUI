#include "Player.h"
#include "model.h"

Player::Player(size_t number)
    : score_{0}, number_{number} {}

const CardList & Player::hand() const {
    return hand_;
}

const CardList & Player::discard() const {
    return discard_;
}

size_t Player::score() const {
    return score_;
}

size_t Player::number() const {
    return number_;
}

bool Player::isHandEmpty() const {
    return hand_.isEmpty();
}

void Player::setHand(CardList && hand) {
    hand_ = std::move(hand);
}

void Player::removeFromHand(const Card * c) {
    hand_.removeCard(*c);
}

void Player::addToDiscard(const Card * c) {
    discard_.addCard(c);
}

void Player::incrementScore(int score) {
  score_ += score;
}

void Player::resetScore() {
    score_ = 0;
}

void Player::clearDiscard() {
    discard_.clear();
}
