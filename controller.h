/*
 * Adapted from MVC example by Jo Atlee
 */


#ifndef STRAIGHTS_CONTROLLER_H
#define STRAIGHTS_CONTROLLER_H

#include <gtkmm.h>
#include "model.h"
#include "PlayController.h"

class Card;

class Controller {
    // Spec fields
    // model - the complete representation of the game
    Model *model_;
    PlayController play_controller_;

public:
    // requires: model is a valid pointer to a model object
    Controller(Model * model);

    // calls model.newGame, so has the same spec
    void newGame(const std::vector<Model::PlayerType> & types, int seed = 0);

    // calls model.newRound, so has the same spec
    void newRound();

    // requires: round in progress
    // requires: c is a valid pointer to a card in model.deck that is in model.curr_player's hand
    // modifies: model
    // implements logic in the project spec to decide whether c should be played or discarded
    void play(const Card * c);

    // calls model.ragequit, so has the same spec
    void ragequit();

    // modifies: model
    // checks if the round or game should be ended
    void updateGame();

}; // Controller


#endif
