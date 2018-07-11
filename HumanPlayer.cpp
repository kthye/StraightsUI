#include "HumanPlayer.h"
#include "PlayController.h"

HumanPlayer::HumanPlayer(size_t number)
    : Player(number) {}

HumanPlayer::~HumanPlayer() {}

void HumanPlayer::play(const PlayController & pc) {
    pc.visitPlayer(*this);
}
