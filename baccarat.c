
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

int calculateHandValue(Card hand[], int count) {
    int total = 0;

    for(int i = 0; i < count; i++){
        total += (hand[i].value > 9) ? 0 : hand[i].value;
    }

    // Only last digit counts in Baccarat
    return total % 10;
}

void determineWinner(Card playerHand[], int playerCount, Card bankerHand[], int bankerCount) {
    int playerTotal = calculateHandValue(playerHand, playerCount);
    int bankerTotal = calculateHandValue(bankerHand, bankerCount);

    printf("\nplayer's hand");
    for(int i = 0; i < playerCount; i++) printCard(playerHand[i]);
    printf(" = %d\n", playerTotal);

    printf("\nbanker's hand");
    for(int i = 0; i < bankerCount; i++) printCard(bankerHand[i]);
    printf(" = %d\n", bankerTotal);

    if(playerTotal > bankerTotal){
        printf("player wins\n");
    } else if(bankerTotal > playerTotal){
        printf("banker wins\n");
    } else{
        printf(" its a tie\n");
    }
}


int main(){
    
    //seed so we get diffrent results
    srand(time(NULL));

    int baccaratBetChoice;
    printf("who do you want to bet on:\n");
    printf("    1. player\n");
    printf("    2. dealer\n");
    printf("    3. tie\n");
    scanf( "%d",&baccaratBetChoice );

    //deal the cards
    Card playerHand[3];  // Max 3 cards
    Card bankerHand[3];  // Max 3 cards

    playerHand[0] = drawCard();
    playerHand[1] = drawCard();
    bankerHand[0] = drawCard();
    bankerHand[1] = drawCard();
    
    int playerCardCount = 2;
    int bankerCardCount = 2;

    //baccarat 3rd card rule
    int playerTotal = calculateHandValue(playerHand, playerCardCount);
    int bankerTotal = calculateHandValue(bankerHand, bankerCardCount);

    //player draw rules
    if(playerTotal < 5){
        playerHand[playerCardCount++] = drawCard();
        playerTotal = calculateHandValue(playerHand, playerCardCount);
    }

  // Banker draw rules
    if(bankerTotal <= 2 || 
       (bankerTotal == 3 && playerCardCount == 3 && playerHand[2].value != 8) ||
       (bankerTotal == 4 && playerCardCount == 3 && playerHand[2].value >= 2 && playerHand[2].value <= 7) ||
       (bankerTotal == 5 && playerCardCount == 3 && playerHand[2].value >= 4 && playerHand[2].value <= 7) ||
       (bankerTotal == 6 && playerCardCount == 3 && (playerHand[2].value == 6 || playerHand[2].value == 7))) {
        bankerHand[bankerCardCount++] = drawCard();
        bankerTotal = calculateHandValue(bankerHand, bankerCardCount);
    }
    determineWinner(playerHand, playerCardCount, bankerHand, bankerCardCount);

    return 0;
}
