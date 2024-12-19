// Programmer: Sophia Bhoria
// Date: 10/21/2024
// Purpose: Defines the game logic and helper functions for Blackjack simulation.


#include "blackjack_simulator.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Function to generate a unique random card from a standard deck of 52 cards
Card generateRandomCard(bool dealtCards[DECK_SIZE]) {
    int cardIndex;
    do {
        cardIndex = rand() % DECK_SIZE;  // Get a random card index from 0 to 51
    } while (dealtCards[cardIndex]);  // Repeat if the card has already been dealt

    dealtCards[cardIndex] = true;  // Mark the card as dealt

    // Create a Card object based on the index
    Card card;
    card.value = (cardIndex % 13) + 1;  // Values from 1 (Ace) to 13 (King)
    card.suit = getSuitName();  // Assign a random suit (Hearts, Diamonds, etc.)

    return card;  // Return the generated card
}

// Function to determine if two cards form a Blackjack
bool isBlackjack(const Card &card1, const Card &card2) {
    return (card1.value == 1 && card2.value >= 10) || (card2.value == 1 && card1.value >= 10);
}

// Function to calculate the total hand value, considering the Ace as 1 or 11
int calculateHandTotal(const Card hand[], int handSize) {
    int total = 0;
    bool hasAce = false;

    for (int i = 0; i < handSize; ++i) {
        int value = hand[i].value;
        if (value > 10) value = 10;  // Face cards are worth 10
        if (value == 1) hasAce = true;  // Track if the hand has an Ace
        total += value;
    }

    // If the hand contains an Ace and the total is <= 11, count the Ace as 11
    if (hasAce && total <= 11) total += 10;

    return total;
}

// Function to sort the player's or dealer's hand (by suit, then value)
void sortHand(Card hand[], int handSize) {
    for (int i = 0; i < handSize - 1; ++i) {
        for (int j = i + 1; j < handSize; ++j) {
            if (hand[j] < hand[i]) {
                swap(hand[i], hand[j]);  // Sort by suit, then value
            }
        }
    }
}

// Function to print the player's or dealer's hand in sorted order
void printHand(Card hand[], int handSize) {
    sortHand(hand, handSize);  // Sort the hand before printing
    for (int i = 0; i < handSize; ++i) {
        cout << hand[i];
        if (i < handSize - 1) cout << ", ";
    }
    cout << endl;
}

// Utility function to get a suit name for a card
string getSuitName() {
    int suit = rand() % 4;  // Random number between 0 and 3
    switch (suit) {
        case 0: return "Hearts";
        case 1: return "Diamonds";
        case 2: return "Clubs";
        case 3: return "Spades";
        default: return "Unknown";
    }
}

// Function to display the outcome of the round
void displayOutcome(bool playerWins, bool isBlackjack, double &balance, double wager) {
    if (playerWins) {
        if (isBlackjack) {
            cout << "Player won with a Blackjack! ";
        } else {
            cout << "Player won this round! ";
        }
        cout << "Winnings: $" << fixed << setprecision(2) << (isBlackjack ? wager * 1.5 : wager) << endl;
    } else {
        cout << "Player lost this round. Wager: $" << fixed << setprecision(2) << wager << endl;
    }
    cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
}

// Function to update the player's balance after the round
void updatePlayerBalance(double &balance, double wager, bool playerWins, bool isBlackjack) {
    if (playerWins) {
        balance += isBlackjack ? wager * 1.5 : wager;
    } else {
        balance -= wager;
    }
}

// Function to display the game summary at the end
void displayGameSummary(int totalRounds, int totalRegularWins, int totalBlackjackWins, int totalRegularLosses, int totalBlackjackLosses, int totalRegularTies, int totalBlackjackTies, double initialBalance, double finalBalance) {
    double netGainLoss = finalBalance - initialBalance;

    cout << "\n=== Game Summary ===" << endl;
    cout << "Total Rounds Played: " << totalRounds << endl;
    cout << "Total Wins (Regular): " << totalRegularWins << endl;
    cout << "Total Wins (Blackjack): " << totalBlackjackWins << endl;
    cout << "Total Losses (Regular): " << totalRegularLosses << endl;
    cout << "Total Losses (Blackjack): " << totalBlackjackLosses << endl;
    cout << "Total Ties (Regular): " << totalRegularTies << endl;
    cout << "Total Ties (Blackjack): " << totalBlackjackTies << endl;
    cout << "Final Balance: $" << fixed << setprecision(2) << finalBalance << endl;
    cout << "Net Gain/Loss: " << (netGainLoss >= 0 ? "+" : "") << fixed << setprecision(2) << netGainLoss << endl;
    cout << "\nThank you for playing CodeJack: The Blackjack Simulator!" << endl;
    cout << "We hope to see you again soon.\n";
}
