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


#ifndef MVC_CONTROLLER_H
#define MVC_CONTROLLER_H

#include <gtkmm.h>
#include "Card.h"
#include "Player.h"
#include "observer.h"
#include "model.h"
#include "PlayController.h"

class Controller : public Observer {
    PlayController play_controller_;
public:
   Controller( Model* );
   void newGame(const std::vector<PlayerType> & types, int seed = 0);
   void newRound();
   void playCard(const Card * c);
   void ragequit(size_t number);

   void update() override;
private:
   Model *model_;
}; // Controller


#endif
