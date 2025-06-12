#include <stdio.h>
#include <stdlib.h>  
#include <time.h>

typedef struct {
    int value;  // 0 - 36
    char color;
} RouletteNumber;

RouletteNumber winningNumber() {
    RouletteNumber rn;
    
    // 0-36 (regular numbers), 37 represents 00
    int num = rand() % 38;
    
    if (num == 37) {
        // Using -1 to represent 00
        rn.value = -1; 
        // 00 is green 
        rn.color = 'G'; 
    } else {
        rn.value = num;
        
        // Determine color for numbers 0-36
        if (num == 0) {
            // 0 is green
            rn.color = 'G';  
        } else {
            // List of all red numbers in roulette
            int reds[] = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
            int isRed = 0;
            
            // Check if the number is red
            for (int i = 0; i < sizeof(reds)/sizeof(reds[0]); i++) {
                if (num == reds[i]) {
                    isRed = 1;
                    break;
                }
            }
            
            rn.color = isRed ? 'R' : 'B';
        }
    }
    
    return rn;
}

void printResult(RouletteNumber rn) {
    // Display 00
    if (rn.value == -1) {
        printf("00");  
    } else if (rn.value == 0) {
        // Display single 0
        printf("0");  
    } else {
        // Display 1-36
        printf("%c %2d", rn.color, rn.value);
    }
}

int main(){
    srand(time(NULL));
    char betChoice[10];

    printf("Choose bet type:\n");
    printf("1. Specific number (pays 35:1)\n");
    printf("2. Red (pays 1:1)\n"); 
    printf("3. Black (pays 1:1)\n");
    printf("4. Green (0/00, pays 17:1)\n");
    scanf("%s", &betChoice);

    RouletteNumber winner = winningNumber();
    printf("\nwinnging number: ");
    printResult(winner);

    return 0;

}