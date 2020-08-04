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

#ifndef COSMO_ENGINE_STATUS_H
#define COSMO_ENGINE_STATUS_H

#include "defines.h"

#define STATUS_BAR_HEIGHT 6

#define STATUS_BAR_WIDTH 38

void status_load_tiles();

void status_panel_init();

void status_display();

void add_to_score_update_on_display(uint32 amount_to_add_low, int x_pos, int y_pos);

void update_health_bar_display();

void display_num_stars_collected();

void display_num_bombs_left();

#endif //COSMO_ENGINE_STATUS_H
