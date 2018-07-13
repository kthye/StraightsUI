#include "ComputerPlayer.h"
#include "PlayerVisitor.h"

ComputerPlayer::ComputerPlayer(size_t number)
    : Player(number) {}

ComputerPlayer::ComputerPlayer(Player && player)
    : Player(std::move(player)) {}

void ComputerPlayer::play(const PlayerVisitor * pv) {
    pv->visitPlayer(*this);
}
