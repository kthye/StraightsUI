#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include "DeckGUI.h"
#include <iostream>

View::View(Controller *c, Model *m) : model_(m), controller_(c), panels(false,10), menuBar(true, 10), newGameButton( "New Game" ),
endGameButton( "End Game" ), table(), scoreboard(true, 10), hand(true, 10), card(deck.null()) {

	// Sets some properties of the window.
    set_title("Straights");
	set_border_width(10);
	
	// Add panels to the window
	add(panels);

	// Set menu bar on top, followed by the table, scoreboard and hand
	panels.add(menuBar);
	panels.add(table);
	panels.add(scoreboard);
	panels.add(hand);
	card.set(deck.null());

	// Add buttons to the box (a container). Buttons initially invisible
	menuBar.add(newGameButton);
	menuBar.add(endGameButton);

	// Associate button "clicked" events with local onButtonClicked() method defined below.
	newGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::nextButtonClicked ) );
	endGameButton.signal_clicked().connect( sigc::mem_fun( *this, &View::resetButtonClicked ) );

	// Define table spacing
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

	// Add rage button to scoreboard
	for (int i = 0; i < 4; i++) {
		rageButtons.push_back(new Gtk::Button("rage quit"));
		scoreboard.add(*rageButtons.at(i));
	}

	// Add empty cards to hand
	for (int i = 0; i < 13; i++) {
		handCards.push_back(new Gtk::Image(deck.null()));
		hand.add(*handCards.at(i));
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
