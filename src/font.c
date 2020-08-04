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

#include <stdio.h>
#include <string.h>
#include "font.h"
#include "tile.h"
#include "util.h"
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
    uint8 font_color = FONT_WHITE;
    char buf[32];
    sprintf(buf, "%d", number);
    for(int i=0;i < cosmo_strnlen(buf, sizeof(buf)); i++)
    {
        video_draw_font_tile(&font_tiles[buf[i]-48+26], (x_pos - cosmo_strnlen(buf, sizeof(buf)) + i + 1) * 8, y_pos * 8, font_color);
    }
}

void display_char(int x_pos, int y_pos, char c, uint8 font_color)
{
    if(c == 0x18 || c == 0x19 || c == 0x1b || c == 0x1c) //FIXME hack to get arrow key font to render.
    {
        video_draw_font_tile(&font_tiles[c-25 + 3], x_pos * 8, y_pos * 8, font_color);
        return;
    }

    if(c >= 32 && c < 91)
    {
        video_draw_font_tile(&font_tiles[c-48+26], x_pos * 8, y_pos * 8, font_color);
    }
    else
    {
        video_draw_font_tile(&font_tiles[c-97+69], x_pos * 8, y_pos * 8, font_color);
    }
}

void display_text(int x_pos, int y_pos, const char *text)
{
    display_text_with_color(x_pos, y_pos, text, 0xf);
}

void display_text_with_color(int x_pos, int y_pos, const char *text, uint8 color)
{
    int len = (int)strlen(text);
    for(int i=0; i < len; i++)
    {
        display_char(x_pos + i, y_pos, text[i], color);
    }
}
