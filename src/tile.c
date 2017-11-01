//
// Created by Eric Fry on 31/10/2017.
//

#include "game.h"
#include "tile.h"

uint8 tileattr_mni_data[7000];

void tile_attr_load()
{
    load_file("TILEATTR.MNI", (unsigned char *)&tileattr_mni_data, 7000);
}
