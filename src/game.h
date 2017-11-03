//
// Created by efry on 25/10/2017.
//

#ifndef COSMO_ENGINE_GAME_H
#define COSMO_ENGINE_GAME_H

#include <stdbool.h>
#include "defines.h"

typedef enum {
    PLAY_GAME=0,
    PLAY_DEMO=1,
    RECORD_DEMO=2
} game_play_mode_enum;

extern game_play_mode_enum game_play_mode;

unsigned char *load_file(const char *filename, unsigned char *buf, uint32 buf_size);

void game_init();
void game_loop();
void set_initial_game_state();


#endif //COSMO_ENGINE_GAME_H
