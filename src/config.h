//
// cosmo_engine created on 31/Dec/2017.
//
#ifndef COSMO_ENGINE_CONFIG_H
#define COSMO_ENGINE_CONFIG_H

#include "defines.h"

void load_config_file();
void write_config_file();

uint8 keycode_to_scancode(SDL_Keycode keycode);
const char *scancode_to_string(uint8 scan_code);

#endif //COSMO_ENGINE_CONFIG_H
