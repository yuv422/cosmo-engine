//
// Created by efry on 4/11/2017.
//

#ifndef COSMO_ENGINE_SAVE_H
#define COSMO_ENGINE_SAVE_H

#include "defines.h"

//Data
extern uint16 cheats_used_flag;

void write_savegame_file(char suffix);
void load_savegame_file(char suffix);

#endif //COSMO_ENGINE_SAVE_H
