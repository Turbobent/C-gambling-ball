#include <stdio.h>
#include <stdlib.h>  
#include <time.h>

typedef struct {
    int value;  // 0 - 36
} RouletteNumber;

RouletteNumber winningNumber(){
    RouletteNumber rn;

    // 0-37 (37 represents 00)
    int num = rand() % 37;  

    if(num == 37){
        rn.value = -1;
    } else{
        rn.value = num;
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
        printf("%2d", rn.value);  
    }
}


int main(){
    srand(time(NULL));
    char* betChoice;

    printf("what color or number do you want to bet on\n");
    scanf("%s", &betChoice);

    RouletteNumber winner = winningNumber();
    printf("\nwinnging number: ");
    printResult(winner);

    return 0;

}