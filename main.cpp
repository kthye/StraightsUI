/*
 * MVC example of GTKmm program
 *
 * Displays top card of sorted deck of cards. When "next" button is clicked,
 * the next card is displayed on top of deck.  When the "reset" button is
 * clicked, the top card of a full sorted deck is displayed
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include <gtkmm/main.h>
#include "StraightsModel.h"
#include "StraightsController.h"
#include "StraightsView.h"

int main( int argc, char * argv[] ) {
	Gtk::Main  kit( argc, argv );         // Initialize gtkmm with the command line arguments, as appropriate.
	StraightsModel model;                          // Create model
        StraightsController controller( &model );  // Create controller
	StraightsView view( &controller, &model );     // Create the view -- is passed handle to controller and model
	Gtk::Main::run( view );               // Show the window and return when it is closed.

	return 0;
} // main
