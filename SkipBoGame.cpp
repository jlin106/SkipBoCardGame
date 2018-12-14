// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "SkipBoGame.h"

// New game constructor
SkipBoGame::SkipBoGame (bool shuffle, int numPlayers, int stockSize, std::istream & is) : draw(shuffle, is) {
  // Initializing shuffle boolean
  isShuffled = shuffle;
  // Initializing players
  nump = numPlayers;
  for (int i = 0; i < nump; i++) {
    peep.push_back(Player(i));
  }
  // Distribute cards round robin style to fill player stock pile
  for (int i = 0; i < stockSize; i++) {
    for (int j = 0; j < nump; j++) {
      peep[j].addStock(draw.popCard());
    }
  }
  // Initializes 4 empty build piles
  for (int i = 0; i < 4; i++) {
    build[i] = BuildPile();
  }
  // If shuffle is true, start at random player
  if (shuffle) {
    srand(time(0));
    int random = rand();
    curp = random % nump;
  }
  else {
    // If shuffle is false, start at player 0
    curp = 0;
  }
}

// Saved game constructor
SkipBoGame::SkipBoGame (bool shuffle, std::istream & is) : draw() {
  // set game shuffle state to new shuffle command
  isShuffled = shuffle;
  // read in saved shuffle state, num players and current player
  std::string shuffled;
  is >> shuffled >> nump >> curp;
  // if shuffle state was originally false, make game with new shuffle state
  if (shuffled == "false") {
    readIn(isShuffled, is);
  }
  // else if shuffle state was originally true, don't reshuffle
  else {
    readIn(false, is);
  }

}

/* for live game play - must not change format!

drawPile  build_a  build_b  build_c  build_d
playerName  stock_0
discards: discard_1 discard_2 discard_3 discard_4
hand: card_5 card_6 card_7 card_8 card_9
 */
void SkipBoGame::display() const {
  std::cout << "Draw: ";
  draw.display();
  std::cout << "  Build Piles: ";
  for (int j = 0; j < 4; j++) {
    build[j].display();
    std::cout << " ";
  }
  std::cout << std::endl;
  peep[curp].display();
}

/* for saving state - must not change format!

shuffle numplayers currplayer
PlayerCurp [display]
PlayerCurp+1 [display]
[etc for all players]
Draw [display]
Build_a [display]
Build_b [display]
Build_c [display]
Build_d [display]
*/
std::string SkipBoGame::toString() const {
  std::stringstream result;
  int idx;
  result << draw.getRand() << " " << nump << " " << curp << "\n";
  for (int i = 0; i < nump; ++i) {
    idx = (curp+i) % nump;
    result << peep[idx].toString();
  }
  result << "Draw " << draw.toString();
  for (int j = 0; j < 4; j++) {
    result << "Build_" << char('a'+j) << " ";
    result << build[j].toString();
  }
  return result.str();
}

// ReadIn function to read from istream into SkipBoGame.
void SkipBoGame::readIn(bool shuffle, std::istream & is) {
  // Add players using the player readIn function to vector of Players
  for (int i = 0; i < nump - curp; i++) {
    peep.push_back(Player(is));
  }
  for (int i = 0; i < curp; i++) {
    peep.insert(peep.begin() + i, Player(is));
  }
  // Create draw and build piles using pile readIn function
  draw = DrawPile(shuffle, is);
  for (int i = 0; i < 4; i++) {
    build[i] = BuildPile(is);
  }
}

// Returns true if the player won
bool SkipBoGame::checkPlayerWin() {
  return peep[curp].stockIsEmpty();
}

// Convert the input char to index representing the type of pile:
// 0 = stock, 1 = discard, 2 = hand, 3 = build
char SkipBoGame::convertType(char index) {
  switch (index) {
    case '0': return '0';
    case '1': case '2': case '3': case '4': return '1';
    case '5': case '6': case '7': case '8': case '9': return '2';
    case 'a': case 'b': case 'c': case 'd': return '3';
    default: return '\0';
  }
}

/* Moves card from stock pile to a specified build pile
 */
void SkipBoGame::moveFromStockToBuild(char end) {
  int ind = -1;
  // If stock is empty, invalid move
  if (!peep[curp].stockIsEmpty()) {
    // Converting player input index for build pile to vector index
    switch(end) {
      case 'a':
        ind = 0;
        break;
      case 'b':
        ind = 1;
        break;
      case 'c':
        ind = 2;
        break;
      case 'd':
        ind = 3;
        break;
      default: // if user input is invalid
        std::cout << "illegal command, try again" << std::endl;
        return;
    }

    // Move card if it is a valid add
    if (build[ind].isValidAdd(peep[curp].peekStock())) {
      Card c = peep[curp].popStock();
      build[ind].addCard(c);
    }
    else {
      std::cout << "illegal command, try again" << std::endl;
    }
    // If full, pop build to asidePile vector
    if (build[ind].isFull()) {
      for (int i = 0; i < 12; i++) {
        Card c = build[ind].popCard(0);
        asidePile.push_back(c);
      }
      std::cout << "build pile " << end << " full, set aside" << std::endl;
    }
  }
  // If move is invalid
  else {
    std::cout << "illegal command, try again" << std::endl;
  }
}

/* Moves card from a specified discard pile to a specified build pile
 */
void SkipBoGame::moveFromDiscardToBuild(char start, char end) {
  int discardInd = start - '0' - 1;
  int buildInd = -1;
  if (!peep[curp].discardIsEmpty(discardInd)) {
    // Converting player input index to vector index
    switch(end) {
      case 'a':
        buildInd = 0;
        break;
      case 'b':
        buildInd = 1;
        break;
      case 'c':
        buildInd = 2;
        break;
      case 'd':
        buildInd = 3;
        break;
      default:
        std::cout << "illegal command, try again" << std::endl;
        return;
    }

    // Move card
    if (build[buildInd].isValidAdd(peep[curp].peekDiscard(discardInd))) {
      Card c = peep[curp].popDiscard(discardInd);
      build[buildInd].addCard(c);
    }
    else {
      std::cout << "illegal command, try again" << std::endl;
    }

    // if full, pop build to asidePile vector
    if (build[buildInd].isFull()) {
      for (int i = 0; i < 12; i++) {
        Card c = build[buildInd].popCard(0);
        asidePile.push_back(c);
      }
      std::cout << "build pile " << end << " full, set aside" << std::endl;
    }
  }
  // Otherwise invalid
  else {
    std::cout << "illegal command, try again" << std::endl;
  }
}


/* Moves specified card from hand to specified build pile
 */
void SkipBoGame::moveFromHandToBuild(char start, char end) {
  int handInd = start - '0' - 5; // hand ranges from 5 - 9
  int buildInd = -1;
  // If index is empty, invalid move
  if (!(peep[curp].handIsEmpty() || handInd > peep[curp].getHandSize() - 1)) {
    // Converting display index to vector index
    switch(end) {
      case 'a':
        buildInd = 0;
        break;
      case 'b':
        buildInd = 1;
        break;
      case 'c':
        buildInd = 2;
        break;
      case 'd':
        buildInd = 3;
        break;
      default:
        std::cout << "illegal command, try again" << std::endl;
        return;
    }

    // Moving card
    if (build[buildInd].isValidAdd(peep[curp].peekHand(handInd))) {
      Card c = peep[curp].popHand(handInd);
      build[buildInd].addCard(c);
    }
    else {
      std::cout << "illegal command, try again" << std::endl;
    }

    // if full, pop build to asidePile vector
    if (build[buildInd].isFull()) {
      for (int i = 0; i < 12; i++) {
        Card c = build[buildInd].popCard(0);
        asidePile.push_back(c);
      }
      std::cout << "build pile " << end << " full, set aside" << std::endl;
    }
  }
  else {
      std::cout << "illegal command, try again" << std::endl;
  }
}

/* Moves specified card from hand to specified discard pile
 */
bool SkipBoGame::moveFromHandToDiscard(char start, char end) {
  // Converting hand index from user input to vector index
  int handInd = start - '0' - 5;
  // If index is invalid or hand is empty, invalid move
  if (!(peep[curp].handIsEmpty() || handInd > peep[curp].getHandSize() - 1)) {
    // Dicsard ranges from 1 - 4, converting to 0 - 3
    int discardInd = end - '0' - 1;
    // Moving card
    Card c = peep[curp].popHand(handInd);
    peep[curp].addDiscard(discardInd, c);
    return true;
  }
  else {
    std::cout << "illegal command, try again" << std::endl;
    return false;
  }
}

/* Move a card from start pile to end pile based on player input
 */
bool SkipBoGame::moveCard(char start, char end) {
  // Convert start and end char to more convenient number
  char sType = convertType(start);
  char eType = convertType(end);
  bool moved = false;
  // Switch cases to check validity of the move
  switch (sType) {
    case '0':
      if (eType == '3') {
        // move from stock to build
        moveFromStockToBuild(end);
      }
      else {
        std::cout << "illegal command, try again" << std::endl;
      }
      break;
    case '1':
      if (eType == '3') {
        // move from discard to build
        moveFromDiscardToBuild(start, end);
      }
      else {
        std::cout << "illegal command, try again" << std::endl;
      }
      break;
    case '2':
      if (eType == '1') {
        // move from hand to discard and checks if move to discard is successful
        moved = moveFromHandToDiscard(start, end);
      }
      else if (eType == '3') {
        // move from hand to build
        moveFromHandToBuild(start, end);
      }
      else {
        std::cout << "illegal command, try again" << std::endl;
      }
      break;
    default:
      // All other pile moves are invalid
      std::cout << "illegal command, try again" << std::endl;
  }
  return moved;
}

/* Checks the move type that curp wants to perform based once
command line inputs
*/
bool SkipBoGame::playerMove(char move, char start, char end) {
  switch(move) {
    case 'm': case 'M':
      // Move card from start to end
      return moveCard(start, end);

    case 'd': case 'D':
      // Only draw if hand is empty
      if (peep[curp].handIsEmpty()) {
        while (peep[curp].getHandSize() != 5) {
          peep[curp].addHand(draw.popCard());
          // Refill draw with aside pile if it is empty
          if (drawIsEmpty()) {
            // If shuffle is true, shuffle aside pile before adding
            if (isShuffled) {
              srand(time(0));
              int random = rand() % asidePile.size();
              std::shuffle(asidePile.begin(), asidePile.end(), std::default_random_engine(random));
            }
            // Add from aside pile and delete card
            for (int i = asidePile.size() - 1; i >= 0; i--) {
              draw.addCard(asidePile[i]);
              asidePile.pop_back();
            }
          }
        }
      }
      else {
        std::cout << "illegal command, try again" << std::endl;
      }
      return false;
    default:
      std::cout << "illegal command, try again" << std::endl;
      return false;
  }
}

/* During a player's turn, allow the player to perform moves until
either the player wins or they add a card to their discard pile
*/
void SkipBoGame::playerTurn() {
  display();
  bool addedToDiscard = false;
  // Check if current player's turn ends
  while (!checkPlayerWin() && !(addedToDiscard)) {
    std::cout << "(m)ove [start] [end] or (d)raw ? ";
    std::string moveString, startString, endString;
    char move, start, end;
    move = start = end = '\0';
    // Read in first string
    std::cin >> moveString;
    if (moveString.length() == 1) {
      // Convert the string to char if length was 1
      move = moveString.at(0);
    }
    else {
      std::cout << "illegal command, try again" << std::endl;
      std::cout << std::endl;
      display();
      continue;
    }

    // If player is moving cards, take in 2 more values
    if (move == 'm' || move == 'M') {
      std::cin >> startString;
      if (startString.length() == 1) {
        // Read in the char for a start pile if length was 1
        start = startString.at(0);
      }
      else {
        std::cout << "illegal command, try again" << std::endl;
        std::cout << std::endl;
        display();
      }

      std::cin >> endString;
      if (endString.length() == 1) {
        // Read in the char for a end pile if length was 1
        end = endString.at(0);
      }
      else {
        std::cout << "illegal command, try again" << std::endl;
        std::cout << std::endl;
        display();
      }
    }

    // Do player move and update bool if they added to discard pile
    addedToDiscard = playerMove(move, start, end);
    std::cout << "\n";
    // Only display if player didn't win
    if (!checkPlayerWin()) {
      display();
    }
  }

  // Check if current player won, if not, update curp
  if (checkPlayerWin()) {
    std::cout << "GAME OVER - " << peep[curp].getName() << " wins!\n";
  }
  else {
    curp = (curp + 1) % nump; // Bounds curp between 0 and nump - 1
  }
}

/* Initialize game play. */
void SkipBoGame::playGame() {
  // Check if game ends
  while (!checkPlayerWin()) {
    // Standard game display for each person's turn
    std::cout << std::endl << " >> " << peep[curp].getName() << " turn next" << std::endl;
    std::cout << "(p)lay, (s)ave, or (q)uit ? ";
    std::string commandString;
    // Read in string for the command
    std::cin >> commandString;
    char command;
    if (commandString.length() == 1) {
      // Read in p, s, or q if length was 1
      command = commandString.at(0);
    }
    else {
      std::cout << "illegal command, try again" << std::endl;
      continue;
    }

    switch (command) {
      // Player plays turn
      case 'p': case 'P':
        // Replenishes hand
        while (peep[curp].getHandSize() != 5) {
          peep[curp].addHand(draw.popCard());
          // Refill draw if it is empty
          if (drawIsEmpty()) {
            // If shuffle is true, shuffle aside pile before adding
            if (isShuffled) {
              srand(time(0));
              int random = rand() % asidePile.size();
              std::shuffle(asidePile.begin(), asidePile.end(), std::default_random_engine(random));
            }
            // Add from aside pile and delete card
            for (int i = asidePile.size() - 1; i >= 0; i--) {
                draw.addCard(asidePile[i]);
                asidePile.pop_back();
            }
          }
        }
        playerTurn();
        break;
      // Player saves game state
      case 's': case 'S': {
        // if there are cards set aside, add to draw
        if (!(asidePile.empty())) {
          for (int i = (int) asidePile.size() - 1; i >= 0; i--) {
            draw.addFront(asidePile.at(i));
          }
        }
        // get filename and save to filename
        std::cout << "save filename: ";
        std::string filename;
        std::cin >> filename;
        std::ofstream savefile(filename);
        savefile << toString();
        savefile.close();
        return;
      }
      // Player quits game
      case 'q': case 'Q':
        std::cout << "thanks for playing" << std::endl;
        return;
      default: std::cout << "illegal command, try again" << std::endl;
    }
  }
}
