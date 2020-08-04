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
#include <SDL_pixels.h>
#include "defines.h"
#include "tile.h"

#ifndef COSMO_ENGINE_VIDEO_H
#define COSMO_ENGINE_VIDEO_H

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define DEFAULT_SCALE_FACTOR 2

void fade_to_black_speed_3();
void fade_in_from_black_with_delay_3();

bool video_init();
void video_shutdown();
void video_set_fullscreen(bool new_state);
void video_set_scale_factor(int scale_factor);

void set_text_mode();
void set_game_mode();

void video_update();

void video_fill_screen_with_black();

void video_draw_tile(Tile *tile, uint16 x, uint16 y);
void video_draw_tile_solid_white(Tile *tile, uint16 x, uint16 y);
void video_draw_tile_mode3(Tile *tile, uint16 x, uint16 y);
void video_draw_tile_with_clip_rect(Tile *tile, uint16 x, uint16 y, uint16 clip_x, uint16 clip_y, uint16 clip_w, uint16 clip_h);
void video_draw_tile_flipped(Tile *tile, uint16 x, uint16 y);
void video_draw_font_tile(Tile *tile, uint16 x, uint16 y, uint8 font_color);


void video_draw_highlight_effect(uint16 x, uint16 y, uint8 type);

void video_draw_fullscreen_image(uint8 *pixels);
void video_update_palette(int palette_index, SDL_Color new_color);

void fade_to_black(uint16 wait_time);
void fade_to_white(uint16 wait_time);
void fade_in_from_black(uint16 wait_time);

void video_draw_text(uint8 character, int fg, int bg, int x, int y);

#endif //COSMO_ENGINE_VIDEO_H
