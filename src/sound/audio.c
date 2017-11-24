//
// Created by efry on 22/11/2017.
//

#include <SDL.h>
#include <SDL_mixer.h>
#include "audio.h"


void audio_init()
{
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        printf("ERROR: intialising audio!\n");
        return;
    }

    if( Mix_OpenAudio( AUDIO_SAMPLE_RATE, AUDIO_S16LSB, 1, 4096 ) == -1 )
    {
        printf("ERROR: Opening audio mixer!\n");
        return;
    }
}

void audio_shutdown()
{
    Mix_CloseAudio();
}