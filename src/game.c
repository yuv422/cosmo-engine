//
// Created by efry on 25/10/2017.
//

#include <MacTypes.h>
#include "actor.h"
#include "palette.h"
#include "player.h"
#include "files/vol.h"
#include "tile.h"
#include "game.h"
#include "input.h"
#include "dialog.h"
#include "map.h"

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
uint16 word_2E1D6;
uint16 num_stars_collected;
uint16 demo_input_index;
uint16 demo_input_length;
uint8 cheats_used_flag;
uint8 knows_about_powerups_flag;
uint8 finished_game_flag_maybe = 0;
uint8 finished_level_flag_maybe;

uint8 move_platform_flag = 0;

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

void reset_game_state()
{
    finished_game_flag_maybe = 0;
    player_hanging_on_wall_direction = 0;
    byte_2E2E4 = 1;
    player_input_jump_related_flag = 1;
    byte_2E182 = 0;
    word_2E180 = 1;
    player_bounce_flag_maybe = 0;
    player_bounce_height_counter = 0;
    player_direction_related_32E98 = 3;
    player_sprite_dir_frame_offset = 0;
    player_direction = 0x17;
    player_death_counter = 0;
    finished_level_flag_maybe = 0;
    player_invincibility_counter = 0x28;
    teleporter_counter = 0;
    teleporter_state_maybe = 0;
    player_in_pneumatic_tube_flag = 0;
    word_32B88 = 0;
    player_is_teleporting_flag = 0;
    word_32EAC = 0;
    energy_beam_enabled_flag = 1;
    byte_2E17C = 0;

    sub_11062();

    word_2E1F8 = 0;
    move_platform_flag = 1;
    byte_32EB8 = 0;
    palette_2E1EE = 0;
    palette_index = 0;
    word_32EC2 = 0;
    player_fall_off_map_bottom_counter = 0;
    word_28BEA = 0;
    byte_2E21C = 0;
    word_2E1E4 = 0;
    word_2E1E2 = 0;
    num_hits_since_touching_ground = 0;

    //Actor values
    word_2E22A = 0;
    word_2E236 = 0;
    word_2E228 = 0;
    word_2E220 = 0;
    word_2E238 = 0;
    word_2E21E = 0;
    word_2E24C = 0;
    word_2E23C = 0;
    word_2E232 = 0;
    word_2E234 = 0;
    word_2E246 = 0;
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
    uint32 bytes_read;
    if(vol_file_load("COSMO1.VOL", filename, buf, buf_size, &bytes_read))
    {
        return buf;
    }

    return vol_file_load("COSMO1.STN", filename, buf, buf_size, &bytes_read);
}

unsigned char *load_file_in_new_buf(const char *filename, uint32 *file_size)
{
    unsigned char *buf;
    buf = vol_file_load("COSMO1.VOL", filename, NULL, 0, file_size);
    if(buf)
    {
        return buf;
    }

    return vol_file_load("COSMO1.STN", filename, NULL, 0, file_size);
}

bool open_file(const char *filename, File *file)
{
    if(vol_file_open("COSMO1.VOL", filename, file))
    {
        return true;
    }

    return vol_file_open("COSMO1.STN", filename, file);
}