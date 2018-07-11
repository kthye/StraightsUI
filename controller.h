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

class Model;
enum PlayerType;

class Controller {
    // Performs the computer's turn until a human player turn is reached
    void playComputer();
public:
   Controller( Model* );
   void newGame(const std::vector<PlayerType> & types, int seed = 0);
   void playCard(const Card * c);
private:
   Model *model_;
}; // Controller


#endif
