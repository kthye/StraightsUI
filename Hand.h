#ifndef HAND_H
#define HAND_H

#include <string>
#include <gtkmm.h>

class StraightsView;

class Hand : public Gtk::HBox {

  // Spec fields
  // parent - window dashboard will be a part of
  // hand_cards - cards in hand

  // Parent window
  StraightsView* parent_;

  // Widgets
	std::vector<std::unique_ptr<Gtk::Image>> hand_images_;
	std::vector<std::unique_ptr<Gtk::Button>> hand_buttons_;

  // hand size
  int hand_size_;

  // Invoked when any cards in the hand are clicked
  void onCardClick(unsigned int cardIndex);
public:

  // modifies: parent, hand_cards
  // ensures: parent initialized to point as parent in args
  // ensures: hand_cards initialized to have args number of cards, all being empty images
  Hand(StraightsView* parent, int handSize);

  // modifies: hand_cards
  // ensures: the card at index cardindex in args will have its image set to buffer from args
  // ensures: if glow is set to true then card at that index will also glow yellow
  // ensures: else will be set to not glowing
  void setCard(Glib::RefPtr<Gdk::Pixbuf> buffer, int cardIndex, bool glow = false);

  // modifies: hand_cards
  // ensures: if glow is set to true then card at that index will also glow yellow
  // ensures: else will be set to not glowing
  void setGlow(int cardIndex, bool glow);

  // modifies: hand_cards
  // ensures: hand_cards can not be interacted with
  void disable();

  // modifies: hand_cards
  // ensures: hand_cards can be interacted with
  void enable();
};

#endif
