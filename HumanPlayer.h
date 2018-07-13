#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    // ensures: underlying Player is constructed with the passed number
    HumanPlayer(size_t number);

    // calls the given visitor on this object
    void play(const PlayerVisitor * pv) override;
    
}; // HumanPlayer

#endif
