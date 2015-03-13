#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "game.h"

/*----------------------------------------
------------------------------------------
-------------STARTING THE GAME------------
------------------------------------------
----------------------------------------*/


void start_game() {
    int** grid_data; // Will be used as a 2D grid to store the position of the tetrominoes.
    GridSize grid_size;

    SDL_Surface *window = NULL;
    WindowSize window_size;

    SDL_Event event;

    grid_size.x = 10;
    grid_size.y = 20;
    initialize_grid_data(&grid_data, grid_size);
    fill_grid_with_zeros(grid_data, grid_size);

    window_size.width = window_size.height = 408;
    window = SDL_SetVideoMode(window_size.width, window_size.height, 32,
                              SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Tetris : Play", NULL);
    // Filling the window with white.
    SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 255, 255, 255));

    printf("grid_size x : %d\n", grid_size.x);
    printf("grid_size y : %d\n", grid_size.y);
    browse_grid_and_draw(grid_data, grid_size, window, window_size);

    while (1) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                free_grid_mallocs(grid_data, grid_size);
                free_sdl_surfaces(window);
                return;
        }
    }
}


/*----------------------------------------
------------------------------------------
-------------------GRID-------------------
------------------------------------------
----------------------------------------*/


/*------------------------------
-------MAKE A NEW GRID DATA-----
------------------------------*/

void initialize_grid_data(int*** grid_data, GridSize grid_size) {
    int i;

    *grid_data = (int**)malloc(grid_size.x * sizeof(int*)); // Allocates the first dimension.

    for(i = 0; i < grid_size.x; i++) {
        (*grid_data)[i] = (int*)malloc(grid_size.y * sizeof(int)); // Allocates the second dimension.
    }
}

/*------------------------------
----FILL GRID DATA WITH ZEROS---
------------------------------*/

void fill_grid_with_zeros(int** grid_data, GridSize grid_size) {
    int y, x;

    for (y = 0; y < grid_size.y; y++) {
        for (x = 0; x < grid_size.x; x++) {
            grid_data[x][y] = 0;
        }
    }
}

/*------------------------------
------BROWSE GRID AND DRAW------
------------------------------*/

// Browse the grid data and draw a square when there is a 1.
void browse_grid_and_draw(int** grid_data, GridSize grid_size, SDL_Surface* window,
                          WindowSize window_size) {
    int y, x;

    SDL_Rect position_to_blit;

    for (y = 0; y < grid_size.y; y++) {
        for (x = 0; x < grid_size.x; x++) {
            if (grid_data[x][y] == 1) {
                position_to_blit.x = x * (window_size.width / grid_size.x);
                position_to_blit.y = y * (window_size.height / grid_size.y);
                draw_tetromino_square(window, position_to_blit, window_size, grid_size);
            }
        }
    }
}

/*------------------------------
--------FREE GRID MALLOCS-------
------------------------------*/

void free_grid_mallocs(int** grid_data, GridSize grid_size) {
    int i;

    for (i = 0; i < grid_size.x; i++) { // Freeing 2nd dimension.
        free(grid_data[i]);
    }

    free(grid_data); // Freeing 1st dimension.
}


/*----------------------------------------
------------------------------------------
---------------SDL SURFACES---------------
------------------------------------------
----------------------------------------*/


/*------------------------------
-------DRAW TETROMINO SQUARE----
------------------------------*/

void draw_tetromino_square(SDL_Surface* window, SDL_Rect position_to_blit,
                           WindowSize window_size, GridSize grid_size) {
    SDL_Surface* tetromino_square = NULL;
    int tetromino_square_width, tetromino_square_height;
    tetromino_square_width = window_size.width / grid_size.x;
    tetromino_square_height = window_size.height / grid_size.y;
    tetromino_square = SDL_CreateRGBSurface(SDL_HWSURFACE, tetromino_square_width,
                                            tetromino_square_height, 32, 0, 0, 0, 0);
    SDL_FillRect(tetromino_square, NULL, SDL_MapRGB(tetromino_square->format, 0, 0, 0));

    SDL_BlitSurface(tetromino_square, NULL, window, &position_to_blit);
    SDL_Flip(window);

    SDL_FreeSurface(tetromino_square); // To avoid memory leak;
}

/*------------------------------
---------FREE SDL SURFACES------
------------------------------*/

void free_sdl_surfaces(SDL_Surface* window) {
    SDL_FreeSurface(window);
}


/*----------------------------------------
------------------------------------------
----------PICKING A RANDOM NUMBER---------
------------------------------------------
----------------------------------------*/


int pick_random_form() {
    return (rand() % 7); // Pick a random number from 0 to 6 (there are 7 tetris forms).
}
