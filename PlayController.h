#ifndef PLAY_CONTROLLER_H
#define PLAY_CONTROLLER_H

#include "PlayerVisitor.h"

class SortedCardList;
class HumanPlayer;
class ComputerPlayer;
class Model;

class PlayController : public PlayerVisitor {
    Model * model_;
public:
    PlayController(Model * model);

    void visitPlayer(const HumanPlayer & hp) const;
    void visitPlayer(const ComputerPlayer & cp) const;
};

#endif
