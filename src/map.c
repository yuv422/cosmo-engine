//
// Created by efry on 30/10/2017.
//

#include "map.h"

int map_width_in_tiles = 0;
int map_stride_bit_shift_amt;
int mapwindow_x_offset = 0;
int mapwindow_y_offset = 0;

int map_get_tile_cell(int x, int y) {
    return 0;
}

const char level_filename_tbl[][12] = {
        "A1.MNI",
        "A2.MNI",
        "bonus1.mni",
        "bonus2.mni",
        "A3.mni",
        "A4.mni",
        "bonus1.mni",
        "bonus2.mni",
        "A5.mni",
        "A6.mni",
        "bonus1.mni",
        "bonus2.mni",
        "A7.mni",
        "A8.mni",
        "bonus1.mni",
        "bonus2.mni",
        "A9.mni",
        "A10.mni",
        "bonus1.mni",
        "bonus2.mni",
        "A11.mni",
        "A12.mni",
        "bonus1.mni",
        "bonus2.mni",
        "A13.mni",
        "A14.mni",
        "bonus1.mni",
        "bonus2.mni",
        "A15.mni",
        "A16.mni"
};

void load_level(int level_number) {
// node 000206b7-00020878 #insn=39 use={} def={si} in={} out={} pred={} RETURN
/* push si */
    si = level_number;
    if (si != 0 || show_one_moment_screen_flag == 0) {
        fade_to_black_speed_3();
    } else {
        display_fullscreen_image(5);
        wait_for_time_or_key(0x12c);
    }
    bx = si << 2;
    ax = open_cosmo_resource_file(*(bx + level_filename_tbl), *(bx + ));
    stream[2] = dx;
    stream = ax;
    level_flags = _getw(ax, dx);
    _fclose(stream, stream[2]);
    music_related_229C7();
    rain_flag = level_flags & 0x20;
    di = level_flags & 0x1f;
    background_x_scroll_flag = level_flags & 0x40;
    background_y_scroll_flag = level_flags & 0x80;
    al = al & 7;
    palette_anim_type = al;
    music_index = level_flags >> 11 & 0x1f;
    reset_game_state();
    set_backdrop(di);
    if (al != 0) {
        bx = di << 2;
        load_backdrop_image(*(bx + backdrop_filename_tbl), *(bx + ), temp_data_buffer, gvar_2E43A);
    }
    load_level_data(si);
    if (si == 0 && show_one_moment_screen_flag != 0) {
        fade_to_black_speed_3();
        show_one_moment_screen_flag = 0;
    }
    if (game_play_mode == 0) {
        switch (si) {
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
                update_ega_mem_ptr(0);
                set_display_page(0);
/* Low-level instruction of type call    )(00020FDDsub_20FDD)       ; video memory copy maybe */
                update_palette_related_delay_3();
                now_entering_level_n_dialog(si);
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
    update_ega_mem_ptr(ega_page_index_maybe);
    ax = (ega_page_index_maybe ? -1 : 0) + 1;
    ega_page_index_maybe = ax;
    set_display_page(ax);
    write_savegame_file(0x54);
    load_music(music_index);
    if (byte_32FEA == 0) {
        gvar_32D12 = REGISTER_29;
        tileattr_mni_data = &ptr + 0x1388;
        word_28BE4 = 0x1111;
        load_tileattr_mni("TILEATTR.MNI", REGISTER_32);
        return ax;
    }
    update_palette_related_delay_3(di);
    return;
}