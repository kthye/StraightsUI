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
#include "DeckGUI.h"
#include "observer.h"

class Controller;
class Model;


class View : public Gtk::Window, public Observer {
public:
    View( Controller*, Model* );
	virtual ~View();
	virtual void update();	// Observer Pattern: concrete update() method

private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Model *model_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;

	// Card Images
	DeckGUI deck;

	// Member widgets:
	Gtk::VBox panels;    

	Gtk::HBox menuBar;   
		Gtk::Button newGameButton;
		Gtk::Button endGameButton;
	Gtk::Grid table;
		vector<vector<Gtk::Image*>> tableSlots;
	Gtk::HBox scoreboard;
		std::vector<Gtk::Button*> rageButtons;
	Gtk::HBox hand;
		vector<Gtk::Image*>	handCards;
	Gtk::Image card;

	// Signal handlers:
	void nextButtonClicked();
	void resetButtonClicked();

}; 

#endif
