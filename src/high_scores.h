/*
 *  Cosmo-Engine
 *  Copyright Eric Fry (c) 2018. All rights reserved.
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

#ifndef COSMO_ENGINE_HIGH_SCORES_H
#define COSMO_ENGINE_HIGH_SCORES_H

#include "defines.h"

#define NUM_HIGH_SCORE_ENTRIES 10

#define HIGH_SCORE_MAX_NAME_LENGTH 14

typedef struct HighScore {
    char name[HIGH_SCORE_MAX_NAME_LENGTH + 1];
    uint32 score;
} HighScore;

void clear_high_score_table();
void add_high_score_with_name(uint32 new_score, const char *name);

void show_high_scores();
HighScore get_high_score(uint8 position);

#endif //COSMO_ENGINE_HIGH_SCORES_H
