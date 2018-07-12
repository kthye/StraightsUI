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
#include "model.h"
#include "GameLogic.h"

Controller::Controller(Model *m) : play_controller_{m}, model_(m) {
    model_->subscribe(this);
}


void Controller::newGame(const std::vector<PlayerType> & types, int seed) {
    model_->newGame(types, seed);
}

void Controller::newRound() {
    model_->newRound();
}

void Controller::playCard(const Card * c) {
    model_->clearError();
    model_->playCard(c);
}

void Controller::ragequit(size_t number) {
    model_->ragequit(number);
}

void Controller::update() {
    if (model_->roundInProgress() && GameLogic::isRoundOver(model_->players())) {
        model_->endRound();
        if (GameLogic::isGameOver(model_->players())) {
            model_->endGame();
        }
    } else if (model_->roundInProgress()) {
        model_->play(&play_controller_);
    }
}
