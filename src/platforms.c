//
// cosmo_engine created on 27/Nov/2017.
//

#include "platforms.h"
#include "defines.h"
#include "player.h"
#include "map.h"
#include "input.h"
#include "actor.h"

uint16 num_mud_fountains = 0;
MovingPlatform moving_platform_tbl[10];
MudFountain mud_fountain_tbl[10];

void update_mud_fountains()
{
    for(int si=0;si < num_mud_fountains; si++)
    {
        MudFountain *mud_fountain = &mud_fountain_tbl[si];
        if(mud_fountain->pause_counter == 0)
        {
            mud_fountain->length_counter++;
            if(mud_fountain->length_counter != mud_fountain->max_height)
            {
                map_write_tile_cell(0, mud_fountain->x, mud_fountain->y);
                map_write_tile_cell(0, mud_fountain->x + 1 + 1, mud_fountain->y);
                if(player_death_counter == 0)
                {
                    if(mud_fountain->y - 1 == player_y_pos)
                    {
                        if(mud_fountain->direction == 0)
                        {
                            player_move_on_platform(mud_fountain->x, mud_fountain->x + 2, 0, 1);
                        }
                        else
                        {
                            player_move_on_platform(mud_fountain->x, mud_fountain->x + 2, 0, 5);
                        }
                    }
                }
                
                if(mud_fountain->direction == 0)
                {
                    mud_fountain->y--;
                    mud_fountain->current_height++;
                }
                else
                {
                    mud_fountain->y++;
                    mud_fountain->current_height--;
                }
                
                map_write_tile_cell(0x48, mud_fountain->x, mud_fountain->y);
                map_write_tile_cell(0x48, mud_fountain->x + 2, mud_fountain->y);
            }
            else
            {
                mud_fountain->length_counter = 0;
                mud_fountain->direction = (uint16)((mud_fountain->direction ? -1 : 0) + 1);
                mud_fountain->pause_counter = 10;
            }
        }
        else
        {
            mud_fountain->pause_counter--;
        }
    }


    return;
}

void display_mud_fountains()
{
    static uint16 frame_counter = 0;
    static uint16 frame_num = 0;
    frame_counter++;
    if ((frame_counter & 1) != 0)
    {
        frame_num++;
    }
    for (int i = 0; i < num_mud_fountains; i++)
    {
        MudFountain *mud_fountain = &mud_fountain_tbl[i];
        display_actor_sprite_maybe(0x4f, frame_num & 1, mud_fountain->x, mud_fountain->y + 1, 0);

        for (int j = 0; j < mud_fountain->current_height + 1; j++)
        {
            display_actor_sprite_maybe(0x4f, (frame_num & 1) + 1 + 1, mud_fountain->x + 1, mud_fountain->y + j + 1, 0);

            if (player_check_collision_with_actor(0x4f, 2, mud_fountain->x + 1, mud_fountain->y + j + 1) != 0)
            {
                player_decrease_health();
            }
        }
    }

    return;
}