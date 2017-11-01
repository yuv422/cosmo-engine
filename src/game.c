//
// Created by efry on 25/10/2017.
//

#include "palette.h"
#include "player.h"
#include "files/vol.h"
#include "tile.h"
#include "game.h"

typedef enum
{
    QUIT,
    PAUSED,
    CONTINUE
} input_state_enum;

void game_init()
{
    tile_attr_load();
}

input_state_enum read_input()
{
    //FIXME
    return CONTINUE;
}

void game_loop()
{
    int input_state = 0;

    for(;;)
    {
        do
        {
            //lock to 10 FPS here.

            update_palette_anim();

            input_state = read_input();
            if (input_state == QUIT)
                return;

        } while(input_state == PAUSED);

        handle_player_input_maybe();
    }
}

unsigned char *load_file(const char *filename, unsigned char *buf, uint32 buf_size)
{
    if(vol_file_load("COSMO1.VOL", filename, buf, buf_size))
    {
        return buf;
    }

    return vol_file_load("COSMO1.STN", filename, buf, buf_size);
}
