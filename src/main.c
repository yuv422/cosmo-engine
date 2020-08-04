/*
 *  Cosmo-Engine
 *  Copyright Eric Fry (c) 2017. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

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
#include "input.h"

int cleanup_and_exit();

int main(int argc, char *argv[]) {
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("argh!!");
    }

    load_config_from_command_line(argc, argv);

    video_init();
    audio_init();
    input_init();
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
    config_cleanup();
    video_shutdown();
    audio_shutdown();
    input_shutdown();
    SDL_Quit();

    return 0;
}
