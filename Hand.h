#ifndef HAND_H
#define HAND_H

#include <string>
#include <gtkmm.h>

class View;

class Hand : public Gtk::HBox {
  View* parent_;

	std::vector<std::unique_ptr<Gtk::Image>> hand_images_;
	std::vector<std::unique_ptr<Gtk::Button>> hand_buttons_;

  int hand_size_;

  // Invoked when any cards in the hand are clicked
  void onCardClick(unsigned int cardIndex);
public:
  Hand(View* parent, int handSize);
  void setCard(Glib::RefPtr<Gdk::Pixbuf> buffer, int cardIndex, bool glow = false);
  void setGlow(int cardIndex, bool glow);

};

#endif
