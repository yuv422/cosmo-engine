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

void display_char(int x_pos, int y_pos, char c)
{
    if(c == 0x18 || c == 0x19) //FIXME hack to get arrow key font to render.
    {
        video_draw_tile(&font_tiles[c-25 + 3], x_pos * 8, y_pos * 8);
        return;
    }

    if(c >= 32 && c < 91)
    {
        video_draw_tile(&font_tiles[c-48+26], x_pos * 8, y_pos * 8);
    }
    else
    {
        video_draw_tile(&font_tiles[c-97+69], x_pos * 8, y_pos * 8);
    }
}

void display_text(int x_pos, int y_pos, const char *text)
{
    int len = strlen(text);
    for(int i=0; i < len; i++)
    {
        display_char(x_pos + i, y_pos, text[i]);
    }
}
