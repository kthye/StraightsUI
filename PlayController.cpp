#include "PlayController.h"
#include "GameLogic.h"
#include "StraightsModel.h"
#include "CardList.h"
#include "ComputerPlayer.h"


PlayController::PlayController(StraightsModel * model) : model_{model} {}

void PlayController::visitPlayer(const HumanPlayer & hp) const {
    // Wait for view to call model_->playCard()
}

void PlayController::visitPlayer(const ComputerPlayer & cp) const {
    CardList plays = GameLogic::getLegalPlays(model_->playArea(), cp.hand());
    if (plays.isEmpty()) {
        model_->discardCard(*cp.hand().begin());
    } else {
        model_->playCard(*plays.begin());
    }
}
