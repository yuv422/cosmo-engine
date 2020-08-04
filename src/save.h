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

#ifndef COSMO_ENGINE_SAVE_H
#define COSMO_ENGINE_SAVE_H

#include "defines.h"

typedef struct SaveGameData {
    uint8 health;
    uint32 score;
    uint16 num_stars_collected;
    uint16 current_level;
    uint16 num_bombs;
    uint8 num_health_bars;
    uint16 cheats_used_flag;
    uint16 has_had_bomb_flag;
    uint8 show_monster_attack_hint;
    uint8 knows_about_powerups_flag;
} SaveGameData;

typedef enum SaveStatus {
    LOADED,
    FILE_IO_ERROR,
    CRC_ERROR
} SaveStatus;

//Data
extern uint16 cheats_used_flag;

void write_savegame_file(char suffix);
bool load_savegame_file(char suffix);
SaveStatus load_savegame_data_from_file(char suffix, SaveGameData *data);
#endif //COSMO_ENGINE_SAVE_H
