#include "actor.h"
#include "defines.h"
#include "map.h"
#include "player.h"

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
    di = y_pos;
    si = x_pos;
    if (actorType < 0x20)
    {
        switch (actorType)
        {
            case 0:
                if (map_width_in_tiles - 15 >= si)
                {
                    if (map_stride_bit_shift_amt <= 5 || si - 15 < 0)
                    {
                        mapwindow_x_offset = 0;
                    }
                    else
                    {
                        mapwindow_x_offset = si - 15;
                    }
                }
                else
                {
                    mapwindow_x_offset = map_width_in_tiles - 38;
                }

                if (di - 10 < 0)
                {
                    mapwindow_y_offset = 0;
                }
                else
                {
                    mapwindow_y_offset = di - 10;
                }

                player_x_pos = si;
                player_y_pos = di;
                break;

            case 1:
                *(num_moving_platforms * ax + moving_platform_tbl) = si;
                *num_moving_platforms * ax + moving_platform_tbl->y = di;
                num_moving_platforms = num_moving_platforms + 1;
                break;

            case 2:
            case 3:
            case 4:
            case 5:
/* push si - 1 */
/* pop ax */
                *(num_mud_fountains * ax + ) = si - 1;
/* push di - 1 */
/* pop ax */
                *num_mud_fountains * ax + ->y = di - 1;
                *num_mud_fountains * ax + ->direction = 0;
                *num_mud_fountains * ax + ->length_counter = 0;
                *num_mud_fountains * ax + ->current_height = 0;
/* push actorType * ax */
/* pop ax */
                *num_mud_fountains * ax + ->max_height = actorType * 3;
                *num_mud_fountains * ax + ->pause_counter = 0;
                num_mud_fountains = num_mud_fountains + 1;
                break;

            case 6:
            case 7:
            case 8:
                if (num_brightness_objs != 0xc7)
                {
/* push actorType - 6 */
/* pop ax */
                    *((num_brightness_objs << 3) + brightness_tbl) = ax;
                    *(num_brightness_objs << 3) + brightness_tbl->x = si;
                    *(num_brightness_objs << 3) + brightness_tbl->y = di;
                    num_brightness_objs = num_brightness_objs + 1;
                }
                break;

// node 00020224-00000000 #insn=0 use={} def={} in={} out={} pred={ 2010C 20117 20141 201DE}
        }
    }

// node 00020224-00020248 #insn=2 use={} def={bp, si, di} in={} out={} pred={ 2009C} RETURN
    if (actorType >= 0x1f)
    {
        if (actor_init(actor_num, actorType - 31, si, di) != 0)
        {
            total_num_actors = total_num_actors + 1;
        }
    }
    return;
}