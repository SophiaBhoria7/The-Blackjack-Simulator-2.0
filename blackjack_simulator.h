// Programmer: Sophia Bhoria
// Date: 10/21/2024
// Purpose: Declare functions, constants, and shared definitions for the Blackjack game.

#ifndef BLACKJACK_SIMULATOR_H
#define BLACKJACK_SIMULATOR_H

#include <string>
#include <iostream>

// Constants for card values and balance
const int MIN_CARD = 1;  // Ace
const int MAX_CARD = 13;  // King
const int DECK_SIZE = 52; // Total number of cards in a deck
const double MIN_BALANCE = 12.00;
const double MAX_BALANCE = 7000.00;
const int MAX_HAND_SIZE = 20;  // Max number of cards in a hand

// Struct to represent a card with value and suit
struct Card {
    int value;
    std::string suit;

    // Overloading the < operator for sorting based on suit first, then value
    bool operator<(const Card &other) const {
        if (suit == other.suit)
            return value < other.value;
        return suit < other.suit;
    }

    // Overloading the << operator for printing card information
    friend std::ostream &operator<<(std::ostream &out, const Card &card) {
        out << card.value << " of " << card.suit;
        return out;
    }
};

// Function Prototypes
Card generateRandomCard(bool dealtCards[DECK_SIZE]);
bool isBlackjack(const Card &card1, const Card &card2);
int calculateHandTotal(const Card hand[], int handSize);
void updatePlayerBalance(double &balance, double wager, bool playerWins, bool isBlackjack);
void displayOutcome(bool playerWins, bool isBlackjack, double &balance, double wager);
void displayGameSummary(int totalRounds, int totalRegularWins, int totalBlackjackWins, int totalRegularLosses, int totalBlackjackLosses, int totalRegularTies, int totalBlackjackTies, double initialBalance, double finalBalance);
void sortHand(Card hand[], int handSize);
std::string getCardName(int value);
std::string getSuitName();
void printHand(Card hand[], int handSize);

#endif
