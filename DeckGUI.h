/*
 * Adapted from MVC example by Caroline Kierstead
 */

#ifndef DECK_GUI_H
#define DECK_GUI_H
#include <gdkmm/pixbuf.h>
#include <vector>

class Card;

class DeckGUI {
    std::vector<Glib::RefPtr<Gdk::Pixbuf >> deck;

public:
	DeckGUI();
	Glib::RefPtr<Gdk::Pixbuf> cardImage(const Card & c);
    Glib::RefPtr<Gdk::Pixbuf> emptyImage();

}; // DeckGUI

#endif
