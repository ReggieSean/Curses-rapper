//
// Created by yuxuanhuang on 2019-03-05.
//
#include"CellReference.h"
#include"Window.h"
Curses::CellReference::CellReference(Curses::Window &win_arg, const int row_arg, const int col_arg):win(win_arg),row(row_arg),col(col_arg) {};

Curses::CellReference& Curses::CellReference::operator=(const char letter) {

  //return *this;
}