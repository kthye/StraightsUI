#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include "Player.h"
#include <iostream>

const int BORDER_LEN = 10;

View::View(Controller *c, Model *m) : controller_(c), model_(m), deck(), panels(false, BORDER_LEN), menuBar(true, BORDER_LEN),
newGameButton("New Game with Seed:"), seedEntry(), endGameButton("End Game"), newGameDialog("Start New Game", true),
labelBox(true, BORDER_LEN), playerBox(true, BORDER_LEN), startBox(true, BORDER_LEN), startNewGameButton("Start New Game"),
cancelButton("Cancel"), seedLabel("Seed: 0"), table(), playerDashboard(), currentPlayerLabel("Player 1's Turn"),
currentScoreLabel("Score: 0"), rageButton("f#$k!"), currentDiscardsLabel("Discards: 0"),
hand(true, 10), logBox(true, 10), logMessage("")  {

	// Sets some properties of the window.
	set_title("Straights");
	set_border_width(BORDER_LEN);

	// Add panels to the window
	add(panels);

	// Set menu bar on top, followed by the table, playerDashboard and hand
	panels.add(menuBar);
	panels.add(table);
	panels.add(playerDashboard);
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

	for (unsigned int i = 1; i <= model_->PLAYER_COUNT; ++i) {
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
	table.set_column_spacing(BORDER_LEN);

	// Initialize placeholders to table
	for (int y = 0; y < 4; y++) {
		std::vector<std::unique_ptr<Gtk::Image>> rows;
		for (int x = 0; x < 13; x++) {
			rows.push_back(std::unique_ptr<Gtk::Image>(new Gtk::Image(deck.emptyImage())));
			table.attach(*rows.at(x), x, y, rows.at(x)->get_width(), rows.at(x)->get_height());
		}
		tableSlots.push_back(std::move(rows));
	}

	rageButton.set_halign(Gtk::ALIGN_CENTER);
	playerDashboard.set_row_homogeneous(true);
	playerDashboard.set_column_homogeneous(true);

	playerDashboard.attach(currentPlayerLabel, 0, 0, currentPlayerLabel.get_width(), currentPlayerLabel.get_height());
	playerDashboard.attach(currentScoreLabel, 0, 1, currentScoreLabel.get_width(), currentScoreLabel.get_height());
	playerDashboard.attach(rageButton, 1, 0, rageButton.get_width(), rageButton.get_height());
	playerDashboard.attach(currentDiscardsLabel, 1, 1, currentDiscardsLabel.get_width(), currentDiscardsLabel.get_height());


	// Initialize placeholders to hand
	for (int i = 0; i < 13; i++) {
		handBoxes.push_back(std::unique_ptr<Gtk::EventBox>(new Gtk::EventBox()));
		handImages.push_back(std::unique_ptr<Gtk::Image>(new Gtk::Image(deck.emptyImage())));

		handBoxes.at(i)->add(*handImages.at(i));
		handBoxes.at(i)->set_events(Gdk::BUTTON_PRESS_MASK);
  	handBoxes.at(i)->signal_button_press_event().connect(sigc::bind<int>(sigc::mem_fun(*this, &View::onCardClick), i));
		hand.add(*handBoxes.at(i));
	}

	// Initialize an empty log box
	logBox.set_halign(Gtk::ALIGN_END);
	logBox.add(logMessage);

	// The final step is to display the buttons (they display themselves)
	show_all();

	// Update screen based on starting state
	update();

	// Register view as observer of model
	model_->subscribe(this);

}

View::~View() {}

void View::onNewGameButtonClicked() {
	if (seedEntry.get_text() == "") {
		seedLabel.set_text("Seed: 0");
	} else {
		seedLabel.set_text("Seed: " + seedEntry.get_text());
	}

	newGameDialog.show_all();
	newGameDialog.present();
}

void View::onEndGameButtonClicked() {
	close();
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
	std::vector<PlayerType> types;
	for (auto it = playerToggleButtons.begin(); it != playerToggleButtons.end(); ++it) {
			PlayerType type = HUMAN;
			if ((*it)->get_label() == "Human") {
				type = COMPUTER;
			}
			types.push_back(type);
	}

	controller_->newGame(types, seed);
	seedEntry.set_text("");
	newGameDialog.hide();
}

void View::onCancelButtonClicked() {
	newGameDialog.hide();
}

bool View::onCardClick(GdkEventButton* eventButton, unsigned int cardIndex) {
	std::cout << "Card clicked!" << std::endl;
	if (cardIndex < model_->currPlayer()->hand().size()) {
		controller_->playCard(model_->currPlayer()->hand().at(cardIndex));
	}

	return true;
}

void View::update() {
	if (!model_->gameInProgress()) {
			// TODO: open the modal but do not let it be closed
			onNewGameButtonClicked();
	} else if (!model_->roundInProgress()) {
		Gtk::MessageDialog roundOverDialog("Round Over", true, Gtk::MESSAGE_QUESTION,
          Gtk::BUTTONS_OK);
		roundOverDialog.set_secondary_text("Player 1 \t Score: " + std::to_string(model_->players().at(0)->score()) + "\n" +
			"Player 2 \t Score: " + std::to_string(model_->players().at(1)->score()) + "\n" +
			"Player 3 \t Score: " + std::to_string(model_->players().at(2)->score()) + "\n" +
			"Player 4 \t Score: " + std::to_string(model_->players().at(3)->score()) + "\n");
		int result = roundOverDialog.run();
		switch(result) {
	    case Gtk::RESPONSE_OK:

	    	// TODO: call something
	    break;
	    default:
	    std::cout << "Unexpected button clicked." << std::endl;
	    break;
  	}
	} else {
		if (model_->error().empty()) {
			// Update table
			for (int s = CLUB; s != SUIT_COUNT; ++s) {
				setTableRow(model_->playArea(), static_cast<Suit>(s));
			}

			// Update player dashboard
			currentPlayerLabel.set_label("Player " + std::to_string(model_->currPlayer()->number()) + "'s Turn");
			currentScoreLabel.set_label("Score: " + std::to_string(model_->currPlayer()->score()));
			currentDiscardsLabel.set_label("Discards: " + std::to_string(model_->currPlayer()->discard().size()));

			// Update hand
			int count = 0;
			for (auto it = model_->currPlayer()->hand().begin(); it != model_->currPlayer()->hand().end(); ++it) {
				handImages.at(count++)->set(deck.cardImage(**it));
			}
			for (; count < 13; ++count) {
				handImages.at(count++)->set(deck.emptyImage());
			}

			// TODO: Show card last played? Clear error message for now
			logMessage.set_label("");

		} else {
			// TODO: Handle error
			std::cout << model_->error() << std::endl;
			// TODO: error messages should be determined by the view
			logMessage.set_label(model_->error());
		}
	}
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
		tableRow.at(column)->set(deck.cardImage(**it));
	}
}
