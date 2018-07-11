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
private:
	void setTableRow(const SortedCardList &playArea, Suit suit);
	// Observer Pattern: to access Model accessors without having to downcast subject
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
      std::vector<Gtk::Label*> playerLabels;
      std::vector<Gtk::Button*> playerToggleButtons;
	Gtk::Grid table;
		std::vector<std::vector<Gtk::Image*>> tableSlots;
	Gtk::Grid playerDashboard;
		Gtk::Label currentPlayerLabel;
		Gtk::Label currentScoreLabel;
		Gtk::Button rageButton;
		Gtk::Label currentDiscardsLabel;
	Gtk::HBox hand;
		std::vector<Gtk::Image*>	handImages;
		std::vector<Gtk::EventBox*> handBoxes;
protected:
	void onNewGameButtonClicked();
	void onEndGameButtonClicked();
	bool onCardClick(GdkEventButton* eventButton);

	void onTogglePlayerClicked(int playerNumber);
	void onStartNewGameButtonClicked();
	void onCancelButtonClicked();
public:
  View( Controller*, Model* );
  virtual ~View();
  virtual void update();	// Observer Pattern: concrete update() method
};

#endif
