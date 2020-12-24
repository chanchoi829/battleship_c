#include "Game.h"
#include "Utility.h"
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Restart the battleship game
int restart(void);

int main(void) {
    // Set the seed for rand()
    srand(time(NULL));

    while (1) {

        struct Game* game_ptr = start();
        printf("***************************\nGame Start!");

        while (1) {
            player_turn(game_ptr);
            if (get_computer_sunk(game_ptr) == NUM_SHIPS) {
                printf("You Win!\n");
                break;
            }

            computer_turn(game_ptr);
            if (get_player_sunk(game_ptr) == NUM_SHIPS) {
                printf("You lose!\n");
                break;
            }
        }

        end(game_ptr);

        if (!restart()) {
            printf("Done\n");
            return 0;
        }
    }

    return 0;
}

// Check if the player wants to restart
int restart(void) {
    while (1) {
        printf("Restart?\nType yes or no\n");

        char answer[MAX_ANSWER + 1];
        scanf(MAX_ANSWER_STR, answer);

        // Convert to lower case
        size_t a;
        for (a = 0; a < MAX_ANSWER + 1; ++a)
            answer[a] = tolower(answer[a]);

        if (strncmp(answer, "yes", 3) == 0)
            return 1;
        else if (strncmp(answer, "no", 2) == 0)
            return 0;
        else {
            // Print an error message and skip rest of the line
            printf("Invalid answer!\n");
            while (getchar() != '\n');

            continue;
        }
    }

    return 0;
}
