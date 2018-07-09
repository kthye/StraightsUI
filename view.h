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


#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include <gtkmm/grid.h>
#include <vector>
#include "observer.h"
#include "DeckGUI.h"
#include "SortedCardList.h"
#include "model.h"

class Controller;
class Model;


class View : public Gtk::Window, public Observer {
public:
    View( Controller*, Model* );
	virtual ~View();
	virtual void update();	// Observer Pattern: concrete update() method

private:
	void setTableRow(const SortedCardList &playArea, Suit suit);
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;

	DeckGUI deck;

	// Member widgets:
	Gtk::VBox panels;

	Gtk::HBox menuBar;
		Gtk::Button newGameButton;
		Gtk::Button endGameButton;
	Gtk::Grid table;
		std::vector<std::vector<Gtk::Image*>> tableSlots;
	Gtk::HBox scoreboard;
		std::vector<Gtk::Button*> rageButtons;
	Gtk::HBox hand;
		std::vector<Gtk::Image*> handCards;
	Gtk::Image card;

};

#endif
