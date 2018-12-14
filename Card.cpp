// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#include <iostream>
#include <string>
#include "Card.h"

// for live game play - must not change!
void Card::display() const {
  std::cout << "[";
  if (value == 0)
    std::cout << "SB";
  else {
    std::cout << value;
  }
  std::cout << "]";
 }

// for saving game state - must not change!
std::string Card::toString() const {
  return std::to_string(value);
}

// Card constructor with value speicfication
Card::Card(int v) {
  value = v >= 0 && v <= 12 ? v : 0;
}

// Returns value of card
int Card::getValue() const {
 return value;
}
