#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int checkWin(int a, int b, int c) {
    if (a == b && b == c) return 10;
    if (a == b || b == c || a == c) return 2;
    return 0;
}

void spinWheel(int min, int max,int results[3]) {
    char colors[][8] = {"\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m", "\033[0;35m", "\033[0;36m"}; //ANSI Colors
    int final_numbers[3];
    // Determine final numbers first
    for(int i = 0; i < 3; i++) {
        final_numbers[i] = rand() % (max - min + 1) + min;
    }

    for(int i = 0; i < 3; i++) {
        results[i] = final_numbers[i];  
    }

    // Animate each reel with different speeds
    for(int frames = 0; frames < 15; frames++) {
        for(int reel = 0; reel < 3; reel++) {
            int temp_num = (final_numbers[reel] + frames) % 10;
            int color_idx = rand() % 6;
            printf("%s%d \033[0m", colors[color_idx], temp_num);
        }
        printf("\r");
        Sleep(50 + frames * 20); // Increasing delay
        
    }
}

int main() {
    srand(time(NULL));
    
    printf("Press Enter to spin the slot machine...");
    getchar();  // Wait for user input
    
    int reelResults[3];
    spinWheel(0, 9, reelResults);
    
    int winMultiplier = checkWin(reelResults[0], reelResults[1], reelResults[2]);
    
    printf("\r");  // Clear the animation line
    if (winMultiplier == 10) {
        printf("\033[1;33mJACKPOT! %dX WIN! (%d %d %d)\033[0m\n", 
               winMultiplier, reelResults[0], reelResults[1], reelResults[2]);
    } 
    else if (winMultiplier == 2) {
        printf("\033[1;32mWINNER! %dX WIN! (%d %d %d)\033[0m\n", 
               winMultiplier, reelResults[0], reelResults[1], reelResults[2]);
    } 
    else {
        printf("No win this time... (%d %d %d)\n", 
               reelResults[0], reelResults[1], reelResults[2]);
    }
    
    return 0;
}
