#include "Dashboard.h"
#include "view.h"

Dashboard::Dashboard(View* parent) : Gtk::Frame(), parent_{parent}, grid_(),
hint_button_("Hint", true),
score_label_("Score: 0"), rage_button_("Rage"), discards_label_("Discards: 0") {

  add(grid_);
  grid_.set_border_width(5);
  grid_.set_row_homogeneous(true);
  grid_.set_column_homogeneous(true);

  hint_button_.set_halign(Gtk::ALIGN_CENTER);
  hint_button_.signal_clicked().connect(sigc::mem_fun(*this, &Dashboard::onHintButtonClicked));
  rage_button_.set_halign(Gtk::ALIGN_CENTER);
  rage_button_.signal_clicked().connect(sigc::mem_fun(*this, &Dashboard::onRageButtonClicked));

  grid_.attach(hint_button_, 0, 0, hint_button_.get_width(), hint_button_.get_height());
  grid_.attach(score_label_, 0, 1, score_label_.get_width(), score_label_.get_height());
  grid_.attach(rage_button_, 1, 0, rage_button_.get_width(), rage_button_.get_height());
  grid_.attach(discards_label_, 1, 1, discards_label_.get_width(), discards_label_.get_height());
}

void Dashboard::onHintButtonClicked() {
  parent_->showHint();
}

void Dashboard::onRageButtonClicked() {
  parent_->rageQuit();
}

void Dashboard::setScore(std::string score) {
  score_label_.set_text(score);
}

void Dashboard::setDiscards(std::string discards) {
  discards_label_.set_text(discards);
}
