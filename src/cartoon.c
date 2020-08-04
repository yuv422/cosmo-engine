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

#include<stdio.h>
#include "cartoon.h"
#include "tile.h"
#include "video.h"

Tile *cartoon_tiles;
Sprite *sprites;

void load_cartoon_images()
{
    uint16 num_tile_info_records;
    uint16 num_tiles;
    cartoon_tiles = load_tiles("CARTOON.MNI", TRANSPARENT, &num_tiles);
    printf("Loading %d cartoon tiles.\n", num_tiles);

    sprites = load_tile_info("CARTINFO.MNI", &num_tile_info_records);
    printf("Loading %d, cartoon tile info records.\n", num_tile_info_records);
}

void display_cartoon_sequence(uint16 frame_num, uint16 x_pos, uint16 y_pos)
{
    TileInfo *info = &sprites[0].frames[frame_num];
    Tile *tile = &cartoon_tiles[info->tile_num];

    for(int y=0; y < info->height; y++)
    {
        for(int x=0; x < info->width; x++)
        {
            video_draw_tile(tile, (x_pos + x) * 8, (y_pos + y - info->height + 1) * 8);
            tile++;
        }
    }
}
