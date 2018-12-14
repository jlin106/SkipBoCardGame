// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#include <iostream>
#include <string>
#include <sstream>
#include "Player.h"

// Player constructor
Player::Player(int pNum) : stock(), hand() {
  // Set player name.
  name = "Player" + std::to_string(pNum);
  // Initialize discard piles
  for (int i = 0; i < 4; i++) {
    discard[i] = FaceUpPile();
  }
  // Initialize stock pile
  stock = FaceUpPile();
}

// Player constructor from saved file
Player::Player(std::istream & is) : stock(), hand() {
  readIn(is);
}

// for live game play - must not change!
void Player::display() const {
  std::cout << "Current ";
  std::cout << name << ":  Stock{0}: " ;
  stock.display();
  std::cout << std::endl;
  std::cout << "   Discards{1-4}: ";
  for (int i = 0; i < 4; ++i) {
    discard[i].display();
    std::cout << "  ";
  }
  std::cout << std::endl;
  std::cout << "   Hand{5-9}: ";
  hand.display();
  std::cout << std::endl;
}

/* saving state format - must not change!
PlayerName
Stock size
01 02 03  ...
...
Hand size
01 02 03 04 05
Discard1 size
01 02 03 04 ...
...
Discard2 size
...
Discard3 size
...
Discard4 size
...
*/
std::string Player::toString() const {
  std::stringstream result;
  result << name << "\n";
  result << "Stock " << stock.toString();
  result << "Hand " << hand.toString();
  for (int i = 0; i < 4; ++i) {
    result << "Discard" << i << " " << discard[i].toString();
  }
  return result.str();
}

// Reads savedgame file
void Player::readIn(std::istream & is) {
  // Read in name of player
  is >> name;
  // Initialize player piles using respective readin constructors
  stock = FaceUpPile(is);
  hand = Hand(is);
  for (int i = 0; i < 4; i++) {
    discard[i] = FaceUpPile(is);
  }
}

// Returns player name
std::string Player::getName() const {
  return name;
}

// Returns player's hand's size
int Player::getHandSize() {
  return hand.size();
}

// Returns true if stock is empty
bool Player::stockIsEmpty() {
  return stock.size() == 0;
}

// Returns true if hand is empty
bool Player::handIsEmpty() {
  return hand.size() == 0;
}

// Returns true of all discard piles are empty
bool Player::discardsAreEmpty() {
  for (int i = 0; i < 4; i++) {
    if (!(discardIsEmpty(i))) {
      return false;
    }
  }
  return true;
}

// Returns true if specified discard pile is empty
bool Player::discardIsEmpty(int index) {
  return discard[index].size() == 0;
}

// Add card to hand
void Player::addHand(Card c) {
  hand.addCard(c);
}

// Pops specific card in pile vector of hand
Card Player::popHand(int index) {
  return hand.popCard(index);
}

// Peeks specific card in pile vector of hand
int Player::peekHand(int index) {
  return hand.getCard(index).getValue();
}

// Adds card to a specific discard pile
void Player::addDiscard(int index, Card c) {
  discard[index].addCard(c);
}

// Pops last card in specific discard pile
Card Player::popDiscard(int index) {
  return discard[index].popCard();
}

// Peeks card in specific discard pile
int Player::peekDiscard(int index) {
  return discard[index].peekCard();
}

// Adds card to stock pile
void Player::addStock(Card c) {
  stock.addCard(c);
}

// Pops last card stock pile
Card Player::popStock() {
  return stock.popCard();
}

// Peeks first stock card
int Player::peekStock() {
  return stock.peekCard();
}
