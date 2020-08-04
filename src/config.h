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
#ifndef COSMO_ENGINE_CONFIG_H
#define COSMO_ENGINE_CONFIG_H

#include <SDL_keycode.h>
#include "defines.h"

void load_config_file();
void write_config_file();

uint8 keycode_to_scancode(SDL_Keycode keycode);
const char *scancode_to_string(uint8 scan_code);

void load_config_from_command_line(int argc, char *argv[]);

char *get_data_dir_full_path(const char *filename);
char *get_save_dir_full_path(const char *filename);
char *get_game_dir_full_path(const char *filename);

void config_cleanup();

#endif //COSMO_ENGINE_CONFIG_H
