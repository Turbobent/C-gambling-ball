#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void addBalance(int *balance);
void showLeaderboard();

int main() { 
    char gameChoice[2];
    int balance = 100;

    srand(time(0)); 
    
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
            printf("How much do you bet? (Balance: %d) ", balance);
            scanf("%d", &betAmount);

            if (betAmount > balance) {
                printf("Invalid bet! You only have %d.\n", balance);
            }
        } while (betAmount > balance);

        balance -= betAmount; 

        int team1Score = rand() % 5;
        int team2Score = rand() % 5;

        printf("\nFinal Score: %s %d - %d %s\n", playing[0], team1Score, team2Score, playing[1]);

        if (team1Score > team2Score) {
            printf("%s wins!\n", playing[0]);
            if (betChoice == 1) {
                balance += betAmount * 2; 
                printf("You won the bet!\n");
            } else {
                printf("You lost the bet!\n");
            }
        } else if (team1Score < team2Score) {
            printf("%s wins!\n", playing[1]);
            if (betChoice == 2) {
                balance += betAmount * 2;
                printf("You won the bet!\n");
            } else {
                printf("You lost the bet!\n");
            }
        } else {
            printf("It's a draw!\n");
            balance += betAmount; 
        }

        do {
            printf("Play again? (Y/N/M for menu): ");
            scanf("%s", gameChoice);

            if (strcmp(gameChoice, "M") == 0 || strcmp(gameChoice, "m") == 0) {
                int menuChoice;
                do {
                    printf("\n===== Menu =====\n");
                    printf("1. Add Money\n");
                    printf("2. View Leaderboard\n");
                    printf("3. Play Game\n");
                    printf("4. Quit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &menuChoice);

                    switch (menuChoice) {
                        case 1:
                            addBalance(&balance);
                            break;
                        case 2:
                            showLeaderboard();
                            break;
                        case 3:
                            strcpy(gameChoice, "Y"); // Restart the game
                            break;
                        case 4:
                            printf("Goodbye!\n");
                            return 0;
                        default:
                            printf("Invalid choice! Try again.\n");
                    }
                } while (menuChoice != 3 && menuChoice != 4);
            }

        } while (strcmp(gameChoice, "Y") != 0 && strcmp(gameChoice, "y") != 0 && 
                 strcmp(gameChoice, "N") != 0 && strcmp(gameChoice, "n") != 0);

    } while (strcmp(gameChoice, "Y") == 0 || strcmp(gameChoice, "y") == 0);

    return 0;
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
