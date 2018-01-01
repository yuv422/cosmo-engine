//
// Created by efry on 21/07/2017.
//

#include <SDL.h>
#include <sound/audio.h>
#include "game.h"
#include "map.h"
#include "dialog.h"
#include "video.h"
#include "status.h"
#include "config.h"

int cleanup_and_exit();

int main(int argc, char *argv[]) {
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("argh!!");
    }

    video_init();
    audio_init();
    game_init();

    video_fill_screen_with_black();

    a_game_by_dialog();

    //do while here
    game_play_mode = main_menu();
    while(game_play_mode != QUIT_GAME)
    {
        load_level(current_level);

        game_loop();

        game_play_mode = main_menu();
    }

    return cleanup_and_exit();
}

int cleanup_and_exit()
{
    write_config_file("COSMO1.CFG");
    video_shutdown();
    audio_shutdown();
    SDL_Quit();

    return 0;
}