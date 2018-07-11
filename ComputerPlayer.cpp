#include "ComputerPlayer.h"
#include "GameLogic.h"
#include "PlayController.h"

ComputerPlayer::ComputerPlayer(size_t number)
    : Player(number) {}

ComputerPlayer::ComputerPlayer(Player && player)
    : Player(std::move(player)) {}

ComputerPlayer::~ComputerPlayer() {}

void ComputerPlayer::play(const PlayController & pc) {
    pc.visitPlayer(*this);
}
