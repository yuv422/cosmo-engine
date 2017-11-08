//
// Created by Eric Fry on 31/10/2017.
//

#include <files/file.h>
#include <stdlib.h>
#include "game.h"
#include "tile.h"

uint8 tileattr_mni_data[7000];

void tile_attr_load()
{
    load_file("TILEATTR.MNI", (unsigned char *)&tileattr_mni_data, 7000);
}
uint8 get_tile_size(TileType type)
{
    return type == SOLID ? (uint8)32 : (uint8)40;
}
uint16 get_number_of_tiles(File *file, TileType type)
{
    uint8 tile_size = get_tile_size(type);

    uint16 num_tiles = 0;
    uint32 filesize = file->size;
    while(filesize > 0xffff)
    {
        num_tiles += 0xffff / tile_size;
        filesize -= 0xffff;
    }

    if(filesize > 0)
    {
        num_tiles += filesize / tile_size;
    }

    return num_tiles;
}

uint8 getPixelAtColumnPosition(uint8 *rowPtr, uint8 column, TileType tileType)
{
    uint8 color = 0;

    if (tileType == TRANSPARENT) {
        if (*rowPtr & (1 << (7 - column))) {
            return TRANSPARENT_COLOR;
        }
        rowPtr++;
    }

    for (int i = 0; i < 4; i++, rowPtr++) {

        color |= (((*rowPtr >> (7 - column)) & 1) << (i));
    }

    return color;
}

void load_tile(uint8 *planarData, TileType type, Tile *tile)
{
    tile->type = type;
    uint8 *pixelPtr = tile->pixels;

    for(uint8 y=0;y<TILE_HEIGHT;y++) {
        for(uint8 x=0;x<TILE_WIDTH;x++) {
            *pixelPtr = getPixelAtColumnPosition(planarData, x, type);
            pixelPtr++;
        }
        planarData += type == SOLID ? (uint8)4 : (uint8)5;
    }
}

Tile *load_tiles(const char *filename, TileType type, uint16 *num_tiles_loaded) {
    uint8 planarData[40];

    File file;
    if(!open_file(filename, &file))
    {
        printf("Error: opening %s\n", filename);
        return NULL;
    }

    uint8 tile_size = get_tile_size(type);

    uint16 num_tiles = get_number_of_tiles(&file, type);
    Tile *tiles = (Tile *)malloc(sizeof(Tile) * num_tiles);


    for(int i=0;i<num_tiles;i++)
    {
        file_read_to_buffer(&file, planarData, tile_size);
        load_tile(planarData, type, &tiles[i]);
        if(i % (0xffff / num_tiles) == 0)
        {
            file_seek(&file, file.pos + (0xffff % num_tiles));
        }
    }

    *num_tiles_loaded = num_tiles;
    return tiles;
}
