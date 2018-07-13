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
    Player(Player && other) = default;
    virtual ~Player() = default;

    // returns: the player's hand
    const CardList & hand() const;

    // returns: the player's discard
    const CardList & discard() const;

    // returns: the player's score
    size_t score() const;

    // returns: the player's number
    // this is always the number the player was initialized with
    size_t number() const;

    // modifies: hand
    // ensures: hand has been replaced with the passed argument
    void setHand(CardList && hand);

    // requires: c is a valid pointer to a card in the deck of the current game
    // modifies: hand
    // ensures: c is removed from the player's hand
    void removeFromHand(const Card * c);

    // requires: c is a valid pointer to a card in the deck of the current game
    // modifies: discard
    // ensures: c is added to the player's discard
    void addToDiscard(const Card * c);

    // modifies: score
    // ensures: the player's score is incremented by the passed amount
    void incrementScore(size_t score);

    // modifies: discard
    // ensures: discard is empty
    void clearDiscard();

    // calls play on the passed visitor
    virtual void play(const PlayerVisitor * pv) = 0;
};

#endif
