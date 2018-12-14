// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#include <vector>
#include "Pile.h"

// Add card to the pile.
void Pile::addCard(const Card& c) {
  pile.push_back(c);
}

// Return the value of the card at end of pile
int Pile::peekCard() {
  return pile.back().getValue();
}

// Get the card at a specific index.
Card Pile::getCard(int index) {
  Card c = pile.at(index);
  return c;
}

// Pop the card at the back of the pile vector.
Card Pile::popCard() {
  Card c = Card(pile.back().getValue());
  pile.pop_back(); // Remove it from the vector
  return c;
}

// Pop the card at a specific index of the pile vector.
Card Pile::popCard(int index) {
  Card c = pile.at(index);
  pile.erase(pile.begin() + index); // Remove it from the vector
  return c;
}

// for saving game state - must not change!
std::string Pile::toString() const {
  std::string result;
  result.append(std::to_string(size()));
  result.append("\n");
  // add all the pile elements to the string, at most 20 per line
  for (int i=0; i < size(); ++i) {
    if (i % 20 == 0 && i != 0)
      result.append("\n");
    else if (i != 0)
      result.append(" ");
    result.append(pile[i].toString());
  }
  result.append("\n");
  return result;
}

// Read in from istream into pile.
void Pile::readIn(std::istream & is) {
  int num;
  int next = is.peek(); // Peek the istream
  // If next is a digit, take in all the digits and add to pile
  if (std::isdigit(next)) {
    while(is >> num) {
      Card c = Card(num);
      addCard(c);
    }
  }
  // If next was not a digit, take in string pile type and int size first
  else {
    std::string pileType;
    int pileSize;
    is >> pileType >> pileSize;
    // Read in the digits and add to the pile
    for (int i = 0; i < pileSize; i++) {
      is >> num;
      Card c = Card(num);
      addCard(c);
    }
  }
}
