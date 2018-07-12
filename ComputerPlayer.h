#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Player.h"

class ComputerPlayer : public Player {
public:
    // ensures: underlying Player is constructed with the passed view
    ComputerPlayer(size_t number);

    // Used for ragequit: we construct a ComputerPlayer from the HumanPlayer it's replacing
    // requires: passed player will no longer participate in the game
    // ensures: underlying Player is move constructed with the passed player
    ComputerPlayer(Player && player);

    // ensures: memory is freed
    // Note that, like Player, ComputerPlayer doesn't own any heap-allocated memory
    ~ComputerPlayer();

    void play(const PlayerVisitor * pv) override;
};

#endif
