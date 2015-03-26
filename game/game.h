#ifndef game
#define game

#include "../structures/structures.h"

/*----------------------------------------
------------------------------------------
-------------STARTING THE GAME------------
------------------------------------------
----------------------------------------*/


void start_game();


/*----------------------------------------
------------------------------------------
-------------------GRID-------------------
------------------------------------------
----------------------------------------*/

/*------------------------------
-------MAKE A NEW GRID DATA-----
------------------------------*/

void initialize_grid(int*** grid_data, Grid grid);

/*------------------------------
----FILL GRID DATA WITH ZEROS---
------------------------------*/

void fill_grid_with_zeros(Grid grid);

/*------------------------------
------BROWSE GRID AND DRAW------
------------------------------*/

// Browse the grid data and draw a square when there is a 1.
void draw_grid(Grid grid, SDL_Surface* window, WindowSize window_size);

/*------------------------------
--------FREE GRID MALLOCS-------
------------------------------*/

void free_grid_mallocs(Grid grid);


/*----------------------------------------
------------------------------------------
---------------SDL SURFACES---------------
------------------------------------------
----------------------------------------*/


/*------------------------------
-------DRAW TETROMINO SQUARE----
------------------------------*/

void draw_tetromino_square(SDL_Surface* window, SDL_Rect position_to_blit, WindowSize window_size,
                           Grid grid);

/*------------------------------
-DRAW TETROMINO SQUARE BORDERS--
------------------------------*/

void draw_tetromino_square_borders(SDL_Surface* border, int border_width, int border_height,
                                   SDL_Rect position_to_blit, int x_space, int y_space,
                                   SDL_Surface* window);

/*------------------------------
---------DRAW BLANK SQUARE------
------------------------------*/

void draw_blank_square(SDL_Surface* window, SDL_Rect position_to_blit, WindowSize window_size,
                       Grid grid);

/*------------------------------
---------FREE SDL SURFACES------
------------------------------*/

void free_sdl_surfaces(SDL_Surface* window);


/*----------------------------------------
------------------------------------------
----------------TETROMINOES---------------
------------------------------------------
----------------------------------------*/


/*------------------------------
------GENERATE NEW TETROMINO----
------------------------------*/

void generate_new_tetromino(int form, Grid grid);

/*------------------------------
-------MAKE TETROMINO FALL------
------------------------------*/

void make_tetromino_fall(Grid grid);

/*------------------------------
-------MOVE TETROMINO RIGHT-----
------------------------------*/

void move_tetromino_right(Grid grid);

/*------------------------------
-------MOVE TETROMINO LEFT------
------------------------------*/

void move_tetromino_left(Grid grid);

#endif
