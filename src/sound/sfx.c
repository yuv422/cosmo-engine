//
// Created by Eric Fry on 22/11/2017.
//

#include <defines.h>
#include <files/file.h>
#include <game.h>
#include <stdlib.h>
#include <SDL_mixer.h>
#include "sfx.h"
#include "audio.h"

#define SFX_SAMPLE_RATE 140
#define PC_PIT_RATE 1193182 // It is actually 1193181.8181...Hz

typedef struct Sfx {
    uint8 priority;
    Mix_Chunk *sample;
} Sfx;

Sfx *sfxs;
int num_sfx = 0;

int get_num_sfx(const char *filename)
{
    File file;
    open_file(filename, &file);
    file_seek(&file, 6);
    int count = file_read2(&file);
    file_close(&file);
    return count;
}

int get_num_samples(File *file, int offset, int index, int total)
{
    if(index < total - 1)
    {
        file_seek(file, (index+2)*16);
        int next_offset = file_read2(file);
        return ((next_offset - offset) / 2) - 1;
    }

    return ((file_get_filesize(file) - offset) / 2) - 1;
}

Mix_Chunk *convert_sfx_to_wave(File *file, int offset, int num_samples)
{
    int sample_length = (FREQUENCY/140);
    sample_length = 0x2000 * FREQUENCY / PC_PIT_RATE;
    Mix_Chunk *chunk = (Mix_Chunk *)malloc(sizeof(Mix_Chunk));
    chunk->alen = num_samples*sample_length*2;
    chunk->abuf = (Uint8 *)malloc(num_samples*sample_length*2);
    chunk->allocated = 0;
    chunk->volume = 128;

    file_seek(file, offset);

    sint16 *wave_data = (sint16 *)chunk->abuf;

    for(int i=0; i < num_samples; i++)
    {
        uint16 freq = file_read2(file);
        if (freq)
        {
            sint16 beepWaveVal = 4095; // 32767 - Too loud
            uint16 beepHalfCycleCounter = 0;
            for (int sampleCounter = 0; sampleCounter < sample_length; sampleCounter++) {
                wave_data[i*sample_length+sampleCounter] = beepWaveVal;
                beepHalfCycleCounter += 2 * PC_PIT_RATE;
                if (beepHalfCycleCounter >= FREQUENCY * freq) {
                    beepHalfCycleCounter %= FREQUENCY * freq;
                    beepWaveVal = -beepWaveVal;
                }
            }
        }
        else
        {
            memset(&wave_data[i*sample_length], 0, sample_length*2); //silence
        }
    }

    return chunk;
}

int load_sfx_file(const char *filename, int sfx_offset)
{
    File file;
    open_file(filename, &file);
    file_seek(&file, 6);
    int count = file_read2(&file);
    for(int i=0;i<count;i++)
    {
        file_seek(&file, (i+1) * 16); //+1 to skip header.
        int offset = file_read2(&file);
        Sfx *sfx = &sfxs[sfx_offset + i];
        sfx->priority = file_read1(&file);
        int num_samples = get_num_samples(&file, offset, i, count);
        printf("sfx[%d] samples = %d\n", i+sfx_offset, num_samples);
        sfx->sample = convert_sfx_to_wave(&file, offset, num_samples);
    }
    return count;
}

void load_sfx()
{
    num_sfx = 0;
    num_sfx += get_num_sfx("SOUNDS.MNI");
    num_sfx += get_num_sfx("SOUNDS2.MNI");
    num_sfx += get_num_sfx("SOUNDS3.MNI");

    printf("Total Sfx %d\n", num_sfx);

    sfxs = (Sfx *)malloc(sizeof(Sfx) * num_sfx);

    int sfx_offset = load_sfx_file("SOUNDS.MNI", 0);
    sfx_offset += load_sfx_file("SOUNDS2.MNI", sfx_offset);
    load_sfx_file("SOUNDS3.MNI", sfx_offset);
}

void play_sfx(int sfx_number)
{
    Mix_PlayChannel(-1, sfxs[sfx_number].sample, 0);
}
