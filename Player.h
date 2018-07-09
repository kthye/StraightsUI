#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "CardList.h"

struct Command;
class SortedCardList;

class Player {
    // Spec fields
    // hand - the cards in the player's hand
    // discard - the cards in the player's discard
    // score - the player's overall score
protected:
    // The player's hand and discard
    CardList hand_, discard_;

private:
    // The player's overall score
    size_t score_;

public:
    // requires: view to be a valid reference to a StraightsView whose lifetime will
    //  be longer than the StraightsGame
    // modifies: hand, discard, score
    // ensures: hand and discard are initialized empty
    // ensures: score is initialized to 0
    // the view argument is used to communicate this player's plays for the rest of the game
    Player();

};

#endif
