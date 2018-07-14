#ifndef NEW_GAME_DIALOG_H
#define NEW_GAME_DIALOG_H

#include <gtkmm.h>
#include "NewGameDialog.h"

class StraightsView;

class NewGameDialog : public Gtk::Dialog {

  // Spec fields
  // parent - window dialog will be a part of
  // seed - seed a potential new game will be started with
  // player_toggle_buttons - button to toggle if a player will be a human or computer
  // cancel_button - button to close this dialog
  // new_game_button - button to start new game

  // Widgets
  StraightsView* parent_;
  Gtk::HBox seed_box_;
  Gtk::HBox label_box_;
  Gtk::HBox player_box_;
  Gtk::HBox button_box_;
  Gtk::Label seed_label_;
  std::vector<std::unique_ptr<Gtk::Label>> player_labels_;
  std::vector<std::unique_ptr<Gtk::Button>> toggle_player_buttons;
  Gtk::Button cancel_button_;
  Gtk::Button new_game_button_;

  // Seed value
  unsigned int seed_;

  // Invoked from new game dialog when a player is toggled
  void onTogglePlayerClicked(int playerNumber);

  // Invoked from new game dialog when start new game button is pressed
  void onNewGameButtonClicked();

  // Invoked from new game dialog when cancel button is clicked
  void onCancelButtonClicked();
public:
  // modifies: parent, seed, player_toggle_button, cancel_button, new_game_button
  // ensures: parent initialized to point as parent in args
  // ensures: seed initialzied to value of zero
  // player_toggle_buttons initialized to change players to computers when clicked
  // cancel_button and new_game_button initialized and linked to functionality
  NewGameDialog(StraightsView* parent);

  // modifies: seed
  // ensures: seed is set to seed value in args
  void setSeed(unsigned int seed);
};

#endif
