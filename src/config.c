//
// cosmo_engine created on 31/Dec/2017.
//

#include <SDL_keycode.h>
#include <files/file.h>
#include <sound/music.h>
#include <sound/sfx.h>
#include "config.h"

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
    }
}

void write_config_file(const char *filename)
{
    //FIXME
}
