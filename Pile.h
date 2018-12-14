// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#ifndef _PILE_H
#define _PILE_H

#include <vector>
#include <iostream>
#include "Card.h"

/* The abstract base Pile class. */
class Pile {

  protected:
    /* The vector of cards. */
    std::vector<Card> pile;

  public:
    /* The default constructor. */
    Pile() { }

    /* Destructor. */
    virtual ~Pile() { }
    
    /* Return the size of the pile. */
    int size() const { return pile.size(); }

    /* Add card to the back of pile vector. */
    virtual void addCard(const Card& c);

    /* Return the value of the card at the back of the pile vecgtor. */
    int peekCard();

    /* Return the card at a specific index of the pile vector w/o removing it. */
    Card getCard(int index);

    /* Pop the card at the back of the pile vector. */
    Card popCard();

    /* Pop the card at a specfic index of the pile vector. */
    Card popCard(int index);

    /* ToString function for saving. */
    std::string toString() const;

    /* ReadIn function to read from istream into pile. */
    void readIn(std::istream & is);

    /* Pure virtual class for the display functions. */
    virtual void display() const = 0;  // for live game play, must override
};


#endif
