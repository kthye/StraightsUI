#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include <gtkmm/grid.h>
#include <vector>
#include <memory>
#include "Observer.h"
#include "DeckGUI.h"
#include "SortedCardList.h"
#include "MenuBar.h"
#include "NewGameDialog.h"
#include "Dashboard.h"
#include "Table.h"
#include "Hand.h"
#include "Log.h"
#include "StraightsModel.h"

class StraightsController;


class StraightsView : public Gtk::Window, public Observer {
	// Spec fields
	// menu bar - containing options to start or end the game
	// table - the play area of the game with the cards already played
	// dashboard - the current state of players with options
	// hand - the active players hand
	//
private:
	// StraightsView needs an instance of the controller for its buttons to invoke
	StraightsController* controller_;

	// StraightsView also needs an instance of the concrete subject it is observing
	StraightsModel *model_;

	// StraightsView needs to instantiate the deck images
	DeckGUI deck_;

	// Widgets
	Gtk::VBox panels_;
	MenuBar menu_bar_;
	NewGameDialog new_game_dialog_;
	Table table_;
	Dashboard dashboard_;
	Hand hand_;
	Log log_;

	// Initializes widgets for new round
	void setNewRound();

	// Sets table rows
	void setTableRow(const SortedCardList &playArea, Suit suit);

public:

	void openNewGameDialog(unsigned int seed = 0);

	void startNewGame(std::vector<StraightsModel::PlayerType> types, unsigned int seed);

	void showHint();

	void rageQuit();

	void playCard(unsigned int cardIndex);

  StraightsView(StraightsController*, StraightsModel*);
  virtual ~StraightsView();
  virtual void update();	// Observer Pattern: concrete update() method
};

#endif
