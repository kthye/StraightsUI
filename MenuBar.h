#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>

class StraightsView;

class MenuBar : public Gtk::HBox {

  // Spec fields
  // parent - window menu will be a part of
  // new_game_button - button to open a new game dialog
  // seed_entry - textbox to fill in seed
  // end_game_button - button to terminate game

  // Parent view
  StraightsView* parent_;

  // Widgets of menu bar
	Gtk::Button new_game_button_;
	Gtk::Entry seed_entry_;
	Gtk::Button end_game_button_;

  // Invoked when new game button is pressed
  void onNewGameButtonClicked();

  // Invoked when end game button is pressed
  void onEndGameButtonClicked();

public:
  // modifies: parent, new_game_button, seed_entry, end_game_button
  // ensures: parent initialized to point as parent in args
  // ensures: new_game_button and end_game_button initalized on the left and right ends of menu bar
  // ensures: seed_entry initalized to be blank
  MenuBar(StraightsView* parent);

  // modifies: seed_entry
  // ensures: seed entry is cleared
  void eraseSeedEntry();
};

#endif
