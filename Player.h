#ifndef PLAYER_H
#define PLAYER_H

#include "CardList.h"

class Player {
    // Spec fields
    // hand - the cards in the player's hand
    // discard - the cards in the player's discard
    // score - the player's overall score

    // The player's hand and discard
    CardList hand_, discard_;

    // The player's overall score
    size_t score_;

public:
    // modifies: hand, discard, score
    // ensures: hand and discard are initialized empty
    // ensures: score is initialized to 0
    Player();

    const CardList & hand() const;
    const CardList & discard() const;
    size_t score() const;

    void setHand(CardList && hand);
};

#endif
