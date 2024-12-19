// Programmer: Sophia Bhoria
// Date: 10/21/2024
// Purpose: This program simulates a simplified Blackjack game between a player and a dealer.
//          It includes features such as wagering, hitting, standing, and Blackjack detection.

#include "blackjack_simulator.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {
    srand(370);  // Seed random number generator
    bool dealtCards[DECK_SIZE] = {false};  // Track dealt cards

    string playerName;
    double balance = MIN_BALANCE + (rand() % static_cast<int>(MAX_BALANCE - MIN_BALANCE + 1)) + (rand() % 100 / 100.0);
    double initialBalance = balance;
    double wager;
    char playAgain = 'Y';

    int totalRounds = 0, totalRegularWins = 0, totalBlackjackWins = 0, totalRegularLosses = 0, totalBlackjackLosses = 0, totalRegularTies = 0, totalBlackjackTies = 0;

    cout << "Welcome to CodeJack: The Blackjack Simulator!\n";
    cout << "Player, please enter your name: ";
    cin >> playerName;
    cout << "Hi " << playerName << ", your starting balance is $" << fixed << setprecision(2) << balance << ".\n";

    while (playAgain == 'Y' && balance > 0) {
        totalRounds++;
        cout << "\nRound " << totalRounds << "\n";
        cout << "Player balance: $" << fixed << setprecision(2) << balance << endl;

        do {
            cout << "Enter wager: $";
            cin >> wager;
        } while (wager > balance || wager <= 0);

        // Deal cards
        Card playerHand[2], dealerHand[2];
        playerHand[0] = generateRandomCard(dealtCards);
        playerHand[1] = generateRandomCard(dealtCards);
        dealerHand[0] = generateRandomCard(dealtCards);
        dealerHand[1] = generateRandomCard(dealtCards);

        cout << "Player's hand: "; printHand(playerHand, 2);
        cout << "Dealer's hand: " << dealerHand[0] << ", [Hidden Card]" << endl;

        // Check for Blackjack
        bool playerHasBlackjack = isBlackjack(playerHand[0], playerHand[1]);
        bool dealerHasBlackjack = isBlackjack(dealerHand[0], dealerHand[1]);

        if (playerHasBlackjack || dealerHasBlackjack) {
            if (playerHasBlackjack && dealerHasBlackjack) {
                cout << "It's a tie! Both have Blackjack!\n";
                totalBlackjackTies++;
            } else if (playerHasBlackjack) {
                cout << "Player has Blackjack!\n";
                totalBlackjackWins++;
                updatePlayerBalance(balance, wager, true, true);
            } else {
                cout << "Dealer has Blackjack! Player loses.\n";
                totalBlackjackLosses++;
                updatePlayerBalance(balance, wager, false, false);
            }
        } else {
            // Handle player's turn (Hit/Stand logic could be added here)

            // Handle dealer's turn (Dealer hits until 17 or more)

            // Compare hand totals to determine winner
            int playerTotal = calculateHandTotal(playerHand, 2);
            int dealerTotal = calculateHandTotal(dealerHand, 2);

            if (playerTotal > dealerTotal && playerTotal <= 21) {
                cout << "Player wins!\n";
                totalRegularWins++;
                updatePlayerBalance(balance, wager, true, false);
            } else if (dealerTotal > 21) {
                cout << "Dealer busts! Player wins.\n";
                totalRegularWins++;
                updatePlayerBalance(balance, wager, true, false);
            } else if (playerTotal == dealerTotal) {
                cout << "It's a tie!\n";
                totalRegularTies++;
            } else {
                cout << "Dealer wins!\n";
                totalRegularLosses++;
                updatePlayerBalance(balance, wager, false, false);
            }
        }

        cout << "Balance Update: $" << fixed << setprecision(2) << balance << endl;

        if (balance > 0) {
            cout << "Play another round? (Y/N): ";
            cin >> playAgain;
        } else {
            cout << "You're out of balance!\n";
            break;
        }
    }

    // Display game summary at the end
    displayGameSummary(totalRounds, totalRegularWins, totalBlackjackWins, totalRegularLosses, totalBlackjackLosses, totalRegularTies, totalBlackjackTies, initialBalance, balance);

    return 0;
}
