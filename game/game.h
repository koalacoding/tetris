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

void initialize_grid_data(int*** grid_data, GridSize grid_size);

/*------------------------------
----FILL GRID DATA WITH ZEROS---
------------------------------*/

void fill_grid_with_zeros(int** grid_data, GridSize grid_size);

/*------------------------------
------BROWSE GRID AND DRAW------
------------------------------*/

// Browse the grid data and draw a square when there is a 1.
void browse_grid_and_draw(int** grid_data, GridSize grid_size, SDL_Surface* window,
                          WindowSize window_size);

/*------------------------------
--------FREE GRID MALLOCS-------
------------------------------*/

void free_grid_mallocs(int** grid_data, GridSize grid_size);


/*----------------------------------------
------------------------------------------
---------------SDL SURFACES---------------
------------------------------------------
----------------------------------------*/


/*------------------------------
-------DRAW TETROMINO SQUARE----
------------------------------*/

void draw_tetromino_square(SDL_Surface* window, SDL_Rect position_to_blit,
                           WindowSize window_size, GridSize grid_size);

/*------------------------------
---------FREE SDL SURFACES------
------------------------------*/

void free_sdl_surfaces(SDL_Surface* window);


/*----------------------------------------
------------------------------------------
----------PICKING A RANDOM NUMBER---------
------------------------------------------
----------------------------------------*/


int pick_random_form();

#endif
