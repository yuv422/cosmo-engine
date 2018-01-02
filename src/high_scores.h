//
// Created by Eric Fry on 2/01/2018.
//

#ifndef COSMO_ENGINE_HIGH_SCORES_H
#define COSMO_ENGINE_HIGH_SCORES_H

#include "defines.h"

void clear_high_score_table();
void add_high_score_with_name(uint32 new_score, const char *name);

void show_high_scores();

#endif //COSMO_ENGINE_HIGH_SCORES_H
