#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#include <stdbool.h>
int generatematches() {
    return rand() % 4; 
}

int main() { 
    char gameChoice[2];
    int balance = 100;
    do{
    int betChoice; 
    int betamount;
    
    char* teams[] = {"randers fc", "agf", "bronby", "aalborg"};
    
    srand(time(0)); 
    int team1Index = generatematches();
    int team2Index = generatematches();

    while (team1Index == team2Index) {
        team2Index = generatematches();
    }

    char* playing[2] = {teams[team1Index], teams[team2Index]};

    printf("Match: %s vs %s\n", playing[0], playing[1]);

    do {
        printf("Enter 1 to bet on %s or 2 to bet on %s: ", playing[0], playing[1]);
        scanf("%d", &betChoice);
    } while (betChoice != 1 && betChoice != 2);

    do {
        printf("How much do you bet? ");
        scanf("%d", &betamount);

        if (betamount > balance) {
            printf("Invalid bet! You only have %d.\n", balance);
        }
    } while (betamount > balance);

    balance -= betamount; 

    int team1Score = rand() % 5;
    int team2Score = rand() % 5;

    printf("Final Score: %s %d - %d %s\n", playing[0], team1Score, team2Score, playing[1]);

    if (team1Score > team2Score) {
        printf("%s wins!\n", playing[0]);

        if (betChoice == 1) {
            balance += betamount * 2; 
            printf("You won the bet!\n");
        } else {
            printf("You lost the bet!\n");
        }
    } else if (team1Score < team2Score) {
        printf("%s wins!\n", playing[1]);

        if (betChoice == 2) {
            balance += betamount * 2;
            printf("You won the bet!\n");
        } else {
            printf("You lost the bet!\n");
        }
    } else {
        printf("It's a draw!\n");
        balance += betamount; 
    }

    printf("Your new balance is: %d\n", balance);
    printf("play again Y/N ");
    scanf("%s", gameChoice);
    } while (strcmp(gameChoice, "Y") == 0 || strcmp(gameChoice, "y") == 0);

    return 0;
}
