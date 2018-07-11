#include "observer.h"
#include "view.h"
#include "controller.h"
#include "model.h"
#include "subject.h"
#include <iostream>

View::View(Controller *c, Model *m) : model_(m), deck(), panels(false, 10), menuBar(true, 10), newGameButton("New Game with Seed:"),
seedEntry(), endGameButton("End Game"), newGameDialog("Start New Game"), labelBox(true, 10), playerBox(true, 10), startBox(true, 10),
startNewGameButton("Start New Game"), cancelButton("Cancel"), seedLabel("Seed: 0"), table(), playerDashboard(),
currentPlayerLabel("Player 1's Turn"), currentScoreLabel("Score: 0"), rageButton("f#$k!"), currentDiscardsLabel("Discards: 0"),
hand(true, 10) {

	// Sets some properties of the window.
	set_title("Straights");
	set_border_width(10);

	// Add panels to the window
	add(panels);

	// Set menu bar on top, followed by the table, playerDashboard and hand
	panels.add(menuBar);
	panels.add(table);
	panels.add(playerDashboard);
	panels.add(hand);

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

	dialogBox->pack_start(seedBox, false, false , 10);
	dialogBox->pack_start(labelBox, false, false , 10);
	dialogBox->pack_start(playerBox, false, false , 5);
	dialogBox->pack_start(startBox, false, false , 5);

	seedBox.add(seedLabel);

	for (int i = 1; i <= 4; i++) {
		Gtk::Label* playerLabel = new Gtk::Label("Player " + std::to_string(i));
		labelBox.add(*playerLabel);
		playerLabels.push_back(playerLabel);

		Gtk::Button* playerButton = new Gtk::Button("Computer");
		playerButton->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &View::onTogglePlayerClicked), i));
		playerBox.add(*playerButton);
		playerToggleButtons.push_back(playerButton);
	}

	cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &View::onCancelButtonClicked));
	startNewGameButton.signal_clicked().connect(sigc::mem_fun(*this, &View::onStartNewGameButtonClicked));
	startBox.add(cancelButton);
	startBox.add(startNewGameButton);

	// Define table spacing
	table.set_row_spacing(10);
	table.set_column_spacing(10);

	// Initialize placeholders to table
	for (int y = 0; y < 4; y++) {
		std::vector<Gtk::Image*> rows;
		for (int x = 0; x < 13; x++) {
			Gtk::Image* temp = new Gtk::Image(deck.emptyImage());
			rows.push_back(temp);
			table.attach(*temp, x, y, temp->get_width(), temp->get_height());
		}
		tableSlots.push_back(rows);
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
		handImages.push_back(new Gtk::Image(deck.emptyImage()));
		Gtk::EventBox* eventBox = new Gtk::EventBox();
		eventBox->add(*handImages.at(i));
		eventBox->set_events(Gdk::BUTTON_PRESS_MASK);
  	eventBox->signal_button_press_event().connect(sigc::mem_fun(*this, &View::onCardClick));
		handBoxes.push_back(eventBox);
		hand.add(*handBoxes.at(i));
	}

	update();

	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

View::~View() {}

void View::onNewGameButtonClicked() {
	if (seedEntry.get_text() == "") {
		seedLabel.set_text("Seed: 0");
	} else {
		seedLabel.set_text("Seed: " + seedEntry.get_text());
	}
	// TODO: actually set seed

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
	// TODO: Initalize new game
	newGameDialog.hide();
}

void View::onCancelButtonClicked() {
	newGameDialog.hide();
}

bool View::onCardClick(GdkEventButton* eventButton) {
	std::cout << "Card clicked!" << std::endl;
	return true;
}

void View::update() {
	setTableRow(model_->getPlayArea(), CLUB);
	setTableRow(model_->getPlayArea(), DIAMOND);
	setTableRow(model_->getPlayArea(), HEART);
	setTableRow(model_->getPlayArea(), SPADE);

	int count = 0;
	for (auto it = model_->getCurrPlayer()->hand().begin(); it != model_->getCurrPlayer()->hand().end(); ++it) {
		handImages.at(count++)->set(deck.cardImage(**it));
	}
}

void View::setTableRow(const SortedCardList &playArea, Suit suit) {
	switch (suit) {
	case CLUB:
		for (auto it = playArea.clubs_begin(); it != playArea.clubs_end(); ++it) {
			int x = static_cast<int>((*it)->getRank());
			int y = 0;
			std::vector<Gtk::Image*>& tableRow = tableSlots.at(y);
			tableRow.at(x)->set(deck.cardImage(**it));
		}
		break;
	case DIAMOND:
		for (auto it = playArea.diamonds_begin(); it != playArea.diamonds_end(); ++it) {
			int x = static_cast<int>((*it)->getRank());
			int y = 1;
			std::vector<Gtk::Image*>& tableRow = tableSlots.at(y);
			tableRow.at(x)->set(deck.cardImage(**it));
		}
		break;
	case HEART:
		for (auto it = playArea.hearts_begin(); it != playArea.hearts_end(); ++it) {
			int x = static_cast<int>((*it)->getRank());
			int y = 2;
			std::vector<Gtk::Image*>& tableRow = tableSlots.at(y);
			tableRow.at(x)->set(deck.cardImage(**it));
		}
		break;
	case SPADE:
		for (auto it = playArea.spades_begin(); it != playArea.spades_end(); ++it) {
			int x = static_cast<int>((*it)->getRank());
			int y = 3;
			std::vector<Gtk::Image*>& tableRow = tableSlots.at(y);
			tableRow.at(x)->set(deck.cardImage(**it));
		}
		break;
	default:
		break;
	}
}
