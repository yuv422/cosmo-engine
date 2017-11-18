//
// Created by efry on 18/11/2017.
//

#include <stdio.h>
#include <string.h>
#include "font.h"
#include "tile.h"
#include "video.h"

Tile *font_tiles;

void font_load_tiles()
{
    uint16 num_tiles;
    font_tiles = load_tiles("FONTS.MNI", FONT, &num_tiles);
    printf("Loading %d font tiles.\n", num_tiles);
}

void display_number(int x_pos, int y_pos, uint32 number)
{
    char buf[32];
    sprintf(buf, "%d", number);
    for(int i=0;i < strlen(buf); i++)
    {
        video_draw_tile(&font_tiles[buf[i]-48+26], (x_pos - strlen(buf) + i + 1) * 8, y_pos * 8);
    }
}

