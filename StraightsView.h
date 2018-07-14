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
	// model - model of game needed to update the window
	// controller - controller needed to update game
	// menu_bar - containing options to start or end the game
	// new_game_dialog - dialog that can appear that can start a new game
	// table - the play area of the game with the cards already played
	// dashboard - the current state of players with options
	// hand - the active players hand
	// log - responses to user on current state of game and their interactions

private:
	// StraightsView needs an instance of the controller for its buttons to invoke
	StraightsController* controller_;

	// StraightsView also needs an instance of the concrete subject it is observing
	StraightsModel *model_;

	// StraightsView needs to instantiate the deck images
	DeckGUI deck_;

	// Splits window to horizontal rows
	Gtk::VBox panels_;

	// Menu bar on top
	MenuBar menu_bar_;

	// Dialog that appears when starting a new game
	NewGameDialog new_game_dialog_;

	// Table showing play area
	Table table_;

	// Player dashboard
	Dashboard dashboard_;

	// Active players hand
	Hand hand_;

	// Log messages
	Log log_;

	// Initializes widgets for new round
	void setNewRound();

	// Sets table rows
	void setTableRow(const SortedCardList &playArea, Suit suit);

public:
	// modifies: model, controller, menu_bar, new_game_dialog, table, dashboard, hand, log
	// ensures: initializes our access to model
	// ensures: initializes our access to controller, controller opens menu_bar's dialog
	// ensures: table initalized to empty 13 by 4 table
	// ensures : new_game_dialog initialized and is displayed
	// ensures: dashboard, hand and log initialized to be empty
  StraightsView(StraightsController*, StraightsModel*);

	// modifies: model, controller, table, dashboard, hand, log
	// ensures: gets state of model
	// ensures: updates controller
	// ensures: if round is over or game is over, prompt user and update dashboard
	// ensures: otherwise, table, dashboard, hand and log is updated based on model state
	virtual void update();

	// modifies: menu_bar, new_game_dialog
	// ensures: if changeSeed true then new_game_dialog is open with a seed initialized by the seed text box in menu_bar
	// else initialized to current seed value
	void openNewGameDialog(bool changeSeed = false, unsigned int seed = 0);

	// requires: new_game_dialog is active
	// modifies: controller, menu_bar, dashboard, hand, log
	// ensures: controller is called to start a new game
	// ensures: and seed entry in menu_bar is erased
	// ensures: dashboard is enabled and all its values are reset
	// ensures: hand is enabled
	// ensures: log is cleared to display no messages
	void startNewGame(std::vector<StraightsModel::PlayerType> types, unsigned int seed);

	// modifies: model, hand, log
	// ensures: checks model for legal plays of active player
	// ensures: if legal plays exist, hand highlights cards that are legal plays yellow
	// ensures: else log prompts user to discard a card
	void showHint();

	// modifies: controller
	// ensures: calls controller to rage quit current player
	void rageQuit();

	// modifies: model, controller
	// ensures: if the card index is valid according to the model, call the controller to play the card
	// ensures: otherwise, do nothing
	void playCard(unsigned int cardIndex);
};

#endif
