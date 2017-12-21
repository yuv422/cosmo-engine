//
// Created by efry on 25/10/2017.
//

#include <SDL_pixels.h>
#include <SDL_surface.h>
#include <sound/sfx.h>
#include "util.h"
#include "palette.h"
#include "defines.h"
#include "video.h"

int next_pal_colour = 0;
uint8 palette_anim_type = 0;
int palette_index = 0;
int palette_2E1EE = 0;

SDL_Color palette[16] = {
        {0,0,0,0},
        {0x00,0x00,0xAA,0},
        {0x00,0xAA,0x00,0},
        {0x00,0xAA,0xAA,0},
        {0xAA,0x00,0x00,0},
        {0xAA,0x00,0xAA,0},
        {0xAA,0x55,0x00,0},
        {0xAA,0xAA,0xAA,0},
        {0x55,0x55,0x55,0},
        {0x55,0x55,0xFF,0},
        {0x55,0xFF,0x55,0},
        {0x55,0xFF,0xFF,0},
        {0xFF,0x55,0x55,0},
        {0xFF,0x55,0xFF,0},
        {0xFF,0xFF,0x55,0},
        {0xFF,0xFF,0xFF,0}
};

void set_palette_on_surface(SDL_Surface *surface)
{
    SDL_SetPaletteColors(surface->format->palette, palette, 0, 16);
}

void set_palette_color(char pal_reg, char color)
{
    video_update_palette(pal_reg, palette[color]);
}

unsigned char palette_anim_type_1_tbl[] =
        {
                0x04, 0x04, 0x0C, 0x0C, 0x0E, 0x0E, 0x0F, 0x0F, 0x0E, 0x0E,
                0x0C, 0x0C, 0xFF, 0x00, 0x00, 0x04, 0x04, 0x0C, 0x04, 0x04,
                0x00, 0x00, 0x02, 0x02, 0x0A, 0x02, 0x02, 0x00, 0x00, 0x01,
                0x01, 0x09, 0x01, 0x01, 0xFF, 0x00, 0x00, 0x08, 0x07, 0x0F,
                0x07, 0x08, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x04,
                0x0D, 0xFF
        };

unsigned char palette_anim_type_2_tbl[] =
        {
                0x00, 0x00, 0x04, 0x04, 0x0C, 0x04, 0x04, 0x00, 0x00, 0x02,
                0x02, 0x0A, 0x02, 0x02, 0x00, 0x00, 0x01, 0x01, 0x09, 0x01,
                0x01, 0xFF
        };

unsigned char palette_anim_type_3_tbl[] =
        {
                0x00, 0x00, 0x08, 0x07, 0x0F, 0x07, 0x08, 0xFF
        };

unsigned char palette_anim_type_4_tbl[] =
        {
                0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x04, 0x0D, 0xFF
        };



void palette_cycle_reg_5_from_tbl(unsigned char *palette_cycle_tbl_ptr)
{
    palette_index++;
    //FIXME need to hook up palette_2E1EE into this logic.

    if (palette_cycle_tbl_ptr[palette_index] == 0xff)
    {
        palette_index = 0;
    }

    if (palette_cycle_tbl_ptr[palette_index] >= 8)
    {
        set_palette_color(5, (char)(palette_cycle_tbl_ptr[palette_index] + 8));
    }
    else
    {
        set_palette_color(5, (char)palette_cycle_tbl_ptr[palette_index]);
    }

    return;
}

void update_palette_anim()
{
    switch (palette_anim_type - 1)
    {
        case 0:
            if (next_pal_colour == 2)
            {
                next_pal_colour = 0;
                set_palette_color(5, 0x10);
                return;
            }
            if (next_pal_colour == 1)
            {
                next_pal_colour = 2;
                set_palette_color(5, 7);
                return;
            }
            if (rand() % 0xffff >= 0x5dc)
            {
                set_palette_color(5, 0);
                next_pal_colour = 0;
            }
            else
            {
                set_palette_color(5, 7);//0x17);
                play_sfx(0x3c);
                next_pal_colour = 1;
            }
            break;

        case 1:
            palette_cycle_reg_5_from_tbl(palette_anim_type_1_tbl);
            break;

        case 2:
            palette_cycle_reg_5_from_tbl(palette_anim_type_2_tbl);
            break;

        case 3:
            palette_cycle_reg_5_from_tbl(palette_anim_type_3_tbl);
            break;

        case 4:
            palette_cycle_reg_5_from_tbl(palette_anim_type_4_tbl);
            break;
    }

    return;
}
