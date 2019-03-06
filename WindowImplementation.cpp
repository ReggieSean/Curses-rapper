//
// Created by mfbut on 2/24/2019.
//
#include "WindowImplementation.h"

/*
 * I've already added the cut to initialize curses if it hasn't been called
 * and to create the window. You may still need to do more initialization if
 * you have other members
 */
Curses::WindowImplementation::WindowImplementation(int numRows, int numCols, int startRow, int startCol) :
    cursesWindow(nullptr, delwin) {
  if (!stdscr) {
    initscr();
  }
  cursesWindow = std::unique_ptr<WINDOW, decltype(delwin)*>(newwin(numRows, numCols, startRow, startCol), delwin);
  cursor_on=true;
}

Curses::WindowImplementation::WindowImplementation(int numRows, int numCols) : WindowImplementation(numRows,
                                                                                                    numCols,
                                                                                                    0,
                                                                                                    0) {

}

//the unique pointer will automatically delete itself
//but if you dynamically allocate any more space for this
//problem make sure to free it here.
Curses::WindowImplementation::~WindowImplementation() {

}

char Curses::WindowImplementation::getWindowChar(int row, int col) {

 char temp=char(mvwinch(cursesWindow.get(),row,col));
 wmove(cursesWindow.get(),row,col);
  return temp;
}

char Curses::WindowImplementation::getWindowChar() {
  int cursorx=getcurx(cursesWindow.get());
  int cursory=getcury(cursesWindow.get());
   char temp=char(winch(cursesWindow.get()));
   wmove(cursesWindow.get(),cursory,cursorx);
   return temp;
}

char Curses::WindowImplementation::getCharInput(int row, int col) {

 char temp=mvwgetch(cursesWindow.get(),row,col);
 wmove(cursesWindow.get(),row,col);
  return temp;

}

char Curses::WindowImplementation::getCharInput() {
  int cursorx=getcurx(cursesWindow.get());
  int cursory=getcury(cursesWindow.get());
  char temp=wgetch(cursesWindow.get());
  wmove(cursesWindow.get(),cursory,cursorx);
  return temp;

}

std::string Curses::WindowImplementation::getStringInput(int row, int col) {//stop getting character if it is  empty
  char a=mvwgetch(cursesWindow.get(),row,col);
  std::string temp;
  temp.push_back(a);

  while (a!='\n'){
    a =wgetch(cursesWindow.get());
    temp.push_back(a);
  }
  wmove(cursesWindow.get(),row,col);
  return temp;
}

std::string Curses::WindowImplementation::getStringInput() {
  int cursorx=getcurx(cursesWindow.get());
  int cursory=getcury(cursesWindow.get());
  char a =wgetch(cursesWindow.get());
  std::string temp;
  temp.push_back(a);
  while (a!='\n'){
    a =wgetch(cursesWindow.get());
    temp.push_back(a);
  }
  wmove(cursesWindow.get(),cursory,cursorx);
  return temp;
}

void Curses::WindowImplementation::addCharacter(int row, int col, char value) {
  moveCursor(row,col);
  addCharacter(value);
  if (!cursor_on){
    wmove(cursesWindow.get(),row,col);
  }
}

void Curses::WindowImplementation::addCharacter(char value) {
  int cursorx=getcurx(cursesWindow.get());
  int cursory=getcury(cursesWindow.get());
  waddch(cursesWindow.get(),value);
  if (!cursor_on){
    wmove(cursesWindow.get(),cursory,cursorx);
  }
}

void Curses::WindowImplementation::addString(int row, int col, const std::string& str) {
  moveCursor(row,col);
  int cursorx=getcurx(cursesWindow.get());
  int cursory=getcury(cursesWindow.get());
  mvwaddstr(cursesWindow.get(),cursory,cursorx,str.c_str());
  if (!cursor_on){
    wmove(cursesWindow.get(),cursory,cursorx);
  }
}

void Curses::WindowImplementation::addString(const std::string& str) {
  int cursorx=getcurx(cursesWindow.get());
  int cursory=getcury(cursesWindow.get());
  waddstr(cursesWindow.get(),str.c_str());
  if (!cursor_on){
    wmove(cursesWindow.get(),cursory,cursorx);
  }
}

int Curses::WindowImplementation::getRowStart() const {
  return getbegy(cursesWindow.get());
}

int Curses::WindowImplementation::getColStart() const {
  return getbegx(cursesWindow.get());
}

int Curses::WindowImplementation::getNumRows() const {
  return getmaxy(cursesWindow.get());
}

int Curses::WindowImplementation::getNumCols() const {
  return getmaxx(cursesWindow.get());
}

int Curses::WindowImplementation::getCurRow() const {
  return getcury(cursesWindow.get());
}

int Curses::WindowImplementation::getCurCol() const {
  return getcurx(cursesWindow.get());
}

void Curses::WindowImplementation::moveCursor(int row, int col) {
  if (row>=getmaxy(cursesWindow.get())){
    row=getmaxy(cursesWindow.get())-1;
  }
  if (col>=getmaxx(cursesWindow.get())){
    col=getmaxx(cursesWindow.get())-1;
  }
  if (row<0){
    row=0;
  }
  if (col<0){
    col=0;
  }
  wmove(cursesWindow.get(),row, col);
}

void Curses::WindowImplementation::moveCursorLeft(int amount) {
  int cursorx=getcurx(cursesWindow.get());
  int cursory=getcury(cursesWindow.get());
  if (cursorx-amount<0){
    cursorx=0;
  }else{
    cursorx=cursorx-amount;
  }
  wmove(cursesWindow.get(), cursory, cursorx);
}

void Curses::WindowImplementation::moveCursorRight(int amount) {
  int cursorx=getcurx(cursesWindow.get());
  int cursory=getcury(cursesWindow.get());

  if (cursorx+amount > getmaxx(cursesWindow.get())-1) {
    cursorx = getmaxx(cursesWindow.get()) - 1;
  }else {
    cursorx=cursorx+amount;
  }
  wmove(cursesWindow.get(), cursory, cursorx);
}
void Curses::WindowImplementation::moveCursorUp(int amount) {
  int cursorx=getcurx(cursesWindow.get());
  int cursory=getcury(cursesWindow.get());
  if (cursory-amount<0){
    cursory=0;
  }else{
    cursory=cursory-amount;
  }
  wmove(cursesWindow.get(),cursory,cursorx);
}

void Curses::WindowImplementation::moveCursorDown(int amount) {
  int cursorx=getcurx(cursesWindow.get());
  int cursory=getcury(cursesWindow.get());
  if (cursory+amount>=getmaxy(cursesWindow.get())){
    cursory=getmaxy(cursesWindow.get())-1;
  }else{
    cursory=cursory+amount;
  }
  wmove(cursesWindow.get(),cursory,cursorx);
}

void Curses::WindowImplementation::setAdvanceCursorOn() {
  cursor_on=true;
}

void Curses::WindowImplementation::setAdvanceCursorOff() {
  cursor_on=false;
}

Curses::RowReference Curses::WindowImplementation::at(int row) {
  return RowReference();
}

Curses::RowReference Curses::WindowImplementation::operator[](int row) {
  return this->at(row);
}

void Curses::WindowImplementation::refresh() {
  wrefresh(cursesWindow.get());

}

void Curses::WindowImplementation::log(std::ostream& out) {

}


