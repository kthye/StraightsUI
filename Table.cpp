#include "Table.h"

const int BORDER_LEN = 10;

Table::Table(StraightsView* parent, int rows, int columns) : Gtk::Grid(), parent_{parent}, rows_{rows},
columns_{columns} {
  set_row_spacing(BORDER_LEN);
  set_column_homogeneous(true);
  for (int y = 0; y < rows_; ++y) {
    std::vector<std::unique_ptr<Gtk::Image>> row;
    for (int x = 0; x < columns_; ++x) {
      row.push_back(std::unique_ptr<Gtk::Image>(new Gtk::Image()));
      attach(*row.at(x), x, y, row.at(x)->get_width(), row.at(x)->get_height());
    }
    table_slots_.push_back(std::move(row));
  }
}

void Table::setCell(Glib::RefPtr<Gdk::Pixbuf> buffer, int x, int y) {
  table_slots_.at(y).at(x)->set(buffer);
}
