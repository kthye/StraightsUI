#ifndef PLAYER_H
#define PLAYER_H

#include "CardList.h"

class PlayerVisitor;

class Player {
    // Spec fields
    // hand - the cards in the player's hand
    // discard - the cards in the player's discard
    // score - the player's overall score

    // The player's hand and discard
    CardList hand_, discard_;

    // The player's overall score
    size_t score_;

    // This player's number (e.g. Player 2 has number 2)
    size_t number_;

public:
    // modifies: hand, discard, score
    // ensures: hand and discard are initialized empty
    // ensures: score is initialized to 0
    Player(size_t number);

    const CardList & hand() const;
    const CardList & discard() const;
    size_t score() const;
    size_t number() const;
    bool isHandEmpty() const;

    void setHand(CardList && hand);
    void removeFromHand(const Card * c);
    void addToDiscard(const Card * c);
    void incrementScore(int score);
    void resetScore();
    void playCard(const Card * c);

    virtual void play(const PlayerVisitor * pv) = 0;
};

#endif
