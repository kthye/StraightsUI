#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <gtkmm.h>
#include <vector>

class StraightsView;

class Dashboard : public Gtk::HBox {
  StraightsView* parent_;

  Gtk::VBox column1;
  Gtk::VBox column2;
  Gtk::VBox column3;

  Gtk::Button hint_button_;
  Gtk::Button rage_button_;
  std::vector<std::unique_ptr<Gtk::Frame>> frames_;
  std::vector<std::unique_ptr<Gtk::VBox>> frame_boxes_;
  std::vector<std::unique_ptr<Gtk::Label>> score_labels_;
  std::vector<std::unique_ptr<Gtk::Label>> discards_labels_;

  // Invoked when the hint button is pressed
  void onHintButtonClicked();

  // Invoked when the rage button is pressed
  void onRageButtonClicked();

public:
  Dashboard(StraightsView* parent);

  void setScore(int playerNumber, std::string score);
  void setDiscards(int playerNumber, std::string discards);
  void disable();
  void enable();
};

#endif
