#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include "Player.h"
#include <iostream>
#include <gdkmm/rgba.h>

const int BORDER_LEN = 10;
const std::string ERR_HAS_LEGAL_PLAY = "You have a legal play. You may not discard.";

View::View(Controller *c, Model *m) : controller_(c), model_(m), deck_(), panels(false, BORDER_LEN), menuBar(true, BORDER_LEN),
newGameButton("New Game with Seed:"), seedEntry(), endGameButton("End Game"), newGameDialog("Start New Game", true),
labelBox(true, BORDER_LEN), playerBox(true, BORDER_LEN), startBox(true, BORDER_LEN), startNewGameButton("Start New Game"),
cancelButton("Cancel"), seedLabel("Seed: 0"), table(), dashboardGrid_(), dashboardHintButton_("Hint", true),
dashboardScoreLabel_("Score: 0"), dashboardRageButton_("Rage"), dashboardDiscardsLabel_("Discards: 0"),
hand(true, 0), logBox(true, 10), logLabel_("")  {

	// Sets some properties of the window.
	set_title("Straights");
	set_border_width(BORDER_LEN);

	// Add panels to the window
	add(panels);

	// Initialize custom styling
	auto css = Gtk::CssProvider::create();
	css->load_from_data(
		"#LegalPlay {\
		background-color: #FFFF00;\
		background-image: none;\
		box-shadow: none;}");
	this->get_style_context()->add_provider_for_screen(Gdk::Screen::get_default(), css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	// Set menu bar on top, followed by the table, dashboardGrid_ and hand
	panels.add(menuBar);
	panels.add(table);
	panels.add(dashboardFrame_);
	panels.add(hand);
	panels.add(logBox);

	// Add buttons to the box (a container). Buttons initially invisible
	menuBar.add(newGameButton);
	menuBar.add(seedEntry);
	menuBar.add(endGameButton);

	// Functionality of menuBar specified
	newGameButton.signal_clicked().connect(sigc::mem_fun(*this, &View::onNewGameButtonClicked));
	endGameButton.signal_clicked().connect(sigc::mem_fun(*this, &View::onEndGameButtonClicked));

	newGameDialog.set_transient_for(*this);
	Gtk::Box* dialogBox = newGameDialog.get_content_area();
	dialogBox->set_orientation(Gtk::ORIENTATION_VERTICAL);
	dialogBox->set_border_width(10);
	// dialogBox->set_homogeneous(true);

	dialogBox->pack_start(seedBox, false, false , BORDER_LEN);
	dialogBox->pack_start(labelBox, false, false , BORDER_LEN);
	dialogBox->pack_start(playerBox, false, false , 5);
	dialogBox->pack_start(startBox, false, false , 5);

	seedBox.add(seedLabel);

	for (unsigned int i = 1; i <= Model::PLAYER_COUNT; ++i) {
		playerLabels.push_back(std::unique_ptr<Gtk::Label>(new Gtk::Label("Player " + std::to_string(i))));
		labelBox.add(*playerLabels.at(i - 1));

		playerToggleButtons.push_back(std::unique_ptr<Gtk::Button>(new Gtk::Button("Computer")));
		playerToggleButtons.at(i - 1)->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &View::onTogglePlayerClicked), i));
		playerBox.add(*playerToggleButtons.at(i - 1));
	}

	cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &View::onCancelButtonClicked));
	startNewGameButton.signal_clicked().connect(sigc::mem_fun(*this, &View::onStartNewGameButtonClicked));
	startBox.add(cancelButton);
	startBox.add(startNewGameButton);

	// Define table spacing
	table.set_row_spacing(BORDER_LEN);
	table.set_column_homogeneous(true);

	// Initialize placeholders to table
	for (int y = 0; y < 4; y++) {
		std::vector<std::unique_ptr<Gtk::Image>> rows;
		for (int x = 0; x < 13; x++) {
			rows.push_back(std::unique_ptr<Gtk::Image>(new Gtk::Image(deck_.emptyImage())));
			table.attach(*rows.at(x), x, y, rows.at(x)->get_width(), rows.at(x)->get_height());
		}
		tableSlots.push_back(std::move(rows));
	}

	dashboardFrame_.add(dashboardGrid_);
	dashboardGrid_.set_border_width(5);
	dashboardGrid_.set_row_homogeneous(true);
	dashboardGrid_.set_column_homogeneous(true);

	dashboardHintButton_.set_halign(Gtk::ALIGN_CENTER);
	dashboardHintButton_.signal_clicked().connect(sigc::mem_fun(*this, &View::onHintButtonClicked));
	dashboardRageButton_.set_halign(Gtk::ALIGN_CENTER);
	dashboardRageButton_.signal_clicked().connect(sigc::mem_fun(*this, &View::onRageButtonClicked));

	dashboardGrid_.attach(dashboardHintButton_, 0, 0, dashboardHintButton_.get_width(), dashboardHintButton_.get_height());
	dashboardGrid_.attach(dashboardScoreLabel_, 0, 1, dashboardScoreLabel_.get_width(), dashboardScoreLabel_.get_height());
	dashboardGrid_.attach(dashboardRageButton_, 1, 0, dashboardRageButton_.get_width(), dashboardRageButton_.get_height());
	dashboardGrid_.attach(dashboardDiscardsLabel_, 1, 1, dashboardDiscardsLabel_.get_width(), dashboardDiscardsLabel_.get_height());


	// Initialize placeholders to hand
	for (int i = 0; i < 13; i++) {
		handButtons.push_back(std::unique_ptr<Gtk::Button>(new Gtk::Button()));
		handImages.push_back(std::unique_ptr<Gtk::Image>(new Gtk::Image(deck_.emptyImage())));

		handButtons.at(i)->set_name("");
		handButtons.at(i)->set_image(*handImages.at(i));
  	handButtons.at(i)->signal_clicked().connect(sigc::bind<unsigned int>(sigc::mem_fun(*this, &View::onCardClick), i));

		hand.add(*handButtons.at(i));
	}

	// Initialize an empty log box
	logBox.set_halign(Gtk::ALIGN_END);
	logBox.add(logLabel_);

	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

	// Start new game
	onNewGameButtonClicked();
}

View::~View() {}

void View::onNewGameButtonClicked() {
	if (seedEntry.get_text() == "") {
		seedLabel.set_text("Seed: 0");
	} else {
		seedLabel.set_text("Seed: " + seedEntry.get_text());
	}

	newGameDialog.show_all();
	newGameDialog.set_keep_above(true);
	newGameDialog.present();
}

void View::onEndGameButtonClicked() {
	close();
}

void View::onHintButtonClicked() {
	if (model_->currLegalPlays().isEmpty()) {
		logLabel_.set_text("You have no legal plays. Choose a card to discard.");
	} else {
		int count = 0;
		for (auto it = model_->currPlayer()->hand().begin(); it != model_->currPlayer()->hand().end(); ++it) {
			if (model_->currLegalPlays().contains(*it)) {
				handButtons.at(count++)->set_name("LegalPlay");
			} else {
				handButtons.at(count++)->set_name("");
			}
		}
	}
}

void View::onRageButtonClicked() {
	controller_->ragequit();
}

void View::onTogglePlayerClicked(int playerNumber) {
	if (playerToggleButtons.at(playerNumber - 1)->get_label() == "Computer") {
		playerToggleButtons.at(playerNumber - 1)->set_label("Human");
	} else {
		playerToggleButtons.at(playerNumber - 1)->set_label("Computer");
	}
}

void View::onStartNewGameButtonClicked() {
	int seed = "" == seedEntry.get_text() ? 0 : std::stoi(seedEntry.get_text());
	std::vector<Model::PlayerType> types;
	for (auto it = playerToggleButtons.begin(); it != playerToggleButtons.end(); ++it) {
			Model::PlayerType type = Model::HUMAN;
			if ((*it)->get_label() == "Human") {
				type = Model::COMPUTER;
			}
			types.push_back(type);
	}

	setNewGame();
	newGameDialog.hide();
	controller_->newGame(types, seed);
}

void View::onCancelButtonClicked() {
	newGameDialog.hide();
}

void View::onCardClick(unsigned int cardIndex) {
	if (cardIndex < model_->currPlayer()->hand().size()) {
		controller_->play(model_->currPlayer()->hand().at(cardIndex));
	}
}

void View::update() {
	if (model_->state() == Model::GAME_ENDED) {
		std::string winnersText = "";
		std::string results = "";

		for (auto it = model_->winners().at(0).begin(); it != model_->winners().at(0).end(); ++it) {
			winnersText += "Player " + std::to_string((*it)->number()) + " wins!";
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
			dashboardFrame_.set_label("Player " + std::to_string(model_->currPlayer()->number()));
			dashboardScoreLabel_.set_label("Score: " + std::to_string(model_->currPlayer()->score()));
			dashboardDiscardsLabel_.set_label("Discards: " + std::to_string(model_->currPlayer()->discard().size()));

			// Update hands
			int count = 0;
			for (auto it = model_->currPlayer()->hand().begin(); it != model_->currPlayer()->hand().end(); ++it) {
				handButtons.at(count)->set_name("");
				handImages.at(count++)->set(deck_.cardImage(**it));
			}

			for (; count < 13; ++count) {
				handButtons.at(count)->set_name("");
				handImages.at(count++)->set(deck_.emptyImage());
			}

			// TODO: Show card last played? Clear error message for now
			std::cerr << "Player " << std::to_string(model_->currPlayer()->number()) << "'s turn."<< std::endl;
			logLabel_.set_label("Player " + std::to_string(model_->currPlayer()->number()) + "'s turn.");

		} else {
			std::cerr << "You have a legal play. You may not discard." << std::endl;
			logLabel_.set_label("You have a legal play. You may not discard.");
		}
	}
	controller_->updateGame();
}

void View::setNewGame() {
	seedEntry.set_text("");
	setNewRound();
}

void View::setNewRound() {
	for (auto it = tableSlots.begin(); it != tableSlots.end(); ++it) {
		for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
			(*it2)->set(deck_.emptyImage());
		}
	}

	for (auto it = handImages.begin(); it != handImages.end(); ++it) {
		(*it)->set(deck_.emptyImage());
	}
	for (auto it = handButtons.begin(); it != handButtons.end(); ++it) {
		(*it)->set_name("");
	}

	logLabel_.set_label("");
}

void View::setTableRow(const SortedCardList &playArea, Suit suit) {

	SortedCardList::iterator it = playArea.begin();
	SortedCardList::iterator itEnd = playArea.end();
	std::vector<std::unique_ptr<Gtk::Image>>& tableRow = tableSlots.at(static_cast<int>(suit));

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
		int column = static_cast<int>((*it)->getRank());
		tableRow.at(column)->set(deck_.cardImage(**it));
	}
}
