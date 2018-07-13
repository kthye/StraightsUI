#include "Dashboard.h"
#include "view.h"

const int BORDER_LEN = 10;
const int PLAYER_COUNT = 4;

Dashboard::Dashboard(View* parent) : Gtk::HBox(true, BORDER_LEN), parent_{parent},
hint_button_("Hint", 10), rage_button_("Rage", 10) {

  hint_button_.set_valign(Gtk::ALIGN_CENTER);
  hint_button_.set_border_width(BORDER_LEN);
  hint_button_.signal_clicked().connect(sigc::mem_fun(*this, &Dashboard::onHintButtonClicked));
  rage_button_.set_valign(Gtk::ALIGN_CENTER);
  rage_button_.set_border_width(BORDER_LEN);
  rage_button_.signal_clicked().connect(sigc::mem_fun(*this, &Dashboard::onRageButtonClicked));

  for (int i = 0; i < PLAYER_COUNT; ++i) {
    frames_.push_back(std::unique_ptr<Gtk::Frame>(new Gtk::Frame("Player " + std::to_string(i + 1))));
    frame_boxes_.push_back(std::unique_ptr<Gtk::VBox>(new Gtk::VBox(true, BORDER_LEN)));
    score_labels_.push_back(std::unique_ptr<Gtk::Label>(new Gtk::Label("Score: 0")));
    discards_labels_.push_back(std::unique_ptr<Gtk::Label>(new Gtk::Label("Discards: 0")));

    frame_boxes_.at(i)->add(*score_labels_.at(i));
    frame_boxes_.at(i)->add(*discards_labels_.at(i));
    frames_.at(i)->add(*frame_boxes_.at(i));
  }
  frames_.push_back(std::unique_ptr<Gtk::Frame>(new Gtk::Frame("Menu")));
  frame_boxes_.push_back(std::unique_ptr<Gtk::VBox>(new Gtk::VBox(true, BORDER_LEN)));
  frame_boxes_.at(PLAYER_COUNT)->add(hint_button_);
  frame_boxes_.at(PLAYER_COUNT)->add(rage_button_);
  frames_.at(PLAYER_COUNT)->add(*frame_boxes_.at(PLAYER_COUNT));

  column1.add(*frames_.at(0));
  column1.add(*frames_.at(1));
  column2.add(*frames_.at(4));
  column3.add(*frames_.at(2));
  column3.add(*frames_.at(3));

  add(column1);
  add(column2);
  add(column3);
}

void Dashboard::onHintButtonClicked() {
  parent_->showHint();
}

void Dashboard::onRageButtonClicked() {
  parent_->rageQuit();
}

void Dashboard::setScore(int playerNumber, std::string score) {
    score_labels_.at(playerNumber - 1)->set_text(score);
}

void Dashboard::setDiscards(int playerNumber, std::string discards) {
    discards_labels_.at(playerNumber - 1)->set_text(discards);
}

void Dashboard::disable() {
  hint_button_.set_sensitive(false);
  rage_button_.set_sensitive(false);
}

void Dashboard::enable() {
  hint_button_.set_sensitive(true);
  rage_button_.set_sensitive(true);
}
