#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "main.h"
#include "game/game.h"


int main()
{
    SDL_Surface *window = NULL;

    int continue_loop = 1;

    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    draw_main_window(window);

    while (continue_loop) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continue_loop = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_KP1:
                        start_game();
                        break;
                }
        }
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}

void draw_main_window(SDL_Surface* window) {
    window = SDL_SetVideoMode(408, 408, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Mario Sokoban", NULL);
    // We fill the window with a white background.
    SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 255, 255, 255));
    write_text_on_window(window, 160, 20, 30, 0, 0, 0, "Tetris");
    write_text_on_window(window, 150, 150, 30, 0, 0, 0, "1. Play");
}
