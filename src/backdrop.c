//
// Created by efry on 3/11/2017.
//

#include <stdio.h>
#include "backdrop.h"
#include "tile.h"
#include "map.h"
#include "video.h"

//Data
uint16 backdrop_index = 0xff;
uint8 background_x_scroll_flag = 0;
uint8 background_y_scroll_flag = 0;

const char backdrop_filename_tbl[][13] = {
        "BDBLANK.MNI",
        "BDPIPE.MNI",
        "BDREDSKY.MNI",
        "BDROCKTK.MNI",
        "BDJUNGLE.MNI",
        "BDSTAR.MNI",
        "BDWIERD.MNI",
        "BDCAVE.MNI",
        "BDICE.MNI",
        "BDSHRUM.MNI",
        "BDTECHMS.MNI",
        "BDNEWSKY.MNI",
        "BDSTAR2.MNI",
        "BDSTAR3.MNI",
        "BDFOREST.MNI",
        "BDMOUNTN.MNI",
        "BDGUTS.MNI",
        "BDBRKTEC.MNI",
        "BDCLOUDS.MNI",
        "BDFUTCTY.MNI",
        "BDICE2.MNI",
        "BDCLIFF.MNI",
        "BDSPOOKY.MNI",
        "BDCRYSTL.MNI",
        "BDCIRCUT.MNI",
        "BDCIRCPC.MNI"
};

Tile *bg_tiles;

void load_backdrop_image(const char *filename)
{
    uint32 num_tiles;
    bg_tiles = load_tiles(filename, SOLID, &num_tiles);
    printf("Loading %d background tiles.\n", num_tiles);
}

bool set_backdrop(uint16 new_backdrop_index)
{
    static uint8 cur_background_x_scroll_flag = 0;
    static uint8 cur_background_y_scroll_flag = 0;

    if (new_backdrop_index != backdrop_index ||
            cur_background_x_scroll_flag != background_x_scroll_flag ||
            cur_background_y_scroll_flag != background_y_scroll_flag)
    {
        backdrop_index = new_backdrop_index;
        cur_background_x_scroll_flag = background_x_scroll_flag;
        cur_background_y_scroll_flag = background_y_scroll_flag;

        load_backdrop_image(backdrop_filename_tbl[backdrop_index]);
    }

    return true;
}

void backdrop_display()
{
    for(int y=0; y < MAP_WINDOW_HEIGHT; y++)
    {
        for(int x=0; x < MAP_WINDOW_WIDTH; x++)
        {
            video_draw_tile(&bg_tiles[x + y * 40], (x+1)*8, (y+1)*8);
        }
    }
}