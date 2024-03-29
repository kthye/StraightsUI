#include "Log.h"
#include "StraightsView.h"

Log::Log(StraightsView* parent) : Gtk::HBox(true, 10), parent_{parent}, log_label_("") {
  set_halign(Gtk::ALIGN_END);
  add(log_label_);
}

void Log::set(std::string message) {
  log_label_.set_label(message);
}
