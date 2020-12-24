#include "Game.h"
#include "Utility.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Game {
    char (*computer_grid)[GRID_SIZE], (*player_grid)[GRID_SIZE];
    int (*computer_ships)[2], (*player_ships)[2];
    int computer_sunk, player_sunk, row_prev, col_prev, easy;
};

// Reset variables like grids and returns a Game pointer
struct Game* start() {
    struct Game* game_ptr = (struct Game*) malloc(sizeof(struct Game));

    game_ptr->computer_grid = malloc(sizeof(*game_ptr->computer_grid) * GRID_SIZE);
	game_ptr->player_grid = malloc(sizeof(*game_ptr->player_grid) * GRID_SIZE);


    // Set initial values
    size_t i;
    for (i = 0; i < GRID_SIZE; ++i) {
        size_t j;
        for (j = 0; j < GRID_SIZE; ++j) {
            game_ptr->computer_grid[i][j] = '.';
            game_ptr->player_grid[i][j] = '.';
        }
    }

    game_ptr->computer_ships = malloc(sizeof(*game_ptr->computer_ships) * NUM_SHIPS);
	game_ptr->player_ships = malloc(sizeof(*game_ptr->player_ships) * NUM_SHIPS);

    game_ptr->computer_sunk = 0;
    game_ptr->player_sunk = 0;
    game_ptr->row_prev = 0;
    game_ptr->col_prev = 0;

    // Read in a difficulty
    while (1) {
        printf("Example: hard\nChoose difficulty easy/hard: ");

        char difficulty[MAX_DIFFICULTY + 1];
        scanf(MAX_DIFFICULTY_STR, difficulty);

        // Conver to lower case
        size_t a;
        for (a = 0; a < MAX_DIFFICULTY + 1; ++a)
            difficulty[a] = tolower(difficulty[a]);

        if (strcmp(difficulty, "easy") == 0) {
            game_ptr->easy = 1;
            break;
        }
        else if (strcmp(difficulty, "hard") == 0) {
            game_ptr->easy = 0;
            break;
        }
        else {
            printf("Enter a valid difficulty!\n");
        }
    }
    
    // Create computer's grid
    place_computer_ship("Destroyer");
    place_computer_ship("Submarine");
    place_computer_ship("Cruiser");
    place_computer_ship("Battleship");
    place_computer_ship("Carrier");

    // Create player's grid
    place_player_ship("Destroyer");
    place_player_ship("Submarine");
    place_player_ship("Cruiser");
    place_player_ship("Battleship");
    place_player_ship("Carrier");

    return game_ptr;
}

// Free memory
void end(struct Game* game_ptr) {
    free(game_ptr->computer_grid);
    free(game_ptr->player_grid);
    free(game_ptr);
}

// Simulate computer's turn
void computer_turn() {

}

// Simulate player's turn
void player_turn() {

}

// Draw computer's grid
void draw_computer_grid() {

}

// Draw player's grid
void draw_player_grid() {

}

// Helper functions
// Place computer's ship
void place_computer_ship(const char* ship) {

}

// Place player's ship
void place_player_ship(const char* ship) {

}

// Check the ship's type
void check_ship_type(const char* ship, int* ship_length, char* ship_letter) {

}

// Check if the given ship can fit
int is_valid(int* positions, const char** grid,
    int position, int direction, int ship_length) {
    return 1;
}

// Get user's input and check if it is valid
void read_position(char* position) {

}

// Convert a char to a ship name
void convert_char_to_ship(char ship_char, char* ship, int* which_ship) {

}
