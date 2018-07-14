#include "StraightsView.h"
#include "NewGameDialog.h"
#include "StraightsModel.h"

const int BORDER_LEN = 10;
const int PLAYER_COUNT = 4;

NewGameDialog::NewGameDialog(StraightsView* parent) : Gtk::Dialog(), parent_{parent}, seed_box_(true, BORDER_LEN), label_box_(true, BORDER_LEN),
player_box_(true, BORDER_LEN), button_box_(true, BORDER_LEN), seed_label_("Seed: 0"), cancel_button_("Cancel"), new_game_button_("Start New Game"),
seed_(0) {

  set_transient_for(*parent);
	Gtk::Box* dialog_ = get_content_area();
	dialog_->set_orientation(Gtk::ORIENTATION_VERTICAL);
	dialog_->set_border_width(10);
	// dialog_->set_homogeneous(true);

	dialog_->pack_start(seed_box_, false, false , BORDER_LEN);
	dialog_->pack_start(label_box_, false, false , BORDER_LEN);
  dialog_->pack_start(player_box_, false, false , 5);
	dialog_->pack_start(button_box_, false, false , BORDER_LEN);

	seed_box_.add(seed_label_);

	for (unsigned int i = 1; i <= PLAYER_COUNT; ++i) {
		player_labels_.push_back(std::unique_ptr<Gtk::Label>(new Gtk::Label("Player " + std::to_string(i))));
		label_box_.add(*player_labels_.at(i - 1));

		toggle_player_buttons.push_back(std::unique_ptr<Gtk::Button>(new Gtk::Button("Computer")));
		toggle_player_buttons.at(i - 1)->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &NewGameDialog::onTogglePlayerClicked), i));
		player_box_.add(*toggle_player_buttons.at(i - 1));
	}

	cancel_button_.signal_clicked().connect(sigc::mem_fun(*this, &NewGameDialog::onCancelButtonClicked));
	new_game_button_.signal_clicked().connect(sigc::mem_fun(*this, &NewGameDialog::onNewGameButtonClicked));
	button_box_.add(cancel_button_);
	button_box_.add(new_game_button_);
}

void NewGameDialog::onTogglePlayerClicked(int playerNumber) {
	if (toggle_player_buttons.at(playerNumber - 1)->get_label() == "Computer") {
		toggle_player_buttons.at(playerNumber - 1)->set_label("Human");
	} else {
		toggle_player_buttons.at(playerNumber - 1)->set_label("Computer");
	}
}

void NewGameDialog::onNewGameButtonClicked() {
	std::vector<StraightsModel::PlayerType> types;
	for (auto it = toggle_player_buttons.begin(); it != toggle_player_buttons.end(); ++it) {
			StraightsModel::PlayerType type = StraightsModel::HUMAN;
			if ((*it)->get_label() == "Human") {
				type = StraightsModel::COMPUTER;
			}
			types.push_back(type);
	}

  hide();
  parent_->startNewGame(types, seed_);
}

void NewGameDialog::onCancelButtonClicked() {
	hide();
}

void NewGameDialog::setSeed(unsigned int seed) {
  seed_ = seed;
  seed_label_.set_label("Seed: " + std::to_string(seed));
}
