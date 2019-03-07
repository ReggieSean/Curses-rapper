//
// Created by mfbut on 2/22/2019.
//

#include "RowReference.h"
Curses::RowReference::RowReference(Curses::Window &win, const int row):win(win),row(row) {
}

Curses::CellReference Curses::RowReference::at(int col) {
  Curses::CellReference temp=Curses::CellReference(this->win,this->row,col);
  return temp;
}
Curses::CellReference Curses::RowReference::operator[](int col) {
  Curses::CellReference temp=this->at(col);
  return temp;
}