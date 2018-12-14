// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#include <iostream>
#include <fstream>
#include <string>
#include "FaceUpPile.h"

// for live game play - must not change!
void FaceUpPile::display() const {
  if (size()) {
    pile[pile.size()-1].display();
  }
  else std::cout << "--";
  std::cout << "/" << size();
}

// FaceUpPile constructor from saved game file
FaceUpPile::FaceUpPile(std::istream & is) : Pile() {
  readIn(is);
}
