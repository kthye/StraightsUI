#ifndef LOG_H
#define LOG_H

#include <string>
#include <gtkmm.h>

class View;

class Log : public Gtk::HBox {
  View* parent_;
  Gtk::Label log_label_;
public:
  Log(View* parent);
  void set(std::string message);
};

#endif
