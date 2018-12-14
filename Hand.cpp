// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#include <iostream>
#include "Hand.h"

// for live game play - must not change!
void Hand::display() const {
  int i;
  for (i = 0; i < size(); i++) {
    pile[i].display();
    std::cout << "  ";
  }
  for ( ; i < 5; i++)
    std::cout << "--  ";
}

// Hand constructor from saved game file
Hand::Hand(std::istream & is) : Pile() {
  readIn(is);
}
