/*
 * Adapted from MVC example by Caroline Kierstead
 */

#include <algorithm>
#include <iterator>
#include "DeckGUI.h"
#include "Card.h"

// Sets up an array of the Portable Network Graphics (PNG) file names that contain the necessary card images.
// The deck will load the contents into pixel buffers for later use.
const char * image_names[] = {
    // Set up ACE of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_0.png", "img/1_0.png", "img/2_0.png", "img/3_0.png",
    // Set up TWO of {CLUB, DIAMOND, HEART, SPADE}
	"img/0_1.png", "img/1_1.png", "img/2_1.png", "img/3_1.png",
    // Set up THREE of {CLUB, DIAMOND, HEART, SPADE}
	"img/0_2.png", "img/1_2.png", "img/2_2.png", "img/3_2.png",
    // Set up FOUR of {CLUB, DIAMOND, HEART, SPADE}
	"img/0_3.png", "img/1_3.png", "img/2_3.png", "img/3_3.png",
    // Set up FIVE of {CLUB, DIAMOND, HEART, SPADE}
	"img/0_4.png", "img/1_4.png", "img/2_4.png", "img/3_4.png",
    // Set up SIX of {CLUB, DIAMOND, HEART, SPADE}
	"img/0_5.png", "img/1_5.png", "img/2_5.png", "img/3_5.png",
    // Set up SEVEN of {CLUB, DIAMOND, HEART, SPADE}
	"img/0_6.png", "img/1_6.png", "img/2_6.png", "img/3_6.png",
    // Set up EIGHT of {CLUB, DIAMOND, HEART, SPADE}
	"img/0_7.png", "img/1_7.png", "img/2_7.png", "img/3_7.png",
    // Set up NINE of {CLUB, DIAMOND, HEART, SPADE}
	"img/0_8.png", "img/1_8.png", "img/2_8.png", "img/3_8.png",
	// Set up TEN of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_9.png", "img/1_9.png", "img/2_9.png", "img/3_9.png",
	// Set up JACK of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_j.png", "img/1_j.png", "img/2_j.png", "img/3_j.png",
	// Set up QUEEN of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_q.png", "img/1_q.png", "img/2_q.png", "img/3_q.png",
	// Set up KING of {DIAMOND,CLUB,HEART,SPADE}
    "img/0_k.png", "img/1_k.png", "img/2_k.png", "img/3_k.png",
	// Set up the back of a card for a place holder/null card
	"img/nothing.png"
};

// Loads the image from the specified file name into a pixel buffer.
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const std::string & name) {
	return Gdk::Pixbuf::create_from_file( name );
} // createPixbuf

DeckGUI::DeckGUI()  {
	// Images can only be loaded once the main window has been initialized, so cannot be done as a static
	// constant array. Instead, use the STL transform algorithm to apply the method createPixbuf to every
	// element in the array of image names, starting with first and ending with the last. New elements are
	// added to the back of deck.
	transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)],
			   std::back_inserter(deck), &createPixbuf );
} // DeckGUI::DeckGUI

// Returns the image for the specified card.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::cardImage(const Card & c) {
    size_t idx = static_cast<size_t>(c.getRank()) * 4 + static_cast<size_t>(c.getSuit());
    return deck.at(idx);
} // DeckGUI::cardImage

// Returns the image to use for the placeholder.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::emptyImage() {
	return deck.back();
} // DeckGUI::emptyImage
