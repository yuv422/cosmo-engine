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
#ifndef COSMO_ENGINE_EFFECTS_H
#define COSMO_ENGINE_EFFECTS_H


#include "defines.h"

void struct6_add_sprite(int x_pos, int y_pos);
int struct6_1B4FC(int actorInfoIndex, int frame_num, int x_pos, int y_pos);
void struct6_update_sprites();
void struct6_clear_sprites();

int blow_up_actor_with_bomb(int actorInfoIndex, int frame_num, int x_pos, int y_pos);
void effect_add_sprite(int actorInfoIndex, int frame_num, int x_pos, int y_pos, int arg_8, int counter);

void effect_update_sprites();
void effect_clear_sprites();

void explode_effect_add_sprite(int actorInfoIndex, int frame_num, int x_pos, int y_pos);
void explode_effect_update_sprites();
void explode_effect_clear_sprites();

void exploding_balls_effect(int x_pos, int y_pos);

void update_rain_effect();

void add_brightness_obj(uint8 type, int x_pos, int y_pos);

void update_brightness_objs();
void clear_brightness_objs();

#endif //COSMO_ENGINE_EFFECTS_H
