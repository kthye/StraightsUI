#include "HumanPlayer.h"
#include "PlayerVisitor.h"

HumanPlayer::HumanPlayer(size_t number)
    : Player(number) {}

void HumanPlayer::play(const PlayerVisitor * pv) {
    pv->visitPlayer(*this);
}
