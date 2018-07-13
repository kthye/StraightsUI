#include "Log.h"
#include "view.h"

Log::Log(View* parent) : Gtk::HBox(true, 10), parent_{parent}, log_label_("") {
  set_halign(Gtk::ALIGN_END);
  add(log_label_);
}

void Log::set(std::string message) {
  log_label_.set_label(message);
}
