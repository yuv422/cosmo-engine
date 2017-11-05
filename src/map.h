//
// Created by efry on 30/10/2017.
//

#ifndef COSMO_ENGINE_MAP_H
#define COSMO_ENGINE_MAP_H

//Data
extern uint16 current_level;
extern int map_width_in_tiles;
extern int map_stride_bit_shift_amt;

extern int mapwindow_x_offset;
extern int mapwindow_y_offset;

int map_get_tile_cell(int x, int y);

void load_level(int level_number);

#endif //COSMO_ENGINE_MAP_H
