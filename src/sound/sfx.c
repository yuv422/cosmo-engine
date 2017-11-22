//
// Created by Eric Fry on 22/11/2017.
//

#include <defines.h>
#include <files/file.h>
#include <game.h>
#include <stdlib.h>
#include "sfx.h"

typedef struct Sfx {
    uint8 priority;
    char *sample;
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
        return (next_offset - offset) / 2;
    }

    return (file_get_filesize(file) - offset) / 2;
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
        int sample_length = get_num_samples(&file, offset, i, count);
        printf("sfx[%d] samples = %d\n", i+sfx_offset, sample_length);
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
