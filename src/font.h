//
// cosmo_engine created on 18/Nov/2017.
//
#ifndef COSMO_ENGINE_FONT_H
#define COSMO_ENGINE_FONT_H

#include "defines.h"
#include "tile.h"

extern Tile *font_tiles;

void font_load_tiles();

void display_number(int x_pos, int y_pos, uint32 number);

#endif //COSMO_ENGINE_FONT_H