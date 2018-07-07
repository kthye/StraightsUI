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

class StraightsModel;

class Controller {
public:
   Controller( StraightsModel* );
   void nextButtonClicked();
   void resetButtonClicked();
private:
   StraightsModel *model_;
}; // Controller


#endif

