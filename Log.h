#ifndef LOG_H
#define LOG_H

#include <string>
#include <gtkmm.h>

class StraightsView;

class Log : public Gtk::HBox {

  // Spec fields
  // parent - window dashboard will be a part of
  // log - message to user

  StraightsView* parent_;
  Gtk::Label log_label_;
public:
  // modifies: parent, log
  // ensures: parent initialized to point as parent in args
  // ensures: log  initialized to be blank
  Log(StraightsView* parent);

  // modifies: log
  // ensures: log set to display message specified in args message
  void set(std::string message);
};

#endif
