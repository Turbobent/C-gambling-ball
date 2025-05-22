#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void spinWheel(int min, int max) {
    char colors[][8] = {"\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m", "\033[0;35m", "\033[0;36m"}; //ANSI Colors
    
    for (int i = 0; i < 3; i++) {
        int color_index = rand() % 6; // Pick random color

        int num = rand() % (max - min + 1) + min;
        printf("%s%d \033[0m", colors[color_index], num);
        Sleep(100 * (i+1));
    }
     printf("\033[0;32m \n");
}

int main() {
    srand(time(NULL));

    printf("Press Enter to spin...");
    getchar();

     for(int i = 0; i < 3; i++) {
        spinWheel(0, 9);
    }

      return 0;
}
