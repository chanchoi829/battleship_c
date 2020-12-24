#ifndef GAME_H
#define GAME_H

/*
Game
*/

struct Game;

// Reset variables like grids and returns a Game pointer
struct Game* start(void);

// Free memory
void end(struct Game* game_ptr);

// Simulate computer's turn
void computer_turn(void);

// Simulate player's turn
void player_turn(void);

// Draw computer's grid
void draw_computer_grid(void);

// Draw player's grid
void draw_player_grid(void);

// Helper functions
// Place computer's ship
void place_computer_ship(const char* ship);

// Place player's ship
void place_player_ship(const char* ship);

// Check the ship's type
void check_ship_type(const char* ship, int* ship_length, char* ship_letter);

// Check if the given ship can fit
int is_valid(int* positions, const char** grid,
    int position, int direction, int ship_length);

// Get user's input and check if it is valid
void read_position(char* position);

// Convert a char to a ship name
void convert_char_to_ship(char ship_char, char* ship, int* which_ship);

#endif
