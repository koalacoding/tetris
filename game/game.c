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
    Grid grid;

    SDL_Surface *window = NULL;
    WindowSize window_size;

    int current_tetromino_pos[4][2];

    int time_actual;
    int time_last = SDL_GetTicks();

    SDL_Event event;

    grid.size_x = 10;
    grid.size_y = 20;
    initialize_grid(&grid.data, grid);
    fill_grid_with_zeros(grid);

    window_size.width = window_size.height = 408;
    window = SDL_SetVideoMode(window_size.width, window_size.height, 32,
                              SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Tetris : Play", NULL);
    // Filling the window with white.
    SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 255, 255, 255));

    current_tetromino_pos[0][0] = 4;
    current_tetromino_pos[0][1] = 0;

    current_tetromino_pos[1][0] = 5;
    current_tetromino_pos[1][1] = 0;

    current_tetromino_pos[2][0] = 6;
    current_tetromino_pos[2][1] = 0;

    current_tetromino_pos[3][0] = 7;
    current_tetromino_pos[3][1] = 0;

    while (1) {
        time_actual = SDL_GetTicks();

        if (time_actual - time_last > 300) { // If 1 second (1000ms) have passed.
            make_tetromino_fall(grid, current_tetromino_pos);
            draw_grid(grid, window, window_size);

            time_last = SDL_GetTicks(); // Refreshing the last time we made the tetrominoes fall.
        }

        else { SDL_Delay(30); }

        SDL_PollEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                free_grid_mallocs(grid);
                free_sdl_surfaces(window);
                return;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_DOWN:


                        break;
                }
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

void initialize_grid(int*** grid_data, Grid grid) {
    int i;
    *grid_data = (int**)malloc(grid.size_x * sizeof(int*)); // Allocates the first dimension.

    for (i = 0; i < grid.size_x; i++) {
        (*grid_data)[i] = (int*)malloc(grid.size_y * sizeof(int)); // Allocates the second dimension.
    }
}

/*------------------------------
----FILL GRID DATA WITH ZEROS---
------------------------------*/

void fill_grid_with_zeros(Grid grid) {
    int y, x;

    for (y = 0; y < grid.size_y; y++) {
        for (x = 0; x < grid.size_x; x++) {
            grid.data[x][y] = 0;
        }
    }
}

/*------------------------------
------BROWSE GRID AND DRAW------
------------------------------*/

// Browse the grid data and draw a square when there is a 1.
void draw_grid(Grid grid, SDL_Surface* window, WindowSize window_size) {
    int y, x;

    SDL_Rect position_to_blit;

    for (y = 0; y < grid.size_y; y++) {
        for (x = 0; x < grid.size_x; x++) {
            if (grid.data[x][y] == 0) {
                position_to_blit.x = x * (window_size.width / grid.size_x);
                position_to_blit.y = y * (window_size.height / grid.size_y);
                draw_blank_square(window, position_to_blit, window_size, grid);
            }

            if (grid.data[x][y] == 1) { // If the case is a tetromino square.
                position_to_blit.x = x * (window_size.width / grid.size_x);
                position_to_blit.y = y * (window_size.height / grid.size_y);
                draw_tetromino_square(window, position_to_blit, window_size, grid);
            }
        }
    }

    SDL_Flip(window);
}

/*------------------------------
--------FREE GRID MALLOCS-------
------------------------------*/

void free_grid_mallocs(Grid grid) {
    int i;

    for (i = 0; i < grid.size_x; i++) { // Freeing 2nd dimension.
        free(grid.data[i]);
    }

    free(grid.data); // Freeing 1st dimension.
}


/*----------------------------------------
------------------------------------------
---------------SDL SURFACES---------------
------------------------------------------
----------------------------------------*/


/*------------------------------
-------DRAW TETROMINO SQUARE----
------------------------------*/

void draw_tetromino_square(SDL_Surface* window, SDL_Rect position_to_blit, WindowSize window_size,
                           Grid grid) {
    SDL_Surface *tetromino_square = NULL, *border_top = NULL, *border_below = NULL,
                *border_right = NULL, *border_left = NULL;

    int tetromino_square_width, tetromino_square_height;
    // -1 because we are going to add a 1px border.
    tetromino_square_width = (window_size.width / grid.size_x) - 1;
    tetromino_square_height = (window_size.height / grid.size_y) - 1;
    tetromino_square = SDL_CreateRGBSurface(SDL_HWSURFACE, tetromino_square_width,
                                            tetromino_square_height, 32, 0, 0, 0, 0);
    SDL_FillRect(tetromino_square, NULL, SDL_MapRGB(tetromino_square->format, 255, 0, 0));
    SDL_BlitSurface(tetromino_square, NULL, window, &position_to_blit);

    draw_tetromino_square_borders(border_top, tetromino_square_width, 1, position_to_blit, 0, -1,
                                  window);
    draw_tetromino_square_borders(border_below, tetromino_square_width, 1, position_to_blit, 0,
                                  tetromino_square_height, window);
    draw_tetromino_square_borders(border_right, 1, tetromino_square_height, position_to_blit,
                                  tetromino_square_width, 0, window);
    draw_tetromino_square_borders(border_left, 1, tetromino_square_height, position_to_blit,
                                  0, 0, window);

    SDL_FreeSurface(tetromino_square); // To avoid memory leak;
}

/*------------------------------
-DRAW TETROMINO SQUARE BORDERS--
------------------------------*/

void draw_tetromino_square_borders(SDL_Surface* border, int border_width, int border_height,
                                   SDL_Rect position_to_blit, int x_space, int y_space,
                                   SDL_Surface* window) {
    border = SDL_CreateRGBSurface(SDL_HWSURFACE, border_width, border_height, 32, 0, 0, 0, 0);
    SDL_FillRect(border, NULL, SDL_MapRGB(border->format, 0, 0, 0));
    position_to_blit.x += x_space;
    position_to_blit.y += y_space;
    SDL_BlitSurface(border, NULL, window, &position_to_blit);

    SDL_FreeSurface(border);
}

/*------------------------------
---------DRAW BLANK SQUARE------
------------------------------*/

void draw_blank_square(SDL_Surface* window, SDL_Rect position_to_blit, WindowSize window_size,
                       Grid grid) {
    SDL_Surface* square = NULL;

    int square_width, square_height;
    square_width = window_size.width / grid.size_x;
    square_height = window_size.height / grid.size_y;
    square = SDL_CreateRGBSurface(SDL_HWSURFACE, square_width, square_height, 32, 0, 0, 0, 0);
    SDL_FillRect(square, NULL, SDL_MapRGB(square->format, 255, 255, 255));
    SDL_BlitSurface(square, NULL, window, &position_to_blit);

    SDL_FreeSurface(square);
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


/*----------------------------------------
------------------------------------------
----------------TETROMINOES---------------
------------------------------------------
----------------------------------------*/


/*------------------------------
------GENERATE NEW TETROMINO----
------------------------------*/

void generate_new_tetromino(int form, int current_tetromino_pos[][2], Grid grid) {
    switch (form) {
     case 0: // ****
        current_tetromino_pos[0][0] = grid.size_x / 3;
        current_tetromino_pos[0][1] = 0;

        current_tetromino_pos[1][0] = grid.size_x / 3 + 1;
        current_tetromino_pos[1][1] = 0;

        current_tetromino_pos[2][0] = grid.size_x / 3 + 2;
        current_tetromino_pos[2][1] = 0;

        current_tetromino_pos[3][0] = grid.size_x / 3 + 3;
        current_tetromino_pos[3][1] = 0;
        break;

    case 1: // *
            // ***
       current_tetromino_pos[0][0] = grid.size_x / 3;
       current_tetromino_pos[0][1] = 0;

       current_tetromino_pos[1][0] = grid.size_x / 3;
       current_tetromino_pos[1][1] = 1;

       current_tetromino_pos[2][0] = grid.size_x / 3 + 1;
       current_tetromino_pos[2][1] = 1;

       current_tetromino_pos[3][0] = grid.size_x / 3 + 2;
       current_tetromino_pos[3][1] = 1;
       break;
   }
}

/*------------------------------
-------MAKE TETROMINO FALL------
------------------------------*/


void make_tetromino_fall(Grid grid, int current_tetromino_pos[][2]) {
    int i;
    int j = 0;

    // If we are at the last line.
    if (current_tetromino_pos[0][1] == grid.size_y - 1) {
        generate_new_tetromino(0, current_tetromino_pos, grid);
    }

    // Check if tetromino can go down.
    for (i = 0; i < 4; i++) {
        // If the case below if empty.
        if (grid.data[current_tetromino_pos[i][0]][current_tetromino_pos[i][1] + 1] == 0) {
            j++;
        }
    }

    if (j == 4) { // If the 4 squares of the tetromino can go down, we make it go down.
        // Destroying the old tetromino's position.
        for (i = 0; i < 4; i++) {
            grid.data[current_tetromino_pos[i][0]][current_tetromino_pos[i][1]] = 0;
            current_tetromino_pos[i][1]++;
        }

        // Drawing the tetromino at its new position.
        for (i = 0; i < 4; i++) {
            grid.data[current_tetromino_pos[i][0]][current_tetromino_pos[i][1]] = 1;
        }
    }

    else { // If the 4 squares of the tetromino cannot go down.
        generate_new_tetromino(1, current_tetromino_pos, grid);
    }
}
