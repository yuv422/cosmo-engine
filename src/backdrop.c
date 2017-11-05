//
// Created by efry on 3/11/2017.
//

#include "backdrop.h"

//Data
uint16 backdrop_index = 0xff;
uint8 background_x_scroll_flag = 0;
uint8 background_y_scroll_flag = 0;

const char backdrop_filename_tbl[][12] = {
        "bdblank.mni",
        "bdpipe.MNI",
        "bdredsky.MNI",
        "bdrocktk.MNI",
        "bdjungle.MNI",
        "bdstar.MNI",
        "bdwierd.mni",
        "bdcave.mni",
        "bdice.mni",
        "bdshrum.mni",
        "bdtechms.mni",
        "bdnewsky.mni",
        "bdstar2.mni",
        "bdstar3.mni",
        "bdforest.mni",
        "bdmountn.mni",
        "bdguts.mni",
        "bdbrktec.mni",
        "bdclouds.mni",
        "bdfutcty.mni",
        "bdice2.mni",
        "bdcliff.mni",
        "bdspooky.mni",
        "bdcrystl.mni",
        "bdcircut.mni",
        "bdcircpc.mni"
};

void load_backdrop_image(const char *filename)
{

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
