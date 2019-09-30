/*! \file
 *  \brief Файл с функцией main
 *
 *  \details Главный файл содержащий главную функцию main.
 */

//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/types.h>
//#include <time.h>
//#include <pthread.h>
//#ifdef _WIN32
//#include <windows.h>
//#endif

#include <SDL.h>


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
            "SDL2Test",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}