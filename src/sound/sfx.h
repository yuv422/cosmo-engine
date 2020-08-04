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

#ifndef COSMO_ENGINE_SFX_H
#define COSMO_ENGINE_SFX_H

#include "defines.h"

#define MAX_SAMPLES_PER_FILE 23 //the game only reads the first 23 sfx in each file.

extern uint8 sfx_on_flag;

void load_sfx();
void play_sfx(int sfx_number);

#endif //COSMO_ENGINE_SFX_H
