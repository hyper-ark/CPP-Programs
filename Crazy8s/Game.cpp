#include "Game.h"

#include <iostream>
#include <fstream>
#include <sstream>

using std::string, std::vector;

Game::Game() : players({}), suits({}), ranks({}), deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename) {
  std::ifstream file(filename);
  std::stringstream ss;
  string suit;
  string rank;
  string line;
  string item;

  if(!file.is_open()) {
    throw std::invalid_argument("File failed to open");
  }

  std::getline(file, line);
  ss.str(line);
  while (ss >> item) {
    suits.push_back(item);
  }

  ss.clear();
  std::getline(file, line);
  ss.str(line);
  while (ss >> item) {
    ranks.push_back(item);
  } 

  while(std::getline(file, line)) {
    std::stringstream newCard(line);
    newCard >> rank >> suit;

    if (newCard.fail()) {
      throw std::runtime_error("Not enough data");
    }

    if (!newCard.eof()) {
      throw std::runtime_error("Too much data");
    }

    for (unsigned int i = 0; i < suits.size(); i++) {
      if (suit == suits.at(i)) {
        break;
      }
      else if (i == suits.size() - 1) {
        throw std::runtime_error("Suit not in suits");
      }
    }

    for (unsigned int i = 0; i < ranks.size(); i++) {
      if (rank == ranks.at(i)) {
        break;
      }
      else if (i == ranks.size() - 1) {
        throw std::runtime_error("Rank not in ranks");
      }
    }

    try {
      Card* card = new Card(rank, suit);
      deck.push_back(card);
      drawPile.insert(drawPile.begin(), card);
    }
    catch (const std::invalid_argument &e) {
      throw std::runtime_error("Invalid argument");
    }

  }
  file.close();
}

void Game::addPlayer(bool isAI) {
  Player* player = new Player(isAI);
  players.push_back(player);
}

void Game::drawCard(Player* p) {

  if (drawPile.size() == 0) {
    std::cout << "Draw pile, empty, flipping the discard pile." << std::endl;

    if (discardPile.size() == 0) {
      throw std::runtime_error("Piles empty");
    }
    else {
      for (int i = discardPile.size() - 1; i >= 0; i--) {
        drawPile.push_back(discardPile.at(i));
      }
      discardPile.clear();
    }
  }
  p->addToHand(drawPile.back());
  drawPile.pop_back();
}

// deals numCards cards to each player
Card* Game::deal(int numCards) {
  Card* discard = drawPile.back();
  discardPile.push_back(discard);
  drawPile.pop_back();

  for (int i = 0; i < numCards; i++) {
    for (unsigned int j = 0; j < players.size(); j++) {
      drawCard(players.at(j));
    }
  }
  return discard;
}

string Game::mostPlayedSuit() {
  vector<int> suitsPlayed;
  int suitTimesPlayed;

  for (unsigned int j = 0; j < suits.size(); j++) {
    suitTimesPlayed = 0;
    string suit = suits.at(j);
    
    for (unsigned int i = 0; i < deck.size(); i++) {
      Card* card = deck.at(i);

      if (card->getSuit() == suit) {
        suitTimesPlayed += card->getTimesPlayed();
      }
    }
    suitsPlayed.push_back(suitTimesPlayed);
  }

  int max = suitsPlayed.at(0);
  int index = 0;

  for (unsigned int i = 0; i < suitsPlayed.size(); i++) {
    if (suitsPlayed.at(i) > max) {
      index = i;
      max = suitsPlayed.at(i);
    }
  }

  return suits.at(index);
}

int Game::runGame() {
  string currentRank = deck[0]->getRank();
  string currentSuit = deck[0]->getSuit();
  Card* played;
  Player* curPlayer;

  while (true) {
    for (unsigned int i = 0; i < players.size(); i++) {
      std::cout << "Player " << i << "'s turn!" << std::endl;
      curPlayer = players.at(i);
      played = curPlayer->playCard(suits, currentRank, currentSuit);
      if (played == nullptr) {
        try {
          drawCard(curPlayer);
        } catch (const std::runtime_error& e) {
          std::cout << "Player " << i << " cannot draw a card." << std::endl;
          return -1;
        }
        
        std::cout << "Player " << i << " draws a card." << std::endl;
        continue;
      }
      else {
        discardPile.push_back(played);
      }
      if (currentRank == "8") {
        std::cout << "Player " << i << " plays " << played->getRank() << " " << played->getSuit();
        std::cout << " and changes the suit to " << currentSuit << "." << std::endl;
      }
      else {
        std::cout << "Player " << i << " plays " << played->getRank() << " " << played->getSuit() << "." << std::endl;
        currentSuit = played->getSuit();
      }
      currentRank = played->getRank();

      if (curPlayer->getHandSize() == 0) {
        return i;
      }
    }
  }
}

// Destructor--Deallocates all the dynamic memory we allocated
Game::~Game() {
  for (unsigned int i = 0; i < deck.size(); i++) {
    delete deck.at(i);
  }
  for (unsigned int i = 0; i < players.size(); i++) {
    delete players.at(i);
  }
}
