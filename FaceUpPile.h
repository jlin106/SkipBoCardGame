// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#ifndef _FACEUPPILE_H
#define _FACEUPPILE_H

#include <iostream>
#include <vector>
#include "DrawPile.h"
#include "Pile.h"

/* A derived FaceUpPile class from the base Pile class. */
class FaceUpPile: public Pile {

  public:
    /* The default constructor. */
    FaceUpPile() : Pile() { }

    /* Constructor using the readIn function for saved games. */
    FaceUpPile(std::istream & is);

    /* Dispilay function for live game play. */
    virtual void display() const;

};

#endif
