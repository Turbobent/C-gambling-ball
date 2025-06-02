#pragma once

void playBaccarat();  // Main game function

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

int calculateHandValue(Card hand[], int count);