#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include <iostream>

View::View(Controller *c, Model *m) : model_(m), panels(false,10), menuBar(true, 10), newGameButton("New Game"),
endGameButton( "End Game" ), table(), scoreboard(true, 10), hand(true, 10) {

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
	// card.set( deck.null() );

	// Add buttons to the box (a container). Buttons initially invisible
	menuBar.add(newGameButton);
	menuBar.add(endGameButton);

	// Define table spacing
	table.set_row_spacing(10);
	table.set_column_spacing(10);

	// Initialize placeholders to table
	for (int y = 0; y < 4; y++) {
		std::vector<Gtk::Image*> rows;
		for (int x = 0; x < 13; x++) {
			Gtk::Image* temp = new Gtk::Image();
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

	// Initialize placeholders to hand
	for (int i = 0; i < 13; i++) {
		handCards.push_back(new Gtk::Image());
		hand.add(*handCards.at(i));
	}

	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

View::~View() {}


void View::update() {
	SortedCardList playArea = model_->getPlayArea();
}

void setTableRow(SortedCardList &playArea, Suit suit) {
	switch (suit) {
	case CLUB:
		for (auto it = playArea.clubs_begin(); it != playArea.clubs_end(); ++it) {
			if (tableSlots.at(0).at((*it)->getRank);
		}
	case DIAMOND:
	case HEART:
	case SPADE:
	default:

	}
}


std::vector<std::unique_ptr<Player>> & getPlayers() const;
Player * getCurrPlayer() const;
SortedCardList & getPlayArea() const;
