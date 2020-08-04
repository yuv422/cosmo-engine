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

#include <stdio.h>
#include "status.h"
#include "defines.h"
#include "tile.h"
#include "video.h"
#include "map.h"
#include "game.h"
#include "font.h"
#include "player.h"

Tile *status_tiles;

void status_load_tiles() {
    uint16 num_tiles;
    status_tiles = load_tiles("STATUS.MNI", SOLID, &num_tiles);
    printf("Loading %d status tiles.\n", num_tiles);
}

void status_display()
{
    for(int y=0; y < STATUS_BAR_HEIGHT; y++)
    {
        for (int x = 0; x < STATUS_BAR_WIDTH; x++)
        {
            video_draw_tile(&status_tiles[x + y * STATUS_BAR_WIDTH], (x + 1) * TILE_WIDTH, (y+MAP_WINDOW_HEIGHT+1) * TILE_HEIGHT);
        }
    }
}

void add_to_score_update_on_display(uint32 amount_to_add_low, int x_pos, int y_pos)
{
    score += amount_to_add_low;
    display_number(x_pos, y_pos, score);
}

void update_health_bar_display()
{
    int x = 0x11;
    int y = 0x16;
    for(int i=0;i< num_health_bars;i++)
    {
        if(health - 1 > i)
        {
            video_draw_tile(&font_tiles[95], (x - i) * TILE_WIDTH, y * TILE_HEIGHT);
            video_draw_tile(&font_tiles[96], (x - i) * TILE_WIDTH, (y+1) * TILE_HEIGHT);
        }
        else
        {
            video_draw_tile(&font_tiles[9], (x - i) * TILE_WIDTH, y * TILE_HEIGHT);
            video_draw_tile(&font_tiles[8], (x - i) * TILE_WIDTH, (y+1) * TILE_HEIGHT);
        }
    }
}

void display_num_stars_collected()
{
    display_number(0x23,0x16,num_stars_collected);
}

void status_panel_init()
{
    video_fill_screen_with_black();
    status_display();
    add_to_score_update_on_display(0, 9, 0x16);
    update_health_bar_display();
    display_num_stars_collected();
    display_num_bombs_left();
}

void display_num_bombs_left()
{
    video_draw_tile(&font_tiles[97], 0x18 * TILE_WIDTH, 0x17 * TILE_HEIGHT);
    display_number(0x18, 0x17, num_bombs);
}
