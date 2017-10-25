//
// Created by efry on 21/07/2017.
//

#include <SDL.h>

int main(int argc, char *argv[]) {
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("argh!!");
    }

    SDL_Quit();
    return 0;
}