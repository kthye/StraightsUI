#include "Hand.h"
#include "view.h"

Hand::Hand(View* parent, int handSize) : Gtk::HBox(true, 10), parent_{parent},
hand_size_{handSize} {
  // Initialize custom styling
	auto css = Gtk::CssProvider::create();
	css->load_from_data(
		"#Glow {\
		background-color: #FFFF00;\
		background-image: none;\
		box-shadow: none;}");
	this->get_style_context()->add_provider_for_screen(Gdk::Screen::get_default(), css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  for (int i = 0; i < hand_size_; ++i) {
    hand_images_.push_back(std::unique_ptr<Gtk::Image>(new Gtk::Image()));
    hand_buttons_.push_back(std::unique_ptr<Gtk::Button>(new Gtk::Button()));
    hand_buttons_.at(i)->set_name("");
    hand_buttons_.at(i)->signal_clicked().connect(sigc::bind<unsigned int>(sigc::mem_fun(*this, &Hand::onCardClick), i));
    add(*hand_buttons_.at(i));
  }
}

void Hand::setCard(Glib::RefPtr<Gdk::Pixbuf> buffer, int cardIndex, bool glow) {
  hand_images_.at(cardIndex)->set(buffer);
  setGlow(cardIndex, glow);
  hand_buttons_.at(cardIndex)->set_image(*hand_images_.at(cardIndex));

}

void Hand::setGlow(int cardIndex, bool glow) {
  if (glow) {
    hand_buttons_.at(cardIndex)->set_name("Glow");
  } else {
    hand_buttons_.at(cardIndex)->set_name("");

  }
}

void Hand::onCardClick(unsigned int cardIndex) {
  parent_->playCard(cardIndex);
}
