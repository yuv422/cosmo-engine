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
#ifndef COSMO_ENGINE_PLATFORMS_H
#define COSMO_ENGINE_PLATFORMS_H

#include "defines.h"

typedef struct MovingPlatform
{
    uint16 x;
    uint16 y;
    uint16 map_tiles[5];
} MovingPlatform;

typedef struct MudFountain
{
    uint16 x;
    uint16 y;
    uint16 direction;
    uint16 length_counter;
    uint16 current_height;
    uint16 max_height;
    uint16 pause_counter;
} MudFountain;

extern uint16 num_moving_platforms;
extern uint16 num_mud_fountains;
extern MovingPlatform moving_platform_tbl[10];
extern MudFountain mud_fountain_tbl[10];

void update_mud_fountains();
void display_mud_fountains();

void update_moving_platforms();

#endif //COSMO_ENGINE_PLATFORMS_H
