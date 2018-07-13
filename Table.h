#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <gtkmm.h>
#include <vector>
#include <memory>
#include "Card.h"

class View;

class Table : public Gtk::Grid {

  View* parent_;

  std::vector<std::vector<std::unique_ptr<Gtk::Image>>> table_slots_;
  int rows_;
  int columns_;
public:

  Table(View* parent, int rows, int columns);
  void setCell(Glib::RefPtr<Gdk::Pixbuf> buffer, int x, int y);
};

#endif
