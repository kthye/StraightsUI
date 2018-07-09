#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include <iostream>

View::View(Controller *c, Model *m) : model_(m), deck(), panels(false, 10), menuBar(true, 10), newGameButton("New Game"),
endGameButton("End Game"), table(), scoreboard(true, 10), hand(true, 10) {

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
	setTableRow(model_->getPlayArea(), CLUB);
	setTableRow(model_->getPlayArea(), DIAMOND);
	setTableRow(model_->getPlayArea(), HEART);
	setTableRow(model_->getPlayArea(), SPADE);

}

void View::setTableRow(const SortedCardList &playArea, Suit suit) {
	switch (suit) {
	case CLUB:
		for (auto it = playArea.clubs_begin(); it != playArea.clubs_end(); ++it) {
			int x = static_cast<int>((*it)->getRank());
			int y = 0;
			std::vector<Gtk::Image*> &tableRow = tableSlots.at(y);

			table.remove(*tableRow.at(x));

			delete tableRow.at(x);
			tableRow.at(x) = new Gtk::Image(deck.cardImage(**it));

			table.attach(*tableRow.at(x), x, y, tableRow.at(x)->get_width(), tableRow.at(x)->get_height());
		}
		break;
	case DIAMOND:
		for (auto it = playArea.diamonds_begin(); it != playArea.diamonds_end(); ++it) {
			int x = static_cast<int>((*it)->getRank());
			int y = 1;
			std::vector<Gtk::Image*> &tableRow = tableSlots.at(y);

			table.remove(*tableRow.at(x));

			delete tableRow.at(x);
			tableRow.at(x) = new Gtk::Image(deck.cardImage(**it));

			table.attach(*tableRow.at(x), x, y, tableRow.at(x)->get_width(), tableRow.at(x)->get_height());
		}
		break;
	case HEART:
		for (auto it = playArea.hearts_begin(); it != playArea.hearts_end(); ++it) {
			int x = static_cast<int>((*it)->getRank());
			int y = 2;
			std::vector<Gtk::Image*> &tableRow = tableSlots.at(y);

			table.remove(*tableRow.at(x));

			delete tableRow.at(x);
			tableRow.at(x) = new Gtk::Image(deck.cardImage(**it));

			table.attach(*tableRow.at(x), x, y, tableRow.at(x)->get_width(), tableRow.at(x)->get_height());
		}
		break;
	case SPADE:
		for (auto it = playArea.spades_begin(); it != playArea.spades_end(); ++it) {
			int x = static_cast<int>((*it)->getRank());
			int y = 3;
			std::vector<Gtk::Image*> &tableRow = tableSlots.at(y);

			table.remove(*tableRow.at(x));

			delete tableRow.at(x);
			tableRow.at(x) = new Gtk::Image(deck.cardImage(**it));

			table.attach(*tableRow.at(x), x, y, tableRow.at(x)->get_width(), tableRow.at(x)->get_height());
		}
		break;
	default:
		break;
	}
}

