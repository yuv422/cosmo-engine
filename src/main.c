//
// Created by efry on 21/07/2017.
//

#include <SDL.h>
#include "sound/audio.h"
#include "sound/music.h"
#include "game.h"
#include "map.h"
#include "dialog.h"
#include "video.h"
#include "status.h"
#include "config.h"
#include "high_scores.h"
#include "demo.h"
#include "b800.h"

int cleanup_and_exit();

int main(int argc, char *argv[]) {
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("argh!!");
    }

    load_config_from_command_line(argc, argv);

    video_init();
    audio_init();
    game_init();

    video_fill_screen_with_black();

    if(!is_quick_start())
    {
        a_game_by_dialog();
        game_play_mode = main_menu();
    }
    else
    {
        set_initial_game_state();
        game_play_mode = PLAY_GAME;
    }

    while(game_play_mode != QUIT_GAME)
    {
        load_level(current_level);

        if(game_play_mode == PLAY_DEMO)
        {
            load_demo();
        }

        game_loop();
        stop_music();
        if(game_play_mode == PLAY_GAME)
        {
            show_high_scores();
        }
        game_play_mode = main_menu();
    }

    stop_music();
    display_exit_text();

    return cleanup_and_exit();
}

int cleanup_and_exit()
{
    write_config_file();
    video_shutdown();
    audio_shutdown();
    SDL_Quit();

    return 0;
}
