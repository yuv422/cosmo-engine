//
// Created by Eric Fry on 22/11/2017.
//

#ifndef COSMO_ENGINE_SFX_H
#define COSMO_ENGINE_SFX_H

#define MAX_SAMPLES_PER_FILE 23 //the game only reads the first 23 sfx in each file.

void load_sfx();
void play_sfx(int sfx_number);

#endif //COSMO_ENGINE_SFX_H
