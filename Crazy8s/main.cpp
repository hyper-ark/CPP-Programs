#include <iostream>
#include <string>

#include "Card.h"
#include "Game.h"
#include "Player.h"

using std::string;

bool loadDeck(Game& g) {
  string filename;
  std::cout << "Choose a file to load the deck from:" << std::endl;
  std::cin >> filename;
  try {
    g.loadDeckFromFile(filename);
  } catch (std::invalid_argument const&) {
    std::cout << "The file was invalid. Aborting." << std::endl;
    return false;
  }
  return true;
}

int getPlayerCount() {
  std::cout << "Enter number of players:" << std::endl;
  int numPlayers;
  while (true) {
    if ((!(std::cin >> numPlayers)) || numPlayers <= 0) {
      if (std::cin.fail()) {
        // Clear the fail flag
        std::cin.clear();
        // Remove the non-integer data from the stream
        string garbage;
        std::cin >> garbage;
      }
      std::cout << "Please enter a positive number" << std::endl;
    } else {
      // break out of the loop once we've read a valid number
      break;
    }
  }
  return numPlayers;
}

void setupPlayers(Game& g, int numPlayers) {
  char input;
    for (int i = 0; i < numPlayers; i++) {
      std::cout << "Is player " << i << " an AI? (y/n)" << std::endl;
      while(true) {
        std::cin >> input;
        if (std::cin.fail() || (input != 'y' && input != 'n')) {
          std::cout << "Please enter y or n" << std::endl;
          continue;
        }
        break;
      }
      if (input == 'y') {
        g.addPlayer(true);
      }
      else if (input == 'n') {
        g.addPlayer(false);
      }
    }
}

void setupGame(Game& g) {
  int input;
  std::cout << "How many cards should each player start with?" << std::endl;
  while (true) {
    std::cin >> input;
    if (std::cin.fail() || input <= 0) {
      std::cout << "Please enter a positive number" << std::endl;
      std::cin.clear();
      string garbage;
      std::cin >> garbage;
      continue;
    }
    break;
  }
  Card* discard = g.deal(input);
  std::cout << "The initial discard is " << discard->getRank() << " " << discard->getSuit() << std::endl;
}

int main() {
  Game g;
  if (!loadDeck(g)) {
    return 1;
  }
  int numPlayers = getPlayerCount();
  setupPlayers(g, numPlayers);
  setupGame(g);
  int winner = g.runGame();
  if (winner != -1) {
    std::cout << "Player " << winner << " wins!" << std::endl;
  } else {
    std::cout << "The game is a draw!" << std::endl;
  }
  std::cout << "The most played suit was " << g.mostPlayedSuit() << std::endl;
  return 0;
}