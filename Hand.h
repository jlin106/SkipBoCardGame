// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#ifndef _HAND_H
#define _HAND_H

#include <vector>
#include <iostream>
#include "Pile.h"
#include "DrawPile.h"

class Hand : public Pile {

  public:
    /* The default constructor. */
    Hand() : Pile() { }

    /* Constructor using the readIn function for saved games. */
    Hand(std::istream & is);

    /* Dispilay function for live game play. */
    virtual void display() const;

};


#endif
