//
// Created by efry on 25/10/2017.
//

#ifndef COSMO_ENGINE_PALETTE_H
#define COSMO_ENGINE_PALETTE_H

#include <SDL_surface.h>
#include "defines.h"

//Data
extern uint8 palette_anim_type;
extern int palette_index;
extern int palette_2E1EE;

void update_palette_anim();
void update_palette_related_delay_3();

void set_palette_on_surface(SDL_Surface *surface);

#endif //COSMO_ENGINE_PALETTE_H