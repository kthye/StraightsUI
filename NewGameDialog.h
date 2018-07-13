#ifndef NEW_GAME_DIALOG_H
#define NEW_GAME_DIALOG_H

#include <gtkmm.h>
#include "NewGameDialog.h"

class View;

class NewGameDialog : public Gtk::Dialog {
  View* parent_;
  Gtk::HBox seed_box_;
  Gtk::HBox label_box_;
  Gtk::HBox player_box_;
  Gtk::HBox button_box_;

  Gtk::Label seed_label_;
  std::vector<std::unique_ptr<Gtk::Label>> player_labels_;
  std::vector<std::unique_ptr<Gtk::Button>> toggle_player_buttons;
  Gtk::Button cancel_button_;
  Gtk::Button new_game_button_;

  unsigned int seed_;

  // Invoked from new game dialog when a player is toggled
  void onTogglePlayerClicked(int playerNumber);

  // Invoked from new game dialog when start new game button is pressed
  void onNewGameButtonClicked();

  // Invoked from new game dialog when cancel button is clicked
  void onCancelButtonClicked();
public:
  // Dialog requires parent
  NewGameDialog(View* parent);

  void setSeed(unsigned int seed);
};

#endif
