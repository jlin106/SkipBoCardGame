// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#include <iostream>
#include "DrawPile.h"

// Drawpile constructor from saved game file
DrawPile::DrawPile(bool shuffle, std::istream & is) : Pile(), isShuffled(shuffle) {
  readIn(is); // calls ReadIn function
  if (shuffle) { // if shuffle is true, shuffle the pile
    srand(time(0));
    int random = rand();
    std::shuffle(pile.begin(), pile.end(), std::default_random_engine(random));
  }
}

// Adds card to front of pile
void DrawPile::addFront(const Card& c) {
  pile.insert(pile.begin(), c);
}

// for live game play - must not change!
void DrawPile::display() const {
  std::cout << "[XX]/" << size();
}

// Return the shuffle state of the drawpile.
std::string DrawPile::getRand() const {
  if (isShuffled) {
    return "true";
  }
  else {
    return "false";
  }
}
