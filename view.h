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
	void setTableRow(const SortedCardList &playArea, Suit suit);
	void clearTable();
	void clearHand();
	// Observer Pattern: to access Model accessors without having to downcast subject
	Controller* controller_;
	Model *model_;
	DeckGUI deck;

	// Member widgets:
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
	Gtk::Grid playerDashboard;
		Gtk::Label currentPlayerLabel;
		Gtk::Label currentScoreLabel;
		Gtk::Button rageButton;
		Gtk::Label currentDiscardsLabel;
	Gtk::HBox hand;
		std::vector<std::unique_ptr<Gtk::Image>> handImages;
		std::vector<std::unique_ptr<Gtk::Button>> handButtons;
	Gtk::HBox logBox;
		Gtk::Label logMessage;
	// Gtk::MessageDialog roundOverDialog;
		// Gtk::ConfirmButton;

	void onNewGameButtonClicked();
	void onEndGameButtonClicked();
	void onCardClick(unsigned int cardIndex);
	void onRageButtonClicked();

	void onTogglePlayerClicked(int playerNumber);
	void onStartNewGameButtonClicked();
	void onCancelButtonClicked();
public:
  View(Controller*, Model*);
  virtual ~View();
  virtual void update();	// Observer Pattern: concrete update() method
};

#endif
