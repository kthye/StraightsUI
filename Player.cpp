#include "Player.h"
#include "model.h"

////////////////////////////////////////
// Constructors
////////////////////////////////////////

Player::Player(size_t number)
: score_{0}, number_{number} {}

////////////////////////////////////////
// Getters
////////////////////////////////////////

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

////////////////////////////////////////
// Modifiers
////////////////////////////////////////

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

void Player::clearDiscard() {
    discard_.clear();
}
