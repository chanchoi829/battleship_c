#include "Game.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Restart the battleship game
int restart(void);

int main(void) {
    // Set the seed for rand()
    srand(time(NULL));
    
    while (1) {

        struct Game* game_ptr = start();

        printf("***************************\nGame Start!");

        end(game_ptr);

        if (!restart())
            return 0;
    }

    return 0;
}

int restart(void) {
    return 0;
}
