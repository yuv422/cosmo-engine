//
// cosmo_engine created on 27/Nov/2017.
//

#include "platforms.h"
#include "defines.h"
#include "player.h"
#include "map.h"
#include "input.h"

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



