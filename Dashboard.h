#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <gtkmm.h>
#include <vector>

class StraightsView;

class Dashboard : public Gtk::HBox {

  // Spec fields
  // parent - window dashboard will be a part of
  // players_info - shows current score and discards for each player
  // hint_button - shows hint to player when clicked
  // rage_button - replaces active player with computer when clicked

  // parent window
  StraightsView* parent_;

  // Widgets
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
  // modifies: parent, players_info, hint_button, rage_button
  // ensures: parent initialized to point as parent in args
  // ensures: player_info initialized to have set all scores and discards to zero
  // ensures: hint_button and rage_button initialized and linked to functionality
  Dashboard(StraightsView* parent);

  // modifies: players_info
  // ensures: player with matching player number to args will have their score modified to match args score
  void setScore(int playerNumber, int score);

  // modifies: players_info
  // ensures: player with matching player number to args will have their discards modified to match args discards
  void setDiscards(int playerNumber, int discards);

  // modifies: hint_button, rage_button
  // ensures: hint_button and rage_button are disabled and do nothing when clicked
  void disable();

  // modifies: hint_button, rage_button
  // ensures: hint_button and rage_button are enabled and will function when clicked
  void enable();

  // modifies: player_info
  // ensures: all players have their score and discards set to zero
  void clear();
};

#endif
