#include "StraightsView.h"
#include "StraightsController.h"
#include "StraightsModel.h"
#include "Player.h"
#include "MenuBar.h"
#include "NewGameDialog.h"
#include <iostream>
#include <gdkmm/rgba.h>
#include "Log.h"

const int BORDER_LEN = 10;
const int TABLE_ROWS = 4;
const int TABLE_COLUMNS = 13;
const std::string ERR_HAS_LEGAL_PLAY = "You have a legal play. You may not discard.";

StraightsView::StraightsView(StraightsController *c, StraightsModel *m) : controller_(c), model_(m), deck_(), panels_(false, BORDER_LEN), menu_bar_(this),
new_game_dialog_(this), table_(this, TABLE_ROWS, TABLE_COLUMNS), dashboard_(this),
hand_(this, TABLE_COLUMNS), log_(this)  {

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
	for (int i = 0; i < TABLE_COLUMNS; i++) {
		hand_.setCard(deck_.emptyImage(), i);
	}

	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

	// Start new game
	openNewGameDialog();
}

StraightsView::~StraightsView() {}

void StraightsView::openNewGameDialog(unsigned int seed) {
	new_game_dialog_.setSeed(seed);
	new_game_dialog_.show_all();
	new_game_dialog_.set_keep_above(true);
	new_game_dialog_.present();
}

void StraightsView::showHint() {
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

void StraightsView::rageQuit() {
	controller_->ragequit();
}

void StraightsView::playCard(unsigned int cardIndex) {
	if (cardIndex < model_->currPlayer()->hand().size()) {
		controller_->play(model_->currPlayer()->hand().at(cardIndex));
	}
}

void StraightsView::update() {
	if (model_->state() == StraightsModel::GAME_ENDED) {
		dashboard_.disable();
        hand_.disable();

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
	} else if (model_->state() == StraightsModel::ROUND_ENDED) {

		// Display round over dialog
		Gtk::MessageDialog roundOverDialog("Round Over", true, Gtk::MESSAGE_QUESTION,
          Gtk::BUTTONS_OK);
		roundOverDialog.set_transient_for(*this);
		roundOverDialog.set_secondary_text(
			"Player 1 \t Score: " + std::to_string(model_->players().at(0)->score()) + "\n" +
			"Player 2 \t Score: " + std::to_string(model_->players().at(1)->score()) + "\n" +
			"Player 3 \t Score: " + std::to_string(model_->players().at(2)->score()) + "\n" +
			"Player 4 \t Score: " + std::to_string(model_->players().at(3)->score()) + "\n");

			// Update dashboard
			for (unsigned int i = 0; i < model_->PLAYER_COUNT; ++i) {
				dashboard_.setScore(i + 1, "Score: " + std::to_string(model_->players().at(i)->score()));
				dashboard_.setDiscards(i + 1, "Discards: " + std::to_string(model_->players().at(i)->discard().size()));
			}

		roundOverDialog.run();
		roundOverDialog.hide();
		roundOverDialog.close();

		setNewRound();
		controller_->newRound();
	} else {
		if (model_->error() == StraightsModel::NONE) {
			// Update table
			for (int s = CLUB; s != SUIT_COUNT; ++s) {
				setTableRow(model_->playArea(), static_cast<Suit>(s));
			}

			// Update dashboard
			for (unsigned int i = 0; i < model_->PLAYER_COUNT; ++i) {
				dashboard_.setDiscards(i + 1, "Discards: " + std::to_string(model_->players().at(i)->discard().size()));
			}

			// Update hands
			int count = 0;
			for (auto it = model_->currPlayer()->hand().begin(); it != model_->currPlayer()->hand().end(); ++it) {
				hand_.setCard(deck_.cardImage(**it), count++);
			}
			for (; count < TABLE_COLUMNS; ++count) {
				hand_.setCard(deck_.emptyImage(), count);
			}

			// Update log
			log_.set("Player " + std::to_string(model_->currPlayer()->number()) + "'s turn.");

		} else {
			std::cerr << ERR_HAS_LEGAL_PLAY << std::endl;
			log_.set(ERR_HAS_LEGAL_PLAY);
		}
	}
	controller_->updateGame();
}

void StraightsView::startNewGame(std::vector<StraightsModel::PlayerType> types, unsigned int seed) {
	menu_bar_.eraseSeedEntry();
	dashboard_.enable();
    hand_.enable();
	setNewRound();
	controller_->newGame(types, seed);
}

void StraightsView::setNewRound() {
	for (int s = CLUB; s < SUIT_COUNT; ++s) {
		for (int r = ACE; r < RANK_COUNT; ++r) {
			table_.setCell(deck_.emptyImage(), r, s);
		}
	}

	for (int i = 0; i < TABLE_COLUMNS; ++i) {
		hand_.setCard(deck_.emptyImage(), i);
	}

	log_.set("");
}

void StraightsView::setTableRow(const SortedCardList &playArea, Suit suit) {

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
