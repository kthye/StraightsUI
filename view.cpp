#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include "Player.h"
#include "MenuBar.h"
#include "NewGameDialog.h"
#include <iostream>
#include <gdkmm/rgba.h>
#include "Log.h"

const int BORDER_LEN = 10;
const std::string ERR_HAS_LEGAL_PLAY = "You have a legal play. You may not discard.";

View::View(Controller *c, Model *m) : controller_(c), model_(m), deck_(), panels_(false, BORDER_LEN), menu_bar_(this),
new_game_dialog_(this), table_(this, 4, 13), dashboard_(this),
hand_(this, 13), log_(this)  {

	// Sets some properties of the window.
	set_title("Straights");
	set_border_width(BORDER_LEN);

	// Add panels_ to the window
	add(panels_);

	panels_.add(menu_bar_);
	panels_.add(table_);
	panels_.add(dashboard_);
	panels_.add(hand_);
	panels_.add(log_);

	// Initialize table
	for (int s = CLUB; s < SUIT_COUNT; ++s) {
    for (int r = ACE; r < RANK_COUNT; ++r) {
      table_.setCell(deck_.emptyImage(), r, s);
    }
  }

	// Initialize placeholders to hand
	for (int i = 0; i < 13; i++) {
		hand_.setCard(deck_.emptyImage(), i);
	}

	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

	// Start new game
	openNewGameDialog();
}

View::~View() {}

void View::openNewGameDialog(unsigned int seed) {
	new_game_dialog_.setSeed(seed);
	new_game_dialog_.show_all();
	new_game_dialog_.set_keep_above(true);
	new_game_dialog_.present();
}

void View::showHint() {
	if (model_->currLegalPlays().isEmpty()) {
		log_.set(ERR_HAS_LEGAL_PLAY);
	} else {
		int count = 0;
		for (auto it = model_->currPlayer()->hand().begin(); it != model_->currPlayer()->hand().end(); ++it) {
			if (model_->currLegalPlays().contains(*it)) {
				hand_.setGlow(count++, true);
			} else {
				hand_.setGlow(count++, false);
			}
		}
	}
}

void View::rageQuit() {
	controller_->ragequit();
}

void View::playCard(unsigned int cardIndex) {
	if (cardIndex < model_->currPlayer()->hand().size()) {
		controller_->play(model_->currPlayer()->hand().at(cardIndex));
	}
}

void View::update() {
	if (model_->state() == Model::GAME_ENDED) {
		std::string winnersText = "";
		std::string results = "";

		for (auto it = model_->winners().at(0).begin(); it != model_->winners().at(0).end(); ++it) {
			winnersText += "Player " + std::to_string((*it)->number()) + " wins! ";
		}

		Gtk::MessageDialog gameOverDialog(winnersText, true, Gtk::MESSAGE_QUESTION,
          Gtk::BUTTONS_OK);
		gameOverDialog.set_transient_for(*this);

		for (auto it = model_->winners().begin(); it != model_->winners().end(); ++it) {
			for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
				results += 	"Player " + std::to_string((*it2)->number()) + " \t Score: " + std::to_string((*it2)->score()) + "\n";
			}
		}

		gameOverDialog.set_secondary_text(results);
		gameOverDialog.run();
		gameOverDialog.close();
	} else if (model_->state() == Model::ROUND_ENDED) {

		// Display round over dialog
		Gtk::MessageDialog roundOverDialog("Round Over", true, Gtk::MESSAGE_QUESTION,
          Gtk::BUTTONS_OK);
		roundOverDialog.set_transient_for(*this);
		roundOverDialog.set_secondary_text(
			"Player 1 \t Score: " + std::to_string(model_->players().at(0)->score()) + "\n" +
			"Player 2 \t Score: " + std::to_string(model_->players().at(1)->score()) + "\n" +
			"Player 3 \t Score: " + std::to_string(model_->players().at(2)->score()) + "\n" +
			"Player 4 \t Score: " + std::to_string(model_->players().at(3)->score()) + "\n");
		roundOverDialog.run();
		roundOverDialog.close();

		setNewRound();
		controller_->newRound();
	} else {
		if (model_->error() == Model::NONE) {
			// Update table
			for (int s = CLUB; s != SUIT_COUNT; ++s) {
				setTableRow(model_->playArea(), static_cast<Suit>(s));
			}

			// Update player dashboard
			dashboard_.set_label("Player " + std::to_string(model_->currPlayer()->number()));
			dashboard_.setScore("Score: " + std::to_string(model_->currPlayer()->score()));
			dashboard_.setDiscards("Discards: " + std::to_string(model_->currPlayer()->discard().size()));

			// Update hands
			int count = 0;
			for (auto it = model_->currPlayer()->hand().begin(); it != model_->currPlayer()->hand().end(); ++it) {
				hand_.setCard(deck_.cardImage(**it), count++);
			}

			for (; count < 13; ++count) {
				hand_.setCard(deck_.emptyImage(), count);
			}

			log_.set("Player " + std::to_string(model_->currPlayer()->number()) + "'s turn.");

		} else {
			std::cerr << ERR_HAS_LEGAL_PLAY << std::endl;
			log_.set(ERR_HAS_LEGAL_PLAY);
		}
	}
	controller_->updateGame();
}

void View::startNewGame(std::vector<Model::PlayerType> types, unsigned int seed) {
	menu_bar_.eraseSeedEntry();
	setNewRound();
	controller_->newGame(types, seed);
}

void View::setNewRound() {
	for (int s = CLUB; s < SUIT_COUNT; ++s) {
		for (int r = ACE; r < RANK_COUNT; ++r) {
			table_.setCell(deck_.emptyImage(), r, s);
		}
	}

	for (int i = 0; i < 13; ++i) {
		hand_.setCard(deck_.emptyImage(), i);
	}

	log_.set("");
}

void View::setTableRow(const SortedCardList &playArea, Suit suit) {

	SortedCardList::iterator it = playArea.begin();
	SortedCardList::iterator itEnd = playArea.end();
	int column = static_cast<int>(suit);

	switch (suit) {
	case CLUB:
		it = playArea.clubs_begin();
		itEnd = playArea.clubs_end();
		break;
	case DIAMOND:
		it = playArea.diamonds_begin();
		itEnd = playArea.diamonds_end();
		break;
	case HEART:
		it = playArea.hearts_begin();
		itEnd = playArea.hearts_end();
		break;
	case SPADE:
		it = playArea.spades_begin();
		itEnd = playArea.spades_end();
		break;
	default:
		break;
	}

	for (; it != itEnd; ++it) {
		int row = static_cast<int>((*it)->getRank());
		table_.setCell(deck_.cardImage(**it), row, column);
	}
}
