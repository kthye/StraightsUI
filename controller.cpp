/*
 * MVC example of GTKmm program
 *
 * Controller class.  Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "controller.h"
#include "GameLogic.h"
#include "CardList.h"

Controller::Controller(Model * m) : model_{m}, play_controller_{m} {}

void Controller::newGame(const std::vector<Model::PlayerType> & types, int seed) {
    model_->newGame(types, seed);
}

void Controller::newRound() {
    model_->newRound();
}

void Controller::play(const Card * c) {
    model_->clearError();

    CardList legal_plays = model_->currLegalPlays();
    if (legal_plays.contains(c)) {
        model_->playCard(c);
    } else if (!legal_plays.isEmpty()) {
        model_->setError(Model::ILLEGAL_DISCARD);
    } else {
        model_->discardCard(c);
    }
}

void Controller::ragequit() {
    model_->ragequit();
}

void Controller::updateGame() {
    if (model_->state() == Model::IN_ROUND) {
        if (GameLogic::isGameOver(model_->players())) {
            model_->endGame();
        } else if (GameLogic::isRoundOver(model_->players())) {
            model_->endRound();
        } else {
            model_->playCurrPlayer(&play_controller_);
        }
    }
}
