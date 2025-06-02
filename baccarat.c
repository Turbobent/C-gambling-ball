
#include <stdio.h>
#include <stdlib.h>  
#include <time.h>

// Card utilities
typedef struct {
    int value;  // 1-13
    char suit;  // 'H','D','C','S'
} Card;

Card drawCard() {
    Card newCard;
    
    // Random value (1-13)
    newCard.value = rand() % 13 + 1;
    
    // Random suit
    char suits[] = {'H', 'D', 'C', 'S'};
    newCard.suit = suits[rand() % 4];
    
    return newCard;
}

void printCard(Card c) {
    char *faceValues = "A23456789TJQK"; // T=10, J=11, Q=12, K=13
    printf("[%c%c]", faceValues[c.value-1], c.suit);
}


void main(){
    int baccaratBetChoice;
    printf("who do you want to bet on:\n");
    printf("    1. player\n");
    printf("    2. dealer\n");
    printf("    3. tie\n");
    scanf( "%d",&baccaratBetChoice );

    Card playerHand[3];  // Max 3 cards
    Card bankerHand[3];  // Max 3 cards

    playerHand[0] = drawCard();
    playerHand[1] = drawCard();
    bankerHand[0] = drawCard();
    bankerHand[1] = drawCard();
    
    int playerCardCount = 2;
    int bankerCardCount = 2;
}