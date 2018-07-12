#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(size_t number);
    ~HumanPlayer();
    void play(const PlayerVisitor * pv) override;
};

#endif
