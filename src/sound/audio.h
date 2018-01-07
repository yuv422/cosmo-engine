//
// cosmo_engine created on 22/Nov/2017.
//
#ifndef COSMO_ENGINE_AUDIO_H
#define COSMO_ENGINE_AUDIO_H

#include <defines.h>

extern int audio_sample_rate;
extern int audio_num_channels;

void audio_init();
void audio_shutdown();

#endif //COSMO_ENGINE_AUDIO_H
