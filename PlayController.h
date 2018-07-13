#ifndef PLAY_CONTROLLER_H
#define PLAY_CONTROLLER_H

#include "PlayerVisitor.h"

class HumanPlayer;
class ComputerPlayer;
class Model;

class PlayController : public PlayerVisitor {
    Model * model_;
public:
    // requires: model is a valid pointer to the game's model
    PlayController(Model * model);

    // waits for human input
    void visitPlayer(const HumanPlayer & hp) const override;

    // executes the computer's turn
    void visitPlayer(const ComputerPlayer & cp) const override;
};

#endif
