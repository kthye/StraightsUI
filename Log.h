#ifndef LOG_H
#define LOG_H

#include <string>
#include <gtkmm.h>

class StraightsView;

class Log : public Gtk::HBox {
  StraightsView* parent_;
  Gtk::Label log_label_;
public:
  Log(StraightsView* parent);
  void set(std::string message);
};

#endif
