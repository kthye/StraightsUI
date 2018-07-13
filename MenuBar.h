#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <gtkmm.h>

class View;

class MenuBar : public Gtk::HBox {
  View* parent_;

	Gtk::Button new_game_button_;
	Gtk::Entry seed_entry_;
	Gtk::Button end_game_button_;

  // Invoked when new game button is pressed
  void onNewGameButtonClicked();

  // Invoked when end game button is pressed
  void onEndGameButtonClicked();

public:
  MenuBar(View* parent);
  void eraseSeedEntry();
};

#endif