/*
 * Adapted from MVC example by Jo Atlee
 */


#include "StraightsController.h"
#include "GameLogic.h"
#include "CardList.h"

StraightsController::StraightsController(StraightsModel * m) : model_{m}, play_controller_{m} {}

void StraightsController::newGame(const std::vector<StraightsModel::PlayerType> & types, int seed) {
    model_->newGame(types, seed);
}

void StraightsController::newRound() {
    model_->newRound();
}

void StraightsController::play(const Card * c) {
    model_->clearError();

    CardList legal_plays = model_->currLegalPlays();
    if (legal_plays.contains(c)) {
        model_->playCard(c);
    } else if (!legal_plays.isEmpty()) {
        model_->setError(StraightsModel::ILLEGAL_DISCARD);
    } else {
        model_->discardCard(c);
    }
}

void StraightsController::ragequit() {
    model_->ragequit();
}

void StraightsController::updateGame() {
    if (model_->state() == StraightsModel::IN_ROUND && GameLogic::isRoundOver(model_->players())) {
        // We must update scores before checking whether the game is over, as isGameOver
        // checks the current scores of the players
        model_->updateScores();
        if (GameLogic::isGameOver(model_->players())) {
            model_->endGame();
        } else {
            model_->endRound();
        }
    } else if (model_->state() == StraightsModel::IN_ROUND) {
        model_->playCurrPlayer(&play_controller_);
    }
}
