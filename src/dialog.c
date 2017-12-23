//
// Created by Eric Fry on 31/10/2017.
//


#include <sound/sfx.h>
#include <SDL_events.h>
#include "game.h"
#include "dialog.h"
#include "input.h"
#include "video.h"
#include "map.h"
#include "font.h"
#include "player.h"
#include "actor.h"

//Data
uint8 show_one_moment_screen_flag = 0;
uint8 byte_28BE3 = 0;
uint8 byte_2E21C = 0;

void wait_for_input(int spinner_x, int spinner_y)
{
    video_update();
    reset_player_control_inputs();

    uint16 spinner_idx = 0;
    while(!poll_for_key_press())
    {
        //Draw spinning cursor
        video_draw_tile(map_get_bg_tile(1987+spinner_idx), spinner_x * TILE_WIDTH, spinner_y * TILE_HEIGHT);
        video_update();
        if(spinner_idx == 3)
            spinner_idx = 0;
        else
            spinner_idx++;
        cosmo_wait(5);
    }
}

void display_cartoon_sequence(uint16 frame_num, uint16 x_pos, uint16 y_pos)
{
    //FIXME this should probably be in its own file.
}

uint16 dialog_text_extract_num(const char *text)
{
    char buf[4];

    buf[0] = text[0];
    buf[1] = text[1];
    buf[2] = text[2];
    buf[3] = 0;

    return (uint16)strtol(buf, NULL, 10);
}

typedef enum {
    FAST_FORWARD,
    EXIT,
    NO_INPUT
} HintDialogInput;

HintDialogInput hint_dialog_get_input(HintDialogInput input)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_SPACE)
            {
                return FAST_FORWARD;
            }
            else
            {
                return EXIT;
            }
        }
        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
        {
            return NO_INPUT;
        }
    }

    return input;
}

void display_dialog_text(uint16 x_pos, uint16 y_pos, const char *text)
{
    HintDialogInput input = NO_INPUT;
    uint16 typewriter_keys_count = 0;
    uint16 typewriter_delay_counter = 0;
    int len = strlen(text);
    int x=0;
    for(int i=0; i < len; i++)
    {
        unsigned char c = (unsigned char)text[i];
        if(c == '\n')
        {
            x = 0;
            y_pos++;
            continue;
        }

        if(c < 123)
        {
            if (typewriter_delay_counter > 0)
            {
                input = hint_dialog_get_input(input);

                if(input == FAST_FORWARD)
                {
                    cosmo_wait(1);
                }
                else
                {
                    if(input == NO_INPUT)
                    {
                        for(; typewriter_keys_count > 0; typewriter_keys_count--)
                        {
                            cosmo_wait(3);
                        }
                    }
                }

                typewriter_keys_count = typewriter_delay_counter;
                if (c != 0x20)
                {
                    play_sfx(0x2c);
                }
            }
            display_char(x_pos + x, y_pos, c);
            x++;
        }
        if(c >= 0xfb && c < 0xff)
        {
            uint16 frame_num = dialog_text_extract_num(&text[i+1]);
            switch(c)
            {
                case 0xfb : display_cartoon_sequence(frame_num, x_pos + x, y_pos); break;
                case 0xfc :
                    typewriter_keys_count = frame_num;
                    typewriter_delay_counter = frame_num;
                    break;
                case 0xfd : display_player_sprite(frame_num, x_pos + x, y_pos, 6); break;
                case 0xfe :
                    display_actor_sprite_maybe(frame_num, dialog_text_extract_num(&text[i+4]), x_pos + x - 1, y_pos, 6);
                    i += 3;
                    break;
            }
            i += 3;
        }
        video_update();

    }
}

void you_havent_found_any_bombs_dialog() {
    if(game_play_mode == PLAY_GAME)
    {
        play_sfx(0x1e);
        uint16 x = create_text_dialog_box(2, 4, 0x1c, "", "");
        x++;
        display_dialog_text(x, 3, "You haven't found any");
        display_dialog_text(x, 4, "bombs to use yet!     \xfe""056000");
        cosmo_wait(0x3c);
        wait_for_input(x-1 + 0x19, 4);
    }
}

void monster_attack_hint_dialog()
{
    if(game_play_mode == PLAY_GAME)
    {
        play_sfx(0x1e);
        uint16 si = create_text_dialog_box(2, 5, 0x16, "REMINDER:  Jump on", "defend yourself.  ");
        display_dialog_text(si, 4, " top of creatures to");
        cosmo_wait(0x3c);
        wait_for_input(si + 0x13, 5);
        si = create_text_dialog_box(2, 13, 0x14, "Like this...", "Press ANY key.");
        display_dialog_text(si + 5, 9, "   \xfd""036");
        display_dialog_text(si + 5, 11, "   \xfe""118000");
        cosmo_wait(0x3c);
        wait_for_input(si + 0x11, 13);
    }
}

game_play_mode_enum main_menu() {
    set_initial_game_state();
    return PLAY_GAME;
}

const static uint8 level_numbers_tbl[] ={ 1, 2, 0, 0, 3, 4, 0, 0, 5, 6, 0, 0, 7, 8, 0, 0, 9, 10 };
void now_entering_level_n_dialog(uint16 level_number)
{
    if(game_play_mode == 0)
    {
        uint16 x = create_text_dialog_box(7, 3, 0x18, "\xfc""003  Now entering level", "");
        cosmo_wait(0x14);
        play_sfx(0x40);
        if(level_number != 10)
        {
            display_number(x + 0x14, 8, level_numbers_tbl[level_number]);
        }
        else
        {
            display_number(x + 0x15, 8, level_numbers_tbl[level_number]);
        }
        video_update();
    }
}

void ingame_hint_dialogs(uint16 hint_number) {
    cosmo_wait(0x1e);
    uint16 x;
    if(hint_number != 0 && hint_number < 15)
    {
        x = create_text_dialog_box(2, 9, 0x1c, "COSMIC HINT!", "Press any key to exit.");
        display_dialog_text(x, 8, " Press SPACE to hurry or");
    }

    switch (hint_number)
    {
        case 0:
            x = create_text_dialog_box(2, 11, 0x1c, "COSMIC HINT!", "Press any key to exit.");
            display_dialog_text(x, 10, " Press SPACE to hurry or");
            display_dialog_text(x, 5, "\xfc""003 These hint globes will\n"
                                               " help you along your\n"
                                               " journey.  Press the up\n"
                                               " key to reread them");

            wait_for_input(x + 0x19, 11);
            break;

        case 1:
            display_dialog_text(x, 5, "\xfc""003 Bump head into switch\n above!");
            break;

        case 2:
            display_dialog_text(x, 5, "\xfc""003 The ice in this cave is\n very, very slippery.");
            break;

        case 3:
            display_dialog_text(x, 5, "\xfc""003 Use this shield for\n temporary invincibility.");
            break;

        case 4:
            display_dialog_text(x, 5, "\xfc""003 You found a secret\n area!!!  Good job!");
            break;

        case 5:
            display_dialog_text(x, 5, "\xfc""003 In high places look up\n to find bonus objects.");
            break;

        case 6:
            display_dialog_text(x, 5, "\xfc""003      Out of Order...");
            break;

        case 7:
            display_dialog_text(x, 5, "\xfc""003 This might be a good\n time to save your game!");
            break;

        case 8:
            display_dialog_text(x, 5, "\xfc""003 Press your up key to\n use the transporter.");
            break;

        case 9:
            display_dialog_text(x, 5, "\xfc""003  (1) FOR...");
            break;

        case 10:
            display_dialog_text(x, 5, "\xfc""003  (2) EXTRA...");
            break;

        case 11:
            display_dialog_text(x, 5, "\xfc""003  (3) POINTS,...");
            break;

        case 12:
            display_dialog_text(x, 5, "\xfc""003  (4) DESTROY...");
            break;

        case 13:
            display_dialog_text(x, 5, "\xfc""003  (5) HINT...");
            break;

        case 14:
            display_dialog_text(x, 5, "\xfc""003  (6) GLOBES!!!");
            break;

        case 15:
            x = create_text_dialog_box(2, 11, 0x1c, "COSMIC HINT!", "Press any key to exit.");
            display_dialog_text(x + 0x16, 8, "\xfe""083000");
            display_dialog_text(x, 10, " Press SPACE to hurry or");
            display_dialog_text(x, 5, "\xfc""003  The Clam Plants won't\n  hurt you if their\n  mouths are closed.");
            wait_for_input(x + 0x19, 11);
            break;

        case 16:
            x = create_text_dialog_box(2, 10, 0x1c, "COSMIC HINT!", "Press any key to exit.");
            display_dialog_text(x, 9, " Press SPACE to hurry or");
            display_dialog_text(x + 0x17, 7, "\xfe""001002\n  Collect the STARS to\n  advance to BONUS\n  STAGES.");
            wait_for_input(x + 0x19, 10);
            break;

        case 17:
            x = create_text_dialog_box(2, 10, 0x1c, "COSMIC HINT!", "Press any key to exit.");
            display_dialog_text(x, 9, " Press SPACE to hurry or");
            display_dialog_text(x, 5, "\xfc""003  Some creatures require\n  more than one pounce\n  to defeat!");
            wait_for_input(x + 0x19, 10);
            break;

        case 18:
            x = create_text_dialog_box(2, 9, 0x1e, "COSMIC HINT!", "Press any key to exit.");
            display_dialog_text(x + 0x19, 8, "\xfd""032");
            display_dialog_text(x, 8, "  Press SPACE to hurry or");
            display_dialog_text(x, 5, "\xfc""003 Cosmo can climb wall's\n with his suction hands.");
            wait_for_input(x + 0x1b, 9);
            break;
    }

    if(hint_number != 0 && hint_number < 15)
    {
        wait_for_input(x + 0x19, 9);
    }
}

void power_up_module_dialog()
{
    if(game_play_mode == PLAY_GAME)
    {
        play_sfx(0x1e);
        int si = create_text_dialog_box(2, 5, 0x16, "", "");
        display_dialog_text(si, 3, " Power Up modules");
        display_dialog_text(si, 4, " increase Cosmo's");
        display_dialog_text(si, 5, " health.         \xfe""028002");
        cosmo_wait(0x3c);
        wait_for_input(si + 8, 5);
    }
}

void display_end_of_level_score_dialog(const char *header_text, const char *footer_text)
{
    fade_to_black_speed_3();
    video_fill_screen_with_black();
    uint16 x = create_text_dialog_box(6, 4, 0x1e, header_text, footer_text);
    fade_in_from_black_with_delay_3();
    wait_for_input(x + 0x1b, 8);
//  FIXME  display_score_from_level();
    fade_to_black_speed_3();
    video_fill_screen_with_black();
}

void end_game_dialog(uint16 dialog_number) {
    //TODO
}

uint16 draw_dialog_frame(uint16 x_pos, uint16 y_pos, uint16 height, uint16 width, const char *top_text, const char *bottom_text, uint8 display_text)
{
    video_draw_tile(map_get_bg_tile(1991), x_pos * TILE_WIDTH, y_pos * TILE_HEIGHT);
    video_draw_tile(map_get_bg_tile(1992), (x_pos + width-1) * TILE_WIDTH, y_pos * TILE_HEIGHT);

    for(int x=1;x < width-1;x++)
    {
        video_draw_tile(map_get_bg_tile(1995), (x_pos + x) * TILE_WIDTH, y_pos * TILE_HEIGHT);
        video_draw_tile(map_get_bg_tile(1996), (x_pos + x) * TILE_WIDTH, (y_pos + height-1) * TILE_HEIGHT);

        for(int y=1;y < height-1;y++)
        {
            video_draw_tile(map_get_bg_tile(1997), x_pos * TILE_WIDTH, (y_pos + y) * TILE_HEIGHT);
            video_draw_tile(map_get_bg_tile(1998), (x_pos + width-1) * TILE_WIDTH, (y_pos + y) * TILE_HEIGHT);

            for(int x1=1;x1 < width-1;x1++)
            {
                video_draw_tile(map_get_bg_tile(1999), (x_pos + x1) * TILE_WIDTH, (y_pos + y) * TILE_HEIGHT);
            }
        }
    }

    video_draw_tile(map_get_bg_tile(1993), x_pos * TILE_WIDTH, (y_pos + height-1) * TILE_HEIGHT);
    video_draw_tile(map_get_bg_tile(1994), (x_pos + width-1) * TILE_WIDTH, (y_pos + height-1) * TILE_HEIGHT);

    if(display_text)
    {
        display_dialog_text(0x14 - (strlen(top_text)/2), y_pos + 1, top_text);
        display_dialog_text(0x14 - (strlen(bottom_text)/2), y_pos + height - 2, bottom_text);
    }

    video_update();
    return x_pos + 1;
}

uint16 create_text_dialog_box(uint16 y_offset, uint16 height, uint16 width, const char *top_message, const char *bottom_message)
{
    int dialog_x = 0x14 - (width / 2);
    int var_4 = (height / 2) + y_offset;
    int cur_width = 1;
    for(int cur_x = 0x13; cur_x > dialog_x; cur_x--)
    {
        cur_width = cur_width + 2;
        draw_dialog_frame(cur_x, var_4, 2, cur_width, "", "", 0);
        cosmo_wait(1);
    }

    int cur_height = 0;
    for(int cur_y = var_4;cur_y >= (height & 1) + y_offset; cur_y--)
    {
        cur_height += 2;
        draw_dialog_frame(dialog_x, cur_y, cur_height, width, "", "", 0);
        cosmo_wait(1);
    }

    return draw_dialog_frame(dialog_x, y_offset, height, width, top_message, bottom_message, 1);
}

