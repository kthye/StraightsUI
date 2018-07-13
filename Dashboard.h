#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <gtkmm.h>

class View;

class Dashboard : public Gtk::Frame {
  View* parent_;

  Gtk::Grid grid_;
  Gtk::Button hint_button_;
  Gtk::Label score_label_;
  Gtk::Button rage_button_;
  Gtk::Label discards_label_;

  // Invoked when the hint button is pressed
  void onHintButtonClicked();

  // Invoked when the rage button is pressed
  void onRageButtonClicked();

public:
  Dashboard(View* parent);

  void setScore(std::string score);
  void setDiscards(std::string discards);
};

#endif
