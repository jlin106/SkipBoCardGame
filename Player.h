// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include <iostream>
#include "DrawPile.h"
#include "FaceUpPile.h"
#include "Hand.h"

/* The class representing a player of the SkipBoGame. */
class Player {

  private:
    /* The name of the player. */
    std::string name;
    /* The stock pile of the player. */
    FaceUpPile stock;
    /* The hand of the player. */
    Hand hand;
    /* Array of four discard piles of the player. */
    FaceUpPile discard[4];

  public:
    /* Player Constructor. */
    Player(int pNum);

    /* Constructor using the readIn function for saved games. */
    Player(std::istream & is);

    /* Destructor. */
    virtual ~Player() { }

    /* Display function for live game play */
    virtual void display() const;

    /* ToString function for saving. */
    std::string toString() const;

    /* ReadIn function to read from istream into player. */
    void readIn(std::istream & is);

    /* Returns player name. */
    std::string getName() const;

    /* Returns player's hand's size. */
    int getHandSize();

    /* Returns true if stock is empty. */
    bool stockIsEmpty();

    /* Returns true if hand is empty. */
    bool handIsEmpty();

  // DO WE NEED BOTH??
    /* Returns true of all discard piles are empty. */
    bool discardsAreEmpty();

    /* Returns true if specified discard pile is empty. */
    bool discardIsEmpty(int index);

    /* Add card to hand. */
    void addHand(Card c);

    /* Pops specific card in hand pile. */
    Card popHand(int index);

    /* Peeks specific card in hand pile. */
    int peekHand(int index);

    /* Adds card to specific discard pile. */
    void addDiscard(int index, Card c);

    /* Pops last card in specific discard pile. */
    Card popDiscard(int index);

    /* Peeks card in specific discard pile. */
    int peekDiscard(int index);

    /* Adds card to stock pile. */
    void addStock(Card c);

    /* Pops last card stock pile. */
    Card popStock();

    /* Peeks stock card. */
    int peekStock();

};


#endif
