// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#ifndef _BUILDPILE_H
#define _BUILDPILE_H

#include <iostream>
#include <vector>
#include "FaceUpPile.h"

/* A derived BuildPile class from the base FaceUpPile class. */
class BuildPile: public FaceUpPile {

  public:
    /* The default constructor. */
    BuildPile() : FaceUpPile() { }

    /* Constructor using the readIn function. */
    BuildPile(std::istream & is) : FaceUpPile() {
      readIn(is);
    }

    /* Display function for live game play. */
    virtual void display() const {
      FaceUpPile::display();
    }

    /* Return true if the number is a valid add (sequential) to the build pile,
    false otherwise */
    bool isValidAdd(int num) {
      // If it is a SB card, always valid
      if (num == 0) {
        return true;
      }
      // If pile is empty, only valid if card is 1
      else if (pile.size() == 0 && num == 1) {
        return true;
      }
      // If pile is not empty, only valid if card is size + 1
      else if (pile.size() > 0 && (num == (int) pile.size() + 1)) {
        return true;
      }
      return false;
    }

    /* Return true if the build pile is full (size = 12), false otherwise. */
    bool isFull() {
      return pile.size() == 12;
    }

};

#endif
