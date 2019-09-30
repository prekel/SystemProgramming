//#include <SDL.h"
#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* win = NULL;
SDL_Surface* john = NULL;

int Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr,"Can't init: %s\n", SDL_GetError());
        return 1;
    }

    win = SDL_CreateWindow("Обедающие философы",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

    if (win == NULL)
    {
        fprintf(stderr,"Can't create window: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

int Quit()
{
    SDL_FreeSurface(john);

    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}

int main(int argc, char** args)
{
    if (Init() == 1)
    {
        return 1;

    }

    bool run = true;
    SDL_Event e;

    while (run)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                run = false;
            }

            if (e.type == SDL_KEYDOWN)
            {
                printf("%d\n", e.key.keysym.scancode);
                fflush(stdout);
                if (e.key.keysym.sym == SDLK_UP)
                {
                    //printf("Up");
                    //fflush(stdout);
                }
                if (e.key.keysym.sym == SDLK_DOWN)
                {
                    //printf("Down");
                   // fflush(stdout);
                }
            }
        }
    }

    return Quit();
}
