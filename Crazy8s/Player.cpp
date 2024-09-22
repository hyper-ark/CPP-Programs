#include <iostream>
#include <sstream>

#include "Player.h"

using std::vector, std::string, std::size_t;

Player::Player(bool isAI) : isAI(isAI), hand({}) {
}

void Player::addToHand(Card* c) {
  hand.push_back(c);
}

size_t Player::getHandSize() {
  return hand.size();
}

std::string Player::getHandString() {
  std::stringstream ss;
  string rank;
  string suit;

  for (unsigned int i = 0; i < hand.size(); i++) {
    rank = hand.at(i)->getRank();
    suit = hand.at(i)->getSuit();

    if (i == 0) {
      ss << rank << " " << suit;
      continue;
    }

    ss << ", " << rank << " " << suit;
  }
  return ss.str();
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit) {
  if (isAI) {
    for (unsigned int i = 0; i < hand.size(); i++) {
      Card* card = hand.at(i);
      if (card->canBePlayed(currentRank, currentSuit)) {
        card->play();
        hand.erase(hand.begin() + i);
        currentRank = card->getRank();
        currentSuit = card->getSuit();
        return card;
      }
    }
    return nullptr;
  }
  else {
    std::cout << "Your hand contains: " << getHandString() << std::endl;
    std::cout << "The next card played must be a " << currentRank << " or " << currentSuit << std::endl;
    std::cout << "What would you like to play? (enter \"draw card\" to draw a card)" << std::endl;
    
    string rank;
    string suit;
    
    while (true) {
      std::cin >> rank >> suit;

      if (rank == "draw" && suit == "card") {
        return nullptr;
      }

      for (unsigned int i = 0; i < hand.size(); i++) {
        Card* card = hand.at(i);

        if (card->getRank() == rank && card->getSuit() == suit) {
          if (card->canBePlayed(currentRank, currentSuit)) {
            card->play();
            hand.erase(hand.begin() + i);
            currentRank = card->getRank();

            if (currentRank == "8") {
              std::cout << "What suit would you like to declare?" << std::endl;
              bool invalid = true;

              while (invalid) {
                std::cin >> suit;

                for (unsigned int j = 0; j < suits.size(); j++) {
                  if (suits.at(j) == suit) {
                    currentSuit = suit;
                    invalid = false;
                    break;
                  }
                  else if (j == suits.size() - 1) {
                    std::cout << "That's not a suit in this deck. Try again." << std::endl;
                  }
                }
              }
            }
            else {
              currentSuit = card->getSuit();
            }
            return card;
          }
          else {
            std::cout << "You can't play that card. Try again." << std::endl;
            break;
          }
        }
        else if (i == hand.size() - 1) {
          std::cout << "That's not a card you have. Try again." << std::endl;
        }
      }
    }
  }
}