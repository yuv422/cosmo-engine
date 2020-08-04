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

#ifndef COSMO_ENGINE_DEFINES_H
#define COSMO_ENGINE_DEFINES_H

#include <stdbool.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;

typedef enum {
    NOT_BLOCKED = 0,
    BLOCKED = 1,
    SLOPE = 2
} BlockingType;

typedef enum {
    UP    = 0,
    DOWN  = 1,
    LEFT  = 2,
    RIGHT = 3
} Direction;

#endif //COSMO_ENGINE_DEFINES_H
