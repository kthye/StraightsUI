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

class Controller;
class Model;


class View : public Gtk::Window, public Observer {
private:
	// View needs an instance of the controller for its buttons to invoke
	Controller* controller_;

	// View also needs an instance of the concrete subject it is observing
	Model *model_;

	// ADT containing all the Pixel Buffers of cards
	DeckGUI deck_;

	// Class for all the widgets on this window
	Gtk::VBox panels;
	Gtk::HBox menuBar;
		Gtk::Button newGameButton;
		Gtk::Entry seedEntry;
		Gtk::Button endGameButton;
		Gtk::Dialog newGameDialog;
			Gtk::HBox seedBox;
			Gtk::HBox labelBox;
			Gtk::HBox playerBox;
			Gtk::HBox startBox;
			Gtk::Button startNewGameButton;
			Gtk::Button cancelButton;
			Gtk::Label seedLabel;
			std::vector<std::unique_ptr<Gtk::Label>> playerLabels;
			std::vector<std::unique_ptr<Gtk::Button>> playerToggleButtons;
	Gtk::Grid table;
		std::vector<std::vector<std::unique_ptr<Gtk::Image>>> tableSlots;
	Gtk::Frame dashboardFrame_;
	Gtk::Grid dashboardGrid_;
		Gtk::Button dashboardHintButton_;
		Gtk::Label dashboardScoreLabel_;
		Gtk::Button dashboardRageButton_;
		Gtk::Label dashboardDiscardsLabel_;
	Gtk::HBox hand;
		std::vector<std::unique_ptr<Gtk::Image>> handImages;
		std::vector<std::unique_ptr<Gtk::Button>> handButtons;
	Gtk::HBox logBox;
		Gtk::Label logLabel_;

	// Invoked when new game button is pressed
	void onNewGameButtonClicked();

	// Invoked when end game button is pressed
	void onEndGameButtonClicked();

	// Invoked when any cards in the hand are clicked
	void onCardClick(unsigned int cardIndex);

	// Invoked when the hint button is pressed
	void onHintButtonClicked();

	// Invoked when the rage button is pressed
	void onRageButtonClicked();

	// Invoked from new game dialog when a player is toggled
	void onTogglePlayerClicked(int playerNumber);

	// Invoked from new game dialog when start new game button is pressed
	void onStartNewGameButtonClicked();

	// Invoked from new game dialog when cancel button is clicked
	void onCancelButtonClicked();

	// Initializes widgets for new game
	void setNewGame();

	// Initializes widgets for new round
	void setNewRound();

	// Sets
	void setTableRow(const SortedCardList &playArea, Suit suit);

public:
  View(Controller*, Model*);
  virtual ~View();
  virtual void update();	// Observer Pattern: concrete update() method
};

#endif
