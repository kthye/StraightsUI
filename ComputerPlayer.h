#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Player.h"

class ComputerPlayer : public Player {
public:
    // ensures: underlying Player is constructed with the passed number
    ComputerPlayer(size_t number);

    // Used for ragequit: we construct a ComputerPlayer from the HumanPlayer it's replacing
    // requires: passed player will no longer participate in the game
    // ensures: underlying Player is move constructed with the passed player
    ComputerPlayer(Player && player);

    // calls the given visitor on this object
    void play(const PlayerVisitor * pv) override;
    
}; // ComputerPlayer

#endif
