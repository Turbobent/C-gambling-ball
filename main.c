#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

// Function prototypes
void addBalance(int *balance);
void showLeaderboard();
void playFootballGame(int *balance);
void playSlotMachine(int *balance);
void playBaccarat(int *balance);
int checkSlotWin(int a, int b, int c);
void spinWheel(int min, int max, int results[3]);


int main() {
    char gameChoice[2];
    int balance = 100;
    int menuChoice;

    srand(time(0));

    do {
        printf("\n===== Main Menu =====\n");
        printf("1. Play Football Betting Game\n");
        printf("2. Play Slot Machine\n");
        printf("3. Play Baccarat\n");  // Changed from "play Baccarat" to "Play Baccarat"
        printf("4. Add Money\n");      // Changed from 3 to 4
        printf("5. View Leaderboard\n"); // Changed from 4 to 5
        printf("6. Quit\n");           // Changed from 5 to 6
        printf("Current Balance: %d\n", balance);
        printf("Enter your choice: ");
        scanf("%d", &menuChoice);
        printf("\n===== Main Menu =====\n");


      switch (menuChoice) {
        case 1:
            playFootballGame(&balance);
            break;
        case 2:
            playSlotMachine(&balance);
            break;
        case 3:
            playBaccarat(&balance);  // New Baccarat game
            break;
        case 4:
            addBalance(&balance);
            break;
        case 5:
            showLeaderboard();
            break;
        case 6:
            printf("Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
}

        if (balance <= 0) {
            printf("\nYou're out of money! Adding 100 to your balance.\n");
            balance = 100;
        }

    } while (menuChoice != 5);

    return 0;
}

void playFootballGame(int *balance) {
    char gameChoice[2];
    
    do {
        int betChoice; 
        int betAmount;
        char* teams[] = {"Randers FC", "AGF", "Brondby", "Aalborg"};
        int team1Index = rand() % 4;
        int team2Index = rand() % 4;

        while (team1Index == team2Index) {
            team2Index = rand() % 4;
        }

        char* playing[2] = {teams[team1Index], teams[team2Index]};

        printf("\nMatch: %s vs %s\n", playing[0], playing[1]);

        do {
            printf("Enter 1 to bet on %s or 2 to bet on %s: ", playing[0], playing[1]);
            scanf("%d", &betChoice);
        } while (betChoice != 1 && betChoice != 2);

        do {
            printf("How much do you bet? (Balance: %d) ", *balance);
            scanf("%d", &betAmount);

            if (betAmount > *balance) {
                printf("Invalid bet! You only have %d.\n", *balance);
            }
        } while (betAmount > *balance);

        *balance -= betAmount; 

        int team1Score = rand() % 5;
        int team2Score = rand() % 5;

        printf("\nFinal Score: %s %d - %d %s\n", playing[0], team1Score, team2Score, playing[1]);

        if (team1Score > team2Score) {
            printf("%s wins!\n", playing[0]);
            if (betChoice == 1) {
                *balance += betAmount * 2; 
                printf("You won %d! New balance: %d\n", betAmount * 2, *balance);
            } else {
                printf("You lost the bet!\n");
            }
        } else if (team1Score < team2Score) {
            printf("%s wins!\n", playing[1]);
            if (betChoice == 2) {
                *balance += betAmount * 2;
                printf("You won %d! New balance: %d\n", betAmount * 2, *balance);
            } else {
                printf("You lost the bet!\n");
            }
        } else {
            printf("It's a draw!\n");
            *balance += betAmount; 
            printf("Your bet is returned. New balance: %d\n", *balance);
        }

        if (*balance <= 0) {
            printf("You're out of money!\n");
            return;
        }

        printf("Play again? (Y/N): ");
        scanf("%s", gameChoice);

    } while (strcmp(gameChoice, "Y") == 0 || strcmp(gameChoice, "y") == 0);
}

void playSlotMachine(int *balance) {
    char gameChoice[2];
    int betAmount;
    
    do {
        printf("\n===== Slot Machine =====\n");
        printf("Current Balance: %d\n", *balance);
        
        do {
            printf("Enter bet amount (0 to quit): ");
            scanf("%d", &betAmount);
            
            if (betAmount == 0) return;
            if (betAmount > *balance) {
                printf("You don't have enough money! Your balance: %d\n", *balance);
            }
        } while (betAmount > *balance || betAmount < 0);
        
        *balance -= betAmount;
        
        printf("Press Enter to spin...");
        getchar(); // Clear input buffer
        getchar(); // Wait for Enter
        
        int reelResults[3];
        spinWheel(0, 9, reelResults);
        
        int winMultiplier = checkSlotWin(reelResults[0], reelResults[1], reelResults[2]);
        int winnings = betAmount * winMultiplier;
        *balance += winnings;
        
        printf("\r");  // Clear the animation line
        if (winMultiplier == 10) {
            printf("\033[1;33mJACKPOT! %dX WIN! (%d %d %d) You won %d!\033[0m\n", 
                   winMultiplier, reelResults[0], reelResults[1], reelResults[2], winnings);
        } 
        else if (winMultiplier == 2) {
            printf("\033[1;32mWINNER! %dX WIN! (%d %d %d) You won %d!\033[0m\n", 
                   winMultiplier, reelResults[0], reelResults[1], reelResults[2], winnings);
        } 
        else {
            printf("No win this time... (%d %d %d)\n", 
                   reelResults[0], reelResults[1], reelResults[2]);
        }
        
        printf("New balance: %d\n", *balance);
        
        if (*balance <= 0) {
            printf("You're out of money!\n");
            return;
        }
        
        printf("Play again? (Y/N): ");
        scanf("%s", gameChoice);
        
    } while (strcmp(gameChoice, "Y") == 0 || strcmp(gameChoice, "y") == 0);
}

int checkSlotWin(int a, int b, int c) {
    if (a == b && b == c) return 10;
    if (a == b || b == c || a == c) return 2;
    return 0;
}

void spinWheel(int min, int max, int results[3]) {
    char colors[][8] = {"\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m", "\033[0;35m", "\033[0;36m"};
    int final_numbers[3];
    
    // Determine final numbers
    for(int i = 0; i < 3; i++) {
        final_numbers[i] = rand() % (max - min + 1) + min;
        results[i] = final_numbers[i];
    }

    // Animation sequence
    for(int frames = 0; frames < 15; frames++) {
        for(int reel = 0; reel < 3; reel++) {
            int temp_num = (final_numbers[reel] + frames) % 10;
            int color_idx = rand() % 6;
            printf("%s%d \033[0m", colors[color_idx], temp_num);
        }
        printf("\r");
        fflush(stdout);
        Sleep(50 + frames * 20);
    }
    
    // Display final numbers with consistent colors
    for(int reel = 0; reel < 3; reel++) {
        int color_idx = rand() % 6;
        printf("%s%d \033[0m", colors[color_idx], final_numbers[reel]);
    }
}

void addBalance(int *balance) {
    int amount;
    printf("\nEnter amount to add: ");
    scanf("%d", &amount);
    *balance += amount;
    printf("New balance: %d\n", *balance);
}

void showLeaderboard() {
    printf("\n===== Leaderboard =====\n");
    printf("Feature coming soon!\n");
}

void playBaccarat(int *balance) {
    char gameChoice[2];
    
    do {
        // Card utilities
        typedef struct {
            int value;  // 1-13
            char suit;  // 'H','D','C','S'
        } Card;

        Card drawCard() {
            Card newCard;
            newCard.value = rand() % 13 + 1;
            char suits[] = {'H', 'D', 'C', 'S'};
            newCard.suit = suits[rand() % 4];
            return newCard;
        }

        void printCard(Card c) {
            char *faceValues = "A23456789TJQK";
            printf("[%c%c]", faceValues[c.value-1], c.suit);
        }

        int calculateHandValue(Card hand[], int count) {
            int total = 0;
            for(int i = 0; i < count; i++) {
                total += (hand[i].value > 9) ? 0 : hand[i].value;
            }
            return total % 10;
        }

        printf("\n===== Baccarat =====\n");
        printf("Current Balance: $%d\n", *balance);
        
        int betAmount, betChoice;
        Card playerHand[3], bankerHand[3];
        int playerCardCount = 2, bankerCardCount = 2;
        
        // Get bet
        do {
            printf("Bet on:\n1. Player (1:1)\n2. Banker (0.95:1)\n3. Tie (8:1)\nChoice: ");
            scanf("%d", &betChoice);
        } while(betChoice < 1 || betChoice > 3);

        do {
            printf("Bet amount (0 to quit): ");
            scanf("%d", &betAmount);
            if(betAmount == 0) return;
        } while(betAmount > *balance);

        *balance -= betAmount;

        // Deal cards
        playerHand[0] = drawCard();
        playerHand[1] = drawCard();
        bankerHand[0] = drawCard();
        bankerHand[1] = drawCard();

        // Third card rules
        int playerTotal = calculateHandValue(playerHand, playerCardCount);
        if(playerTotal <= 5) {
            playerHand[playerCardCount++] = drawCard();
            playerTotal = calculateHandValue(playerHand, playerCardCount);
        }

        int bankerTotal = calculateHandValue(bankerHand, bankerCardCount);
        if((bankerTotal <= 2) ||
           (bankerTotal == 3 && playerCardCount == 3 && playerHand[2].value != 8) ||
           (bankerTotal == 4 && playerCardCount == 3 && playerHand[2].value >= 2 && playerHand[2].value <= 7) ||
           (bankerTotal == 5 && playerCardCount == 3 && playerHand[2].value >= 4 && playerHand[2].value <= 7) ||
           (bankerTotal == 6 && playerCardCount == 3 && (playerHand[2].value == 6 || playerHand[2].value == 7))) {
            bankerHand[bankerCardCount++] = drawCard();
            bankerTotal = calculateHandValue(bankerHand, bankerCardCount);
        }

        // Display results
        printf("\nPlayer: ");
        for(int i = 0; i < playerCardCount; i++) printCard(playerHand[i]);
        printf(" = %d\n", playerTotal);

        printf("Banker: ");
        for(int i = 0; i < bankerCardCount; i++) printCard(bankerHand[i]);
        printf(" = %d\n", bankerTotal);

        // Determine payout
        int payout = 0;
        if(playerTotal > bankerTotal && betChoice == 1) {
            payout = betAmount * 2;
            printf("\033[1;32mPlayer wins! You win $%d\033[0m\n", betAmount);
        } 
        else if(bankerTotal > playerTotal && betChoice == 2) {
            payout = betAmount + (int)(betAmount * 0.95);
            printf("\033[1;32mBanker wins! You win $%d\033[0m\n", (int)(betAmount * 0.95));
        } 
        else if(playerTotal == bankerTotal && betChoice == 3) {
            payout = betAmount * 9;
            printf("\033[1;33mTie! You win $%d\033[0m\n", betAmount * 8);
        }
        else {
            printf("\033[1;31mYou lost.\033[0m\n");
        }

        *balance += payout;
        printf("New balance: $%d\n", *balance);
        
        if (*balance <= 0) {
            printf("You're out of money!\n");
            return;
        }

        printf("Play again? (Y/N): ");
        scanf("%s", gameChoice);

    } while (strcmp(gameChoice, "Y") == 0 || strcmp(gameChoice, "y") == 0);
}