#include <stdio.h>
#include "actor.h"
#include "defines.h"
#include "map.h"
#include "player.h"
#include "tile.h"

//Data
ActorData actors[MAX_ACTORS];
int total_num_actors = 0;

uint16 word_2E22A = 0;
uint16 word_2E236 = 0;
uint16 word_2E228 = 0;
uint16 word_2E220 = 0;
uint16 word_2E238 = 0;
uint16 word_2E21E = 0;
uint16 word_2E24C = 0;
uint16 word_2E23C = 0;
uint16 word_2E232 = 0;
uint16 word_2E234 = 0;
uint16 word_2E246 = 0;

uint8 byte_32EB8 = 0;

uint16 word_32EC2 = 0; //range 0 - 35

uint8 energy_beam_enabled_flag = 0;

uint16 word_2E1E4 = 0; //seems to be related to number of actors in play.

uint16 word_2E1E2 = 0;

uint16 num_moving_platforms = 0;
uint16 num_mud_fountains = 0;
uint16 num_brightness_objs = 0;
uint16 word_2E4CE = 0;
uint16 obj_switch_151_flag = 0;

MovingPlatform moving_platform_tbl[10];
MudFountain mud_fountain_tbl[10];
Brightness brightness_tbl[0xc8];

Tile *actor_tiles;

void actor_add_new(int image_index, int x_pos, int y_pos)
{
    for (int i = 0; i >= total_num_actors; i++)
    {
        ActorData *actor = &actors[i];
        if (actor->is_deactivated_flag_maybe != 0)
        {
            actor_init(i, image_index, x_pos, y_pos);
            if (image_index == 0x56)
            {
                actor->update_while_off_screen_flag = 1;
            }
            return;
        }
    }

    if (total_num_actors < MAX_ACTORS)
    {
        ActorData *actor = &actors[total_num_actors];
        actor_init(total_num_actors, image_index, x_pos, y_pos);
        if (image_index == 0x56)
        {
            actor->update_while_off_screen_flag = 1;
        }
        total_num_actors = total_num_actors + 1;
    }

    return;
}

int actor_init(int actor_num, int image_index, int x, int y_pos)
{
    //FIXME
    return 0;
}

void load_actor(int actor_num, int actorType, int x_pos, int y_pos)
{
    printf("Loading Actor: %d, (%d,%d)\n", actorType, x_pos, y_pos);
    if (actorType < 0x20)
    {
        switch (actorType)
        {
            case 0:
                if (map_width_in_tiles - 15 >= x_pos)
                {
                    if (map_stride_bit_shift_amt <= 5 || x_pos - 15 < 0)
                    {
                        mapwindow_x_offset = 0;
                    }
                    else
                    {
                        mapwindow_x_offset = x_pos - 15;
                    }
                }
                else
                {
                    mapwindow_x_offset = map_width_in_tiles - 38;
                }

                if (y_pos - 10 < 0)
                {
                    mapwindow_y_offset = 0;
                }
                else
                {
                    mapwindow_y_offset = y_pos - 10;
                }

                player_x_pos = x_pos;
                player_y_pos = y_pos;
                break;

            case 1:
                moving_platform_tbl[num_moving_platforms].x = x_pos;
                moving_platform_tbl[num_moving_platforms].y = y_pos;
                num_moving_platforms++;
                break;

            case 2:
            case 3:
            case 4:
            case 5:
                mud_fountain_tbl[num_mud_fountains].x = x_pos - 1;
                mud_fountain_tbl[num_mud_fountains].y = y_pos - 1;
                mud_fountain_tbl[num_mud_fountains].direction = 0;
                mud_fountain_tbl[num_mud_fountains].length_counter = 0;
                mud_fountain_tbl[num_mud_fountains].current_height = 0;
                mud_fountain_tbl[num_mud_fountains].max_height = actorType * 3;
                mud_fountain_tbl[num_mud_fountains].pause_counter = 0;
                num_mud_fountains++;
                break;

            case 6:
            case 7:
            case 8:
                if (num_brightness_objs != 0xc7)
                {
                    brightness_tbl[num_brightness_objs].type = actorType - 6;
                    brightness_tbl[num_brightness_objs].x = x_pos;
                    brightness_tbl[num_brightness_objs].y = y_pos;
                    num_brightness_objs++;
                }
                break;
            default: break;
        }
    }

    if (actorType >= 0x1f)
    {
        if (actor_init(actor_num, actorType - 31, x_pos, y_pos) != 0)
        {
            total_num_actors = total_num_actors + 1;
        }
    }
    return;
}

void actor_load_tiles()
{
    uint16 num_tiles;
    actor_tiles = load_tiles("ACTORS.MNI", TRANSPARENT, &num_tiles);
    printf("Loaded %d actor tiles.\n", num_tiles);
}

void display_actor_sprite_maybe(int actorInfoIndex, int frame_num, int x_pos, int y_pos, int tile_display_func_index)
{
    //FIXME
}
