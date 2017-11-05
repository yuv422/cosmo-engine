//
// Created by efry on 30/10/2017.
//

#include <stdio.h>
#include <files/file.h>
#include "input.h"
#include "backdrop.h"
#include "game.h"
#include "video.h"
#include "map.h"
#include "music.h"
#include "dialog.h"
#include "palette.h"
#include "player.h"
#include "save.h"

//Data
uint16 current_level;

int map_width_in_tiles = 0;
int map_stride_bit_shift_amt;
int mapwindow_x_offset = 0;
int mapwindow_y_offset = 0;

uint8 rain_flag = 0;


int map_get_tile_cell(int x, int y) {
    return 0;
}

const char level_filename_tbl[][12] = {
        "A1.MNI",
        "A2.MNI",
        "BONUS1.MNI",
        "BONUS2.MNI",
        "A3.MNI",
        "A4.MNI",
        "BONUS1.MNI",
        "BONUS2.MNI",
        "A5.MNI",
        "A6.MNI",
        "BONUS1.MNI",
        "BONUS2.MNI",
        "A7.MNI",
        "A8.MNI",
        "BONUS1.MNI",
        "BONUS2.MNI",
        "A9.MNI",
        "A10.MNI",
        "BONUS1.MNI",
        "BONUS2.MNI",
        "A11.MNI",
        "A12.MNI",
        "BONUS1.MNI",
        "BONUS2.MNI",
        "A13.MNI",
        "A14.MNI",
        "BONUS1.MNI",
        "BONUS2.MNI",
        "A15.MNI",
        "A16.MNI"
};

void load_level_data(int level_number);

void load_level(int level_number)
{
    if (level_number != 0 || show_one_moment_screen_flag == 0) {
        fade_to_black_speed_3();
    } else {
        display_fullscreen_image(5);
        wait_for_time_or_key(0x12c);
    }

    uint32 filesize;
    File map_file;
    if(!open_file(level_filename_tbl[level_number], &map_file))
    {
        printf("Error: loading level data. %s\n", level_filename_tbl[level_number]);
        return;
    }

    uint16 level_flags = file_read2(&map_file);
    file_close(&map_file);

    music_related_229C7();
    rain_flag = (uint8)(level_flags & 0x20);
    uint16 backdrop_index = (uint16)(level_flags & 0x1f);
    background_x_scroll_flag = (uint8)(level_flags & 0x40);
    background_y_scroll_flag = (uint8)(level_flags & 0x80);

    palette_anim_type = (uint8)(level_flags >> 8 & 7);
    music_index = (uint16)((level_flags >> 11) & 0x1f);

    printf("Level %d: rain=%d, backdrop_index=%d, bg_x_scroll=%d, bg_y_scroll=%d, pal_anim_type=%d, music_index=%d\n", current_level, rain_flag, backdrop_index, background_x_scroll_flag, background_y_scroll_flag, palette_anim_type, music_index);
    reset_game_state();

    set_backdrop(backdrop_index);

    load_level_data(level_number);

    if (level_number == 0 && show_one_moment_screen_flag != 0) {
        fade_to_black_speed_3();
        show_one_moment_screen_flag = 0;
    }
    if (game_play_mode == 0) {
        switch (level_number) {
            case 0:
            case 1:
            case 4:
            case 5:
            case 8:
            case 9:
            case 12:
            case 13:
            case 16:
            case 17:
                //update_ega_mem_ptr(0);
                //set_display_page(0);
/* Low-level instruction of type call    )(00020FDDsub_20FDD)       ; video memory copy maybe */
                update_palette_related_delay_3();
                now_entering_level_n_dialog(level_number);
                wait_for_time_or_key(0x96);
                fade_to_black_speed_3();
                break;
            default:
                break;
        }
    }
    struct4_clear_sprites();
    struct6_clear_sprites();
    struct7_clear_sprites();
    player_reset_push_variables();
    struct5_clear_sprites();
    load_status_panel_into_video_mem();
//    update_ega_mem_ptr(ega_page_index_maybe);
//    ax = (ega_page_index_maybe ? -1 : 0) + 1;
//    ega_page_index_maybe = ax;
//    set_display_page(ax);
    write_savegame_file('T');
    load_music(music_index);


    //I Don't think this will be needed.

//    if (byte_32FEA == 0) {
//        gvar_32D12 = REGISTER_29;
//        tileattr_mni_data = &ptr + 0x1388;
//        word_28BE4 = 0x1111;
//        load_tileattr_mni("TILEATTR.MNI", REGISTER_32);
//    }

    update_palette_related_delay_3();
    return;
}

void load_level_data(int level_number)
{
    //FIXME
}