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

Controller::Controller(Model *m) : model_(m) {}


void Controller::newGame(const std::vector<PlayerType> & types, int seed) {
    model_->newGame(types, seed);
}

void Controller::playCard(const Card * c) {
    model_->clearError();
    model_->playCard(c);
}

void Controller::playComputer() {

}
