#include "PlayController.h"
#include "GameLogic.h"
#include "model.h"
#include "CardList.h"
#include "ComputerPlayer.h"

PlayController::PlayController(Model * model) : model_{model} {}

void PlayController::visitPlayer(const HumanPlayer & hp) const {
    // Wait for view to call model.playCard
}

void PlayController::visitPlayer(const ComputerPlayer & cp) const {
    CardList plays = GameLogic::getLegalPlays(model_->playArea(), cp.hand());
    if (plays.isEmpty()) {
        model_->playCard(*cp.hand().begin());
    } else {
        model_->playCard(*plays.begin());
    }
}
