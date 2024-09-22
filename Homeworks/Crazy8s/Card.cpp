#include <iostream>
#include <cctype>

#include "Card.h"

using std::string;

Card::Card(string rank, string suit) : rank(rank), suit(suit), timesPlayed(0) {
  if (rank.empty() || suit.empty()) {
    throw std::invalid_argument("Invalid Character");
  }
  for (unsigned int i = 0; i < rank.length(); i++) {
    if (!(isalnum(rank.at(i)))) {
      throw std::invalid_argument("Invalid Character");
    }
  }
    for (unsigned int i = 0; i < suit.length(); i++) {
    if (!(isalnum(suit.at(i)))) {
      throw std::invalid_argument("Invalid Character");
    }
  }
}

string Card::getRank() {
  return rank;
}

string Card::getSuit() {
  return suit;
}

int Card::getTimesPlayed() {
  return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit) {
  if (this->rank == currentRank || this->suit == currentSuit || this->rank == "8") {
    return true;
  }
  return false;
}

void Card::play() {
  timesPlayed++;
}
