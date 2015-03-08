#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/*----------------------------------------
------------------------------------------
-------------STARTING THE GAME------------
------------------------------------------
----------------------------------------*/


void start_game() {
    SDL_Surface *window = NULL;
    int window_width, window_height, i;

    SDL_Event event;

    window_width = window_height = 408;
    window = SDL_SetVideoMode(window_width, window_height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Tetris : Play", NULL);
    // Filling the window with white.
    SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 255, 255, 255));
    SDL_Flip(window);

    for (i = 0; i < 100; i++) {
        printf("%d", pick_random_form());
    }

    while (1) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                SDL_FreeSurface(window);
                return;
        }
    }
}


/*----------------------------------------
------------------------------------------
----------PICKING A RANDOM NUMBER---------
------------------------------------------
----------------------------------------*/


int pick_random_form() {
    return (rand() % 7); // Pick a random number from 0 to 6 (there are 7 tetris forms).
}
