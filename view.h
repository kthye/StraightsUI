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
#include <memory>
#include "observer.h"
#include "DeckGUI.h"
#include "SortedCardList.h"
#include "model.h"
#include "MenuBar.h"
#include "NewGameDialog.h"
#include "Dashboard.h"
#include "Table.h"
#include "Hand.h"
#include "Log.h"

class Controller;
class Model;


class View : public Gtk::Window, public Observer {
private:
	// View needs an instance of the controller for its buttons to invoke
	Controller* controller_;

	// View also needs an instance of the concrete subject it is observing
	Model *model_;

	DeckGUI deck_;

	// Class for all the widgets on this window
	Gtk::VBox panels_;
	MenuBar menu_bar_;
	NewGameDialog new_game_dialog_;
	Table table_;
	Dashboard dashboard_;
	Hand hand_;
	Log log_;

	// Initializes widgets for new round
	void setNewRound();

	void setTableRow(const SortedCardList &playArea, Suit suit);

public:
	void openNewGameDialog(unsigned int seed = 0);

	void startNewGame(std::vector<Model::PlayerType> types, unsigned int seed);

	void showHint();

	void rageQuit();

	void playCard(unsigned int cardIndex);

  View(Controller*, Model*);
  virtual ~View();
  virtual void update();	// Observer Pattern: concrete update() method
};

#endif
