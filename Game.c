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
    place_computer_ship(game_ptr, "Destroyer");
    place_computer_ship(game_ptr, "Submarine");
    place_computer_ship(game_ptr, "Cruiser");
    place_computer_ship(game_ptr, "Battleship");
    place_computer_ship(game_ptr, "Carrier");

    // Create player's grid
    place_player_ship(game_ptr, "Destroyer");
    place_player_ship(game_ptr, "Submarine");
    place_player_ship(game_ptr, "Cruiser");
    place_player_ship(game_ptr, "Battleship");
    place_player_ship(game_ptr, "Carrier");

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
void place_computer_ship(struct Game* game_ptr, const char* ship) {
    int ship_length;
    char ship_letter;

    check_ship_type(ship, &ship_length, &ship_letter);

    // Direction: left, up, right, down
    int* positions = &ship_length;
    int directions[DIRECTIONS] = { -1, -10, 1, 10 };

    // Generate random positions until the ship fits
    while (!is_valid(&positions, game_ptr->computer_grid, rand() % 100,
        directions[rand() % DIRECTIONS], ship_length)){}

    int which_ship;
    char* ship_name = "";
    convert_char_to_ship(ship_letter, &ship_name, &which_ship);
    free(ship_name);

    // Set ship's hp
    game_ptr->computer_ships[which_ship][0] = 0;
    game_ptr->computer_ships[which_ship][1] = ship_length;

    // Place the ship
    int i;
    for (i = 0; i < ship_length; ++i)
        game_ptr->computer_grid[positions[i] / GRID_SIZE][positions[i] % GRID_SIZE] = ship_letter;

    free(positions);
}

// Place player's ship
void place_player_ship(struct Game* game_ptr, const char* ship) {
    int ship_length;
    char ship_letter;

    check_ship_type(ship, &ship_length, &ship_letter);

    while (1) {
        draw_player_grid();
        printf("\nExample: G5\nPlace your %s (length %d ): ", ship, ship_length);

        char* position = "";
        if (!read_position(&position)) {
            continue;
        }
    }
}

// Check the ship's type
void check_ship_type(const char* ship, int* ship_length, char* ship_letter) {
	if (strcmp(ship, "Destroyer") == 0) {
        *ship_length = 2;
        *ship_letter = 'd';
    }
    else if (strcmp(ship, "Submarine") == 0) {
        *ship_length = 3;
        *ship_letter = 's';
    }
    else if (strcmp(ship, "Cruiser") == 0){ 
        *ship_length = 3;
        *ship_letter = 'c';
    }
    else if (strcmp(ship, "Battleship")) {
        *ship_length = 4;
        *ship_letter = 'b';
    }
    else {
        *ship_length = 5;
        *ship_letter = 'C';
    }  
}

// Check if the given ship can fit
int is_valid(int** positions, char (*grid)[10],
    int position, int direction, int ship_length) {
    *positions = malloc(sizeof(int) * ship_length);

	// Check if the ship fits
    int ship_fits = 1, ship_index = 0, i;

    for (i = 0; i < ship_length; ++i) {
        int row = position / GRID_SIZE, col = position % GRID_SIZE;

        // Check if the position is in range and if the ship can fit
        if (position < 0 || position > 99 || (position % GRID_SIZE == 0 && direction == -1) ||
            (position % GRID_SIZE == 9 && direction == 1)
            || grid[row][col] != '.') {
            ship_fits = 0;
            free(*positions);
            break;
        }

        (*positions)[ship_index++] = position;
        position += direction;
    }

    return ship_fits;
}

// Get user's input and check if it is valid
int read_position(char** position) {
    char position_[MAX_POINT + 1];
    position_[MAX_POINT] = '!';
    scanf(POINT_STR, position_);

    // Conver to lower case
    size_t a;
    for (a = 0; a < MAX_DIFFICULTY + 1; ++a)
        position_[a] = tolower(position_[a]);

    // Check the input
    if (position_[0] < 'a' || position_[0] > 'j') {
        printf("Enter a valid answer!\n");
        return 0;
    }

    if (position_[MAX_POINT] == '!' && (position_[1] < '1' || position_[1] > '9')) {
        printf("Enter a valid answer!\n");
        return 0;
    }

    if (position_[MAX_POINT] != '!' && (position_[1] != '1' || position_[2] != '0')) {
        printf("Enter a valid answer!\n");
        return 0;
    }

    // Length 2
    if (position_[MAX_POINT] == '!') {
        *position = malloc(MAX_POINT);
        strcpy(*position, position_);
    }
    // Length 3
    else {
        *position = malloc(MAX_POINT + 1);
        strcpy(*position, position_);
    }

    return 1;
}

// Convert a char to a ship name
void convert_char_to_ship(char ship_char, char** ship, int* which_ship) {
    if (ship_char == 'd') {
        *which_ship = 0;
        *ship = malloc(DESTROYER_STR + 1);
        strcpy(*ship, "Destroyer");
    }
    else if (ship_char == 's') {
        *which_ship = 1;
        *ship = malloc(SUBMARINE_STR + 1);
        strcpy(*ship, "Submarine");
    }
    else if (ship_char == 'c') {
        *which_ship = 2;
        *ship = malloc(CRUISER_STR + 1);
        strcpy(*ship, "Cruiser");
    }
    else if (ship_char == 'b') {
        *which_ship = 3;
        *ship = malloc(BATTLESHIP_STR + 1);
        strcpy(*ship, "Battleship");
    }
    else {
        *which_ship = 4;
        *ship = malloc(CARRIER_STR + 1);
        strcpy(*ship, "Carrier");
    }
}
