// Erlun Lian, Jennifer Lin, Chester Huynh
// 601.220, Fall 2018

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "SkipBoGame.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::tolower;
using std::atoi;
using std::ifstream;

/* Converting command line arguments to lowercase. */
string toLowerCase(string input) {
  string output = "";
  for (unsigned int i = 0; i < input.length(); i++) {
    output += tolower(input[i]);
  }
  return output;
}

/* The main method. */
int main(int argc, char* argv[]) {
  // If there are 5 command line args, initialize new SkipBoGame
  if (argc == 5) {
    // Determine shuffle mode
    bool shuffle;
    string arg1(argv[1]);
    if (toLowerCase(arg1) == "true") {
      shuffle = true;
    }
    else if (toLowerCase(arg1) == "false") {
      shuffle = false;
    }
    else {
      cout << "invalid program usage: invalid first argument" << endl;
      return 1;
    }

    // Determine number of players
    int num_players = atoi(argv[2]);
    if (!(num_players >= 2 && num_players <= 6)) {
      cout << "invalid program usage: num players must be 2-6" << endl;
      return 1;
    }
    cout << "num players is " << num_players << endl;

    // Check that stock size is appropriate based on number of players
    int stock_size = atoi(argv[3]);
    if (num_players == 6) {
      if (stock_size > 20) {
        cout << "invalid program usage: bad stock size" << endl;
        return 1;
      }
    }
    else if (!(stock_size >= 1 && stock_size <= 30)) {
      cout << "invalid program usage: bad stock size" << endl;
      return 1;
    }
    cout << "stock size is " << stock_size << endl;

    // Check the deck pile is valid
    ifstream is(argv[4]);
    if (!is) {
      cout << "invalid program usage: can't open deck file" << endl;
      return 1;
    }

    // Create and start new skipbogame
    SkipBoGame newGame = SkipBoGame(shuffle, num_players, stock_size, is);
    newGame.playGame();
  }
  // If there are 3 command line args, load saved game
  else if (argc == 3) {
    // Determine shuffle mode
    bool shuffle;
    string arg1(argv[1]);
    if (toLowerCase(arg1) == "true") {
      shuffle = true;
    }
    else if (toLowerCase(arg1) == "false") {
      shuffle = false;
    }
    else {
      cout << "invalid program usage: invalid first argument" << endl;
      return 1;
    }

    // Check if saved state file can be opened
    ifstream is(argv[2]);
    if (!is) {
      cout << "invalid program usage: can't open input game file" << endl;
      return 1;
    }

    // Create and start saved skipbogame
    SkipBoGame savedGame = SkipBoGame(shuffle, is);
    savedGame.playGame();
  }
  else {
    cout << "invalid program usage: invalid number of arguments" << endl;
    return 1;
  }
  return 0;
}
