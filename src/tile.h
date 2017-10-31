//
// Created by Eric Fry on 31/10/2017.
//

#ifndef COSMO_ENGINE_TILE_H
#define COSMO_ENGINE_TILE_H

#include "defines.h"

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

#define TILE_ATTR_BLOCK_DOWN      0x1
#define TILE_ATTR_BLOCK_UP        0x2
#define TILE_ATTR_BLOCK_LEFT      0x4
#define TILE_ATTR_BLOCK_RIGHT     0x8
#define TILE_ATTR_SLIPPERY       0x10
#define TILE_ATTR_IN_FRONT       0x20
#define TILE_ATTR_SLOPED         0x40
#define TILE_ATTR_CAN_GRAB_WALL  0x80

extern uint8 tileattr_mni_data[7000];

#endif //COSMO_ENGINE_TILE_H
