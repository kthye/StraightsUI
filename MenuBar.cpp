#include <string>
#include "MenuBar.h"
#include "StraightsView.h"

const int BORDER_LEN = 10;

MenuBar::MenuBar(View* parent) : Gtk::HBox(true, BORDER_LEN), parent_{parent}, new_game_button_("New Game with Seed:"),
seed_entry_(), end_game_button_("End Game") {

	add(new_game_button_);
	add(seed_entry_);
	add(end_game_button_);

	new_game_button_.signal_clicked().connect(sigc::mem_fun(*this, &MenuBar::onNewGameButtonClicked));
	end_game_button_.signal_clicked().connect(sigc::mem_fun(*this, &MenuBar::onEndGameButtonClicked));
}

void MenuBar::onNewGameButtonClicked() {
	if (seed_entry_.get_text() == "") {
		parent_->openNewGameDialog(0);
	} else {
		parent_->openNewGameDialog(std::stoi(seed_entry_.get_text()));
	}
}

void MenuBar::onEndGameButtonClicked() {
	parent_->close();
}

void MenuBar::eraseSeedEntry() {
  seed_entry_.set_text("");
}
