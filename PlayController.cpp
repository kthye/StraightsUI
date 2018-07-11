#include "PlayController.h"
#include "model.h"

PlayController::PlayController(Model * model) : model_{model} {}

void PlayController::visitPlayer(const HumanPlayer & hp) const {
    // Wait for model to call
}

void PlayController::visitPlayer(const ComputerPlayer & cp) const {
    // call playCard with some card
}
