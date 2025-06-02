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
int checkWin(int a, int b, int c);
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
        printf("3. Add Money\n");
        printf("4. View Leaderboard\n");
        printf("5. Quit\n");
        printf("Current Balance: %d\n", balance);
        printf("Enter your choice: ");
        scanf("%d", &menuChoice);

        switch (menuChoice) {
            case 1:
                playFootballGame(&balance);
                break;
            case 2:
                playSlotMachine(&balance);
                break;
            case 3:
                addBalance(&balance);
                break;
            case 4:
                showLeaderboard();
                break;
            case 5:
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
        
        int winMultiplier = checkWin(reelResults[0], reelResults[1], reelResults[2]);
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

int checkWin(int a, int b, int c) {
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