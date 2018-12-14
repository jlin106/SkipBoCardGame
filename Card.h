// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#ifndef _CARD_H
#define _CARD_H

/* A Card class to represent a deck card. */
class Card {

  private:
    /* The value of the card */
    int value;  // 0 for skip-bo card

  public:
    /* Default card constructor, sets value to 0. */
    Card(): value(0) { }

    /* Card constructor with value speicfication. */
    Card(int v);

    /* Returns value of card. */
    int getValue() const;

    /* Display function for live game play */
    void display() const;

    /* ToString function for printing/file saving. */
    std::string toString() const;

};

#endif
