//
// cosmo_engine created on 31/Dec/2017.
//

#include <SDL_keycode.h>
#include <files/file.h>
#include <sound/music.h>
#include <sound/sfx.h>
#include "config.h"
#include "high_scores.h"

SDL_Keycode cfg_up_key;
SDL_Keycode cfg_down_key;
SDL_Keycode cfg_left_key;
SDL_Keycode cfg_right_key;
SDL_Keycode cfg_jump_key;
SDL_Keycode cfg_bomb_key;

void load_config_file(const char *filename)
{
    File file;

    if(file_open(filename, "rb", &file))
    {
        //FIXME read file here.
        file_close(&file);
    }
    else
    {
        cfg_up_key = SDLK_UP;
        cfg_down_key = SDLK_DOWN;
        cfg_left_key = SDLK_LEFT;
        cfg_right_key = SDLK_RIGHT;
        cfg_jump_key = SDLK_LCTRL;
        cfg_bomb_key = SDLK_LALT;
        music_on_flag = 1;
        sfx_on_flag = 1;

        add_high_score_with_name(0xf4240, "BART");
        add_high_score_with_name(0xdbba0, "LISA");
        add_high_score_with_name(0xc3500, "MARGE");
        add_high_score_with_name(0xaae60, "ITCHY");
        add_high_score_with_name(0x927c0, "SCRATCHY");
        add_high_score_with_name(0x7a120, "MR. BURNS");
        add_high_score_with_name(0x61a80, "MAGGIE");
        add_high_score_with_name(0x493e0, "KRUSTY");
        add_high_score_with_name(0x30d40, "HOMER");
    }
}

void write_config_file(const char *filename)
{
    //FIXME
}
