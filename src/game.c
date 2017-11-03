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


//Data
game_play_mode_enum game_play_mode = PLAY_GAME;
uint32 score;
uint8 health;
uint8 num_health_bars;
uint8 current_level;
uint16 word_2E1D6;
uint16 num_stars_collected;
uint16 demo_input_index;
uint16 demo_input_length;
uint8 cheats_used_flag;
uint8 has_had_bomb_flag;
uint8 knows_about_powerups_flag;

void game_init()
{
    tile_attr_load();
}

void set_initial_game_state()
{
    score = 0;
    health = 4;
    num_health_bars = 3;
    current_level = 0;
    num_bombs = 0;
    word_2E1D6 = 0;
    num_stars_collected = 0;
    demo_input_index = 0;
    demo_input_length = 0;
    cheats_used_flag = 0;
    has_had_bomb_flag = 0;
    knows_about_powerups_flag = 0;
    return;
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
