// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#ifndef _DRAWPILE_H
#define _DRAWPILE_H

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include "Pile.h"
#include "Card.h"

/* A derived DrawPile class from the base Pile class. */
class DrawPile : public Pile {

  private:
    /* If the draw pile is shuffled. */
    bool isShuffled;

  public:
    /* The default constructor. */
    DrawPile() : Pile() { }

    /* Constructor using the readIn function and new shuffle state
    for previously saved games. */
    DrawPile(bool shuffle, std::istream & is);

    /* Adds card to front of the draw pile. */
    void addFront(const Card& c);

    /* Dispilay function for live game play. */
    virtual void display() const;

    /* Return the shuffle state of the drawpile. */
    std::string getRand() const;

};

#endif
