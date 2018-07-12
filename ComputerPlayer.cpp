#include "ComputerPlayer.h"
#include "GameLogic.h"
#include "PlayerVisitor.h"

#include <iostream>
using namespace std;

ComputerPlayer::ComputerPlayer(size_t number)
    : Player(number) {}

ComputerPlayer::ComputerPlayer(Player && player)
    : Player(std::move(player)) {}

ComputerPlayer::~ComputerPlayer() {}

void ComputerPlayer::play(const PlayerVisitor * pv) {
    pv->visitPlayer(*this);
}
