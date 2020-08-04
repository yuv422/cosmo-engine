/*
 *  Cosmo-Engine
 *  Copyright Eric Fry (c) 2017. All rights reserved.
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

#include <SDL.h>
#ifdef __EMSCRIPTEN__
#include <SDL2/SDL_mixer.h>
#else
#include <SDL_mixer.h>
#endif
#include "audio.h"
#include "music.h"

#define AUDIO_DESIRED_SAMPLE_RATE 22050
#define AUDIO_DESIRED_NUM_CHANNELS 1

AudioConfig audioConfig;

void audio_init()
{
    audioConfig.enabled = false;
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        printf("ERROR: intialising audio!\n");
        return;
    }

    if( Mix_OpenAudio( AUDIO_DESIRED_SAMPLE_RATE, AUDIO_S16LSB, AUDIO_DESIRED_NUM_CHANNELS, 1024*2 ) == -1 )
    {
        printf("ERROR: Opening audio mixer!\n");
        return;
    }

    // get and print the audio format in use
    int numtimesopened;
    Uint16 format;
    numtimesopened=Mix_QuerySpec(&audioConfig.sampleRate, &format, &audioConfig.numChannels);
    if(!numtimesopened) {
        printf("Mix_QuerySpec: %s\n",Mix_GetError());
    }
    else {
        const char *format_str="Unknown";
        switch(format) {
            case AUDIO_U8: format_str="U8"; break;
            case AUDIO_S8: format_str="S8"; break;
            case AUDIO_U16LSB: format_str="U16LSB"; break;
            case AUDIO_S16LSB:
                format_str="S16LSB";
                audioConfig.format = AUDIO_INT16_SIGNED_LSB;
                audioConfig.bytesPerSample = 2;
                break;
            case AUDIO_U16MSB: format_str="U16MSB"; break;
            case AUDIO_S16MSB: format_str="S16MSB"; break;
            case AUDIO_F32LSB:
                format_str="F32LSB";
                audioConfig.format = AUDIO_FLOAT32_SIGNED_LSB;
                audioConfig.bytesPerSample = 4;
                break;
        }
        printf("audio_init(): opened=%d times  frequency=%dHz  format=%s  channels=%d\n",
               numtimesopened, audioConfig.sampleRate, format_str, audioConfig.numChannels);

        if(format != AUDIO_S16LSB && format != AUDIO_F32LSB)
        {
            printf("ERROR: AUDIO_S16LSB or AUDIO_F32LSB required. found 0x%X\n", format);
            audio_shutdown();
            return;
        }
    }

    music_init();
    audioConfig.enabled = true;
}

void audio_shutdown()
{
    Mix_CloseAudio();
}
