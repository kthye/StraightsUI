#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <gtkmm.h>
#include <vector>
#include <memory>
#include "Card.h"

class StraightsView;

class Table : public Gtk::Grid {

  // Spec fields
  // parent - window table will be a part of
  // table - table of card images

  StraightsView* parent_;

  std::vector<std::vector<std::unique_ptr<Gtk::Image>>> table_slots_;
  int rows_;
  int columns_;
public:
  // modifies: parent, table
  // ensures: parent initialized to point as parent in args
  // ensures: table initialized to empty images with rows and columns equal to rows and columns in args
  Table(StraightsView* parent, int rows, int columns);

  // requires: coordinates are valid
  // modifies: table
  // ensures: table cell at args coordinates set to image buffer
  void setCell(Glib::RefPtr<Gdk::Pixbuf> buffer, int x, int y);
};

#endif
