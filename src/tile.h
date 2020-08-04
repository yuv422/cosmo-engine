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

#ifndef COSMO_ENGINE_TILE_H
#define COSMO_ENGINE_TILE_H

#include "defines.h"
typedef enum {
    SOLID,
    TRANSPARENT,
    FONT
} TileType;

enum TileAttr
{
    BLOCK_DOWN = 0x1,
    BLOCK_UP = 0x2,
    BLOCK_LEFT = 0x4,
    BLOCK_RIGHT = 0x8,
    SLIPPERY = 0x10,
    IN_FRONT = 0x20,
    SLOPED = 0x40,
    CAN_GRAB_WALL = 0x80,
};

typedef struct {
    TileType type;
    uint8 pixels[64];
} Tile;

typedef struct {
    uint16 height;
    uint16 width;
    uint16 tile_num;
} TileInfo;

typedef struct {
    uint16 num_frames;
    TileInfo *frames;
} Sprite;

#define TILE_ATTR_NONE              0u
#define TILE_ATTR_BLOCK_DOWN      0x1u
#define TILE_ATTR_BLOCK_UP        0x2u
#define TILE_ATTR_BLOCK_LEFT      0x4u
#define TILE_ATTR_BLOCK_RIGHT     0x8u
#define TILE_ATTR_SLIPPERY       0x10u
#define TILE_ATTR_IN_FRONT       0x20u
#define TILE_ATTR_SLOPED         0x40u
#define TILE_ATTR_CAN_GRAB_WALL  0x80u

#define TILE_HEIGHT 8
#define TILE_WIDTH 8

#define TRANSPARENT_COLOR 255

extern uint8 tileattr_mni_data[7000];

void tile_attr_load();

Tile *load_tiles(const char *filename, TileType type, uint16 *num_tiles_loaded);

Sprite *load_tile_info(const char *filename, uint16 *num_records_loaded);

#endif //COSMO_ENGINE_TILE_H
