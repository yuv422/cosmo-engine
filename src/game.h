//
// Created by efry on 25/10/2017.
//

#ifndef COSMO_ENGINE_GAME_H
#define COSMO_ENGINE_GAME_H

#include <stdbool.h>
#include "defines.h"

unsigned char *load_file(const char *filename, unsigned char *buf, uint32 buf_size);

void game_init();
void game_loop();

#endif //COSMO_ENGINE_GAME_H
