//
// Created by efry on 21/07/2017.
//

#include <SDL.h>
#include "game.h"
#include "map.h"
#include "dialog.h"
#include "video.h"

int main(int argc, char *argv[]) {
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("argh!!");
    }

    video_init();
    game_init();
    //do while here
    game_play_mode = main_menu();
    load_level(current_level);

    SDL_Event event;
    while(1)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            break;
        }
    }

    video_shutdown();
    SDL_Quit();
    return 0;
}