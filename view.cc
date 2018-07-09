/*
 * MVC example of GTKmm program
 *
 * View class.  Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include "DeckGUI.h"
#include <iostream>

struct View::Player {
	Gtk::Button rage;
	Player() : rage("Rage Quit") {}
};

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
View::View(Controller *c, Model *m) : model_(m), controller_(c), panels(false,10), menuBar(true, 10), table(), next_button( "next" ),
reset_button( "reset" ), card(deck.null()) {

	// Sets some properties of the window.
    set_title( "CS246 MVC example" );
	set_border_width( 10 );
	
	// Add panels to the window
	add(panels);

	// Set menu bar, table and players
	panels.add(menuBar);
	panels.add(table);
	panels.add(scoreboard);
	card.set( deck.null() );

	// Add buttons to the box (a container). Buttons initially invisible
	menuBar.add( next_button );
	menuBar.add( reset_button );

	// Associate button "clicked" events with local onButtonClicked() method defined below.
	next_button.signal_clicked().connect( sigc::mem_fun( *this, &View::nextButtonClicked ) );
	reset_button.signal_clicked().connect( sigc::mem_fun( *this, &View::resetButtonClicked ) );
	
	players.push_back(new Player());
	players.push_back(new Player());
	players.push_back(new Player());
	players.push_back(new Player());

	// players
	scoreboard.add(players.at(0)->rage);
	scoreboard.add(players.at(1)->rage);
	scoreboard.add(players.at(2)->rage);
	scoreboard.add(players.at(3)->rage);

	table.set_row_spacing(10);
	table.set_column_spacing(10);

	// Add cards to table
	for (int y = 0; y < 4; y++) {
		vector<Gtk::Image*> rows;
		for (int x = 0; x < 13; x++) {
			Gtk::Image* temp = new Gtk::Image(deck.null());
			rows.push_back(temp);
			table.attach(*temp, x, y, temp->get_width(), temp->get_height());
		}
		tableSlots.push_back(rows);
	}

	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

View::~View() {}


void View::update() {
  Suits suit = model_->suit();
  Faces face = model_->face();
  if ( suit == NOSUIT ) 
    card.set( deck.null() );
  else
    card.set( deck.image(face, suit) );

}

void View::nextButtonClicked() {
  controller_->nextButtonClicked();
} // View::nextButtonClicked

void View::resetButtonClicked() {
  controller_->resetButtonClicked();
} // View::resetButtonClicked
