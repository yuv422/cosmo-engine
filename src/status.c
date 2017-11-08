//
// Created by Eric Fry on 8/11/2017.
//

#include <stdio.h>
#include "status.h"
#include "defines.h"
#include "tile.h"
#include "video.h"
#include "map.h"

Tile *status_tiles;

void status_load_tiles() {
    uint16 num_tiles;
    status_tiles = load_tiles("STATUS.MNI", SOLID, &num_tiles);
    printf("Loading %d status tiles.\n", num_tiles);
}

void status_display()
{
    for(int y=0; y < STATUS_BAR_HEIGHT; y++)
    {
        for (int x = 0; x < STATUS_BAR_WIDTH; x++)
        {
            video_draw_tile(&status_tiles[x + y * STATUS_BAR_WIDTH], (x + 1) * TILE_WIDTH, (y+MAP_WINDOW_HEIGHT+1) * TILE_HEIGHT);
        }
    }
}
