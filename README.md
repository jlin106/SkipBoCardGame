Collaboration between: Jennifer Lin, Erlun Lian, Chester Huynh

SkipBo Card Game
----------------
Intermediate Programming Course Project, Programmed in C++

An implementation of the multiplayer version of the card game "Skip-Bo". Used object
oriented programming and inheritance-related classes. 

Base Classes and derived Classes
-----------------------------------------
- Card - represent the playing cards
- Pile -  uses a vector of cards to represent card piles 
    - DrawPile
    - FaceUpPile
       - BuildPile
    - Hand
- Player - has Hand and FaceUpPiles (Stock Pile and 4 Discard Piles) 
- SkipBoGame - has 2-4 Players, 4 Build Piles and a DrawPile
- Main - command line interactions for game play 

Game Structure
---------------
Main constructs a new SkipBoGame object (if initializing new game) or constructs a SkipBoGame object using 
readIn function (if save file is provided).

Once a SkipBoGame object is constructed, SkipBoGame.playGame() is called,
and takes in input to play save or quit the game, then loops through each
player's turn by PlayerTurn().

PlayerTurn() takes in input move or draw command.
- If player inputs move, moveCard() function is called and moves card based on input (start and end index)
- If player inputs draw, refills hand if hand is empty for player
- If player moves a card to a discard pile, then next player's turn

Game ends when a player's stock pile is empty.

