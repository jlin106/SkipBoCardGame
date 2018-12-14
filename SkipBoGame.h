// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#ifndef _SKIPBOGAME_H
#define _SKIPBOGAME_H

#include <vector>
#include <iostream>
#include "DrawPile.h"
#include "BuildPile.h"
#include "Player.h"

/* The class representing the SkipBoGame. */
class SkipBoGame {

  private:
    /* The vector of players. */
    std::vector<Player> peep;
    /* The draw pile of the game. */
    DrawPile draw;
    /* The array of 4 build piles. */
    BuildPile build[4];
    /* The number of players. */
    int nump;
    /* The current player. */
    int curp;
    /* The vector of cards for the completed build piles. */
    std::vector<Card> asidePile;
    /* The shuffle mode of the game. */
    bool isShuffled;

  public:
    /* The constructor for a new SkipBoGame. */
    SkipBoGame (bool shuffle, int numP, int stockSize, std::istream & is);

    /* The constructor saved Skipbogame using ReadIn function. */
    SkipBoGame (bool shuffle, std::istream & is);

    /* ReadIn function to read from istream into SkipBoGame. */
    void readIn(bool shuffle, std::istream & is);

    /* Display function for live game play. */
    virtual void display() const;

    /* ToString function for saving state. */
    std::string toString() const;

    /* Returns true if draw pile is empty. */
    bool drawIsEmpty() { return draw.size() == 0; }

    /* Checks if current player has won. */
    bool checkPlayerWin();

    /* Convert player entered char for pile index to a more convenient char. */
    char convertType(char index);

    /* Move card function that calls more specific move functions based on
    user input. */
    bool moveCard(char start, char end);

    /* Specific move from stock to build. */
    void moveFromStockToBuild(char index);

    /* Specific move from discard to build. */
    void  moveFromDiscardToBuild(char start, char end);

    /* Specific move from hand to build. */
    void moveFromHandToBuild(char start, char end);

    /* Specific move from hand to discard. */
    bool moveFromHandToDiscard(char start, char end);

    /* Helper player move function. */
    bool playerMove(char move, char start, char end);

    /* Player Turn. */
    void playerTurn();

    /* Runs the game. */
    void playGame();
};


#endif
