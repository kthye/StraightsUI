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


#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <gtkmm.h>
#include "model.h"
#include "PlayController.h"

class Card;

class Controller {
    Model *model_;
    PlayController play_controller_;

public:
   Controller(Model * model);

   void newGame(const std::vector<Model::PlayerType> & types, int seed = 0);
   void newRound();
   void play(const Card * c);
   void ragequit();
   void updateGame();
}; // Controller


#endif
