#include "HumanPlayer.h"
#include "PlayerVisitor.h"

HumanPlayer::HumanPlayer(size_t number)
    : Player(number) {}

HumanPlayer::~HumanPlayer() {}

void HumanPlayer::play(const PlayerVisitor * pv) {
    pv->visitPlayer(*this);
}
