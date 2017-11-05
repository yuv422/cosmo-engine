//
// Created by efry on 3/11/2017.
//

#include "defines.h"

#ifndef COSMO_ENGINE_VIDEO_H
#define COSMO_ENGINE_VIDEO_H

void display_fullscreen_image(uint8 image_number);
void fade_to_black_speed_3();
void load_status_panel_into_video_mem();


//FIXME where should these functions live?
void struct4_clear_sprites();
void struct5_clear_sprites();
void struct6_clear_sprites();
void struct7_clear_sprites();

#endif //COSMO_ENGINE_VIDEO_H
