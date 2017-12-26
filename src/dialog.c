//
// Created by Eric Fry on 31/10/2017.
//


#include <sound/sfx.h>
#include <SDL_events.h>
#include <sound/music.h>
#include "game.h"
#include "dialog.h"
#include "input.h"
#include "video.h"
#include "map.h"
#include "font.h"
#include "player.h"
#include "actor.h"
#include "save.h"
#include "fullscreen_image.h"

//Data
uint8 show_one_moment_screen_flag = 0;
uint8 byte_28BE3 = 0;
uint8 byte_2E21C = 0;

int cleanup_and_exit();

SDL_Keycode wait_for_input(int spinner_x, int spinner_y)
{
    video_update();
    reset_player_control_inputs();

    uint16 spinner_idx = 0;
    SDL_Keycode keycode = poll_for_key_press();
    while(keycode == SDLK_UNKNOWN)
    {
        //Draw spinning cursor
        video_draw_tile(map_get_bg_tile(1987+spinner_idx), spinner_x * TILE_WIDTH, spinner_y * TILE_HEIGHT);
        video_update();
        if(spinner_idx == 3)
            spinner_idx = 0;
        else
            spinner_idx++;
        cosmo_wait(5);
        keycode = poll_for_key_press();
    }
    return keycode;
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
                video_update();
                display_char(x_pos + x, y_pos, c);
            }
            else
            {
                display_char(x_pos + x, y_pos, c);
            }
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
    }
    video_update();
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

int quit_game_dialog()
{
    uint16 x = create_text_dialog_box(11, 4, 0x12, "Are you sure you", "want to quit? ");
    if (wait_for_input(x + 14, 13) == SDLK_y)
    {
        return 1;
    }

    return 0;
}

void apogee_bbs_dialog()
{
    fade_to_black_speed_3();
    video_fill_screen_with_black();
    uint16 x = create_text_dialog_box(1, 0x16, 0x26, "THE OFFICIAL APOGEE BBS", "Press ANY key.");
    x =+ 3;
    display_dialog_text(x, 3, "    -----------------------");
    display_dialog_text(x, 5, "The SOFTWARE CREATIONS BBS is");
    display_dialog_text(x, 6, " the home BBS for the latest");
    display_dialog_text(x, 7, " Apogee games.  Check out our");
    display_dialog_text(x, 8, "FREE 'Apogee' file section for");
    display_dialog_text(x, 9, "  new releases and updates.");
    display_dialog_text(x, 11, "       BBS phone lines:");
    display_dialog_text(x, 13, "(508) 365-2359  2400 baud");
    display_dialog_text(x, 14, "(508) 365-9825  9600 baud");
    display_dialog_text(x, 15, "(508) 365-9668  14.4k dual HST");
    display_dialog_text(x, 0x11, "Home of the Apogee BBS Network!");
    display_dialog_text(x, 0x13, "    A Major Multi-Line BBS.");

    fade_in_from_black_with_delay_3();
    wait_for_input(x + 0x20, 0x15);
    fade_to_black_speed_3();
    video_fill_screen_with_black();

    x = create_text_dialog_box(0, 0x19, 0x28, "APOGEE ON AMERICA ONLINE! ", "Press ANY key.");
    display_dialog_text(x, 2, "      -------------------------");
    display_dialog_text(x, 4, "   America Online (AOL) is host of");
    display_dialog_text(x, 5, " the Apogee Forum, where you can get");
    display_dialog_text(x, 6, "   new Apogee games. Use the Apogee");
    display_dialog_text(x, 7, "  message areas to talk and exchange");
    display_dialog_text(x, 8, "   ideas, comments and secrets with");
    display_dialog_text(x, 9, "   our designers and other players.");
    display_dialog_text(x, 11, "  If you are already a member, after");
    display_dialog_text(x, 12, " you log on, use the keyword \"Apogee\"");
    display_dialog_text(x, 13, " (Ctrl-K) to jump to the Apogee area.");
    display_dialog_text(x, 15, "  If you'd like to know how to join,");
    display_dialog_text(x, 0x10, "        please call toll free:");
    display_dialog_text(x, 0x12, "            1-800-827-6364");
    display_dialog_text(x, 0x13, "    Please ask for extension 5703.");
    display_dialog_text(x, 0x15, "   You'll get the FREE startup kit.");

    fade_in_from_black_with_delay_3();
    wait_for_input(x + 0x25, 0x17);
}

void ordering_info_dialog()
{
    fade_to_black_speed_3();
    video_fill_screen_with_black();
    uint16 x = create_text_dialog_box(0, 0x18, 0x26, "Ordering Information", "Press ANY key.");
    display_dialog_text(x, 2, "  \xfe""223000                              ""\xfe""223000");
    display_dialog_text(x, 4, "      COSMO'S COSMIC ADVENTURE");
    display_dialog_text(x, 5, "    consists of three adventures.");
    display_dialog_text(x, 7, "    Only the first adventure is");
    display_dialog_text(x, 8, " available as shareware.  The final");
    display_dialog_text(x, 9, "   two amazing adventures must be");
    display_dialog_text(x, 10, "    purchased from Apogee, or an");
    display_dialog_text(x, 11, "          authorized dealer.");
    display_dialog_text(x, 13, "  The last two adventures of Cosmo");
    display_dialog_text(x, 14, "   feature exciting new graphics,");
    display_dialog_text(x, 15, "  new creatures, new puzzles, new");
    display_dialog_text(x, 0x10, "   music and all-new challenges!");
    display_dialog_text(x, 0x12, "    The next few screens provide");
    display_dialog_text(x, 0x13, "       ordering instructions.");
    display_dialog_text(x, 0x16, "  \xfe""155000                              ""\xfe""154001");
    fade_in_from_black(1);
    wait_for_input(x + 0x23, 0x16);
    fade_to_black(1);
    video_fill_screen_with_black();

    x = create_text_dialog_box(1, 0x16, 0x26, "Ordering Information", "Press ANY key.");
    display_dialog_text(x, 4, "       Order now and receive:");
    display_dialog_text(x, 6, "   * All three exciting adventures");
    display_dialog_text(x, 7, "   * The hints and tricks sheet");
    display_dialog_text(x, 8, "   * The Secret Cheat password");
    display_dialog_text(x, 9, "   * Exciting new bonus games");
    display_dialog_text(x, 11, "      To order, call toll free:");
    display_dialog_text(x, 12, "           1-800-426-3123");
    display_dialog_text(x, 13, "   (Visa and MasterCard Welcome)");
    display_dialog_text(x, 15, "   Order all three adventures for");
    display_dialog_text(x, 0x10, "     only $35, plus $4 shipping.");
    display_dialog_text(x, 0x13, "              \xfe""129002");
    display_dialog_text(x, 0x14, "  \xfb""014                          ""\xfb""015");
    fade_in_from_black(1);
    wait_for_input(x + 0x23, 0x15);
    fade_to_black(1);
    video_fill_screen_with_black();

    x = create_text_dialog_box(1, 0x16, 0x26, "Ordering Information", "Press ANY key.");
    display_dialog_text(x, 4, "      Please specify disk size:");
    display_dialog_text(x, 5, "           5.25\"  or  3.5\"");
    display_dialog_text(x, 7, "     To order send $35, plus $4");
    display_dialog_text(x, 8, "      shipping, USA funds, to:");
    display_dialog_text(x, 10, "           Apogee Software");
    display_dialog_text(x, 11, "           P.O. Box 476389");
    display_dialog_text(x, 12, "       Garland, TX 75047  (USA)");
    display_dialog_text(x, 14, "\xfe""101003       Or CALL NOW toll free:  ""\xfe""101000");
    display_dialog_text(x, 15, "           1-800-426-3123");
    display_dialog_text(x, 0x12, "         ORDER COSMO TODAY!");
    display_dialog_text(x, 0x13, "           All 3 for $39!");
    display_dialog_text(x, 0x14, "  \xfb""014                          ""\xfb""015");
    fade_in_from_black(1);
    wait_for_input(x + 0x23, 0x15);
    fade_to_black(1);
    video_fill_screen_with_black();

    x = create_text_dialog_box(4, 15, 0x26, "USE YOUR FAX MACHINE TO ORDER!", "Press ANY key.");
    display_dialog_text(x, 7, "  You can now use your FAX machine");
    display_dialog_text(x, 8, "   to order your favorite Apogee");
    display_dialog_text(x, 9, "     games quickly and easily.");
    display_dialog_text(x, 11, "   Simply print out the ORDER.FRM");
    display_dialog_text(x, 12, "    file, fill it out and FAX it");
    display_dialog_text(x, 13, "    to us for prompt processing.");
    display_dialog_text(x, 15, "     FAX Orders: (214) 278-4670");
    fade_in_from_black(1);
    wait_for_input(x + 0x23, 0x11);
    fade_to_black(1);
    video_fill_screen_with_black();

    x = create_text_dialog_box(1, 0x14, 0x26, "About Apogee Software", "Press ANY key.");
    x += 2;
    display_dialog_text(x, 4, "Our goal is to establish Apogee");
    display_dialog_text(x, 5, "  as the leader in commercial");
    display_dialog_text(x, 6, " quality shareware games. With");
    display_dialog_text(x, 7, " enthusiasm and dedication we");
    display_dialog_text(x, 8, "think our goal can be achieved.");
    display_dialog_text(x, 10, "However,  we need your support.");
    display_dialog_text(x, 11, "Shareware is not free software.");
    display_dialog_text(x, 13, "  We thank you in advance for");
    display_dialog_text(x, 14, "   your contribution to the");
    display_dialog_text(x, 15, "  growing shareware community.");
    display_dialog_text(x - 2, 0x11, "\xfd""010        Your honesty pays...     ""\xfd""033");
    fade_in_from_black(1);
    wait_for_input(x + 0x21, 0x13);
}

void main_menu_dialog()
{
    uint16 si = create_text_dialog_box(2, 0x15, 0x14, "MAIN MENU", "");
    display_dialog_text(si, 5, " B)egin New Game");
    display_dialog_text(si, 6, " R)estore A Game");
    display_dialog_text(si, 7, " S)tory");
    display_dialog_text(si, 8, " I)nstructions");
    display_dialog_text(si, 9, " H)igh Scores");
    display_dialog_text(si, 10, " G)ame Redefine");
    display_dialog_text(si, 12, " O)rdering Info.");
    display_dialog_text(si, 14, " F)oreign Orders");
    display_dialog_text(si, 15, " A)pogee's BBS");
    display_dialog_text(si, 0x10, " D)emo");
    display_dialog_text(si, 0x11, " C)redits");
    display_dialog_text(si, 0x12, " T)itle Screen");
    display_dialog_text(si, 0x14, " Q)uit Game");
}

game_play_mode_enum main_menu() {
    set_initial_game_state();
    show_one_moment_screen_flag = 0;
    load_music(0x12);
    display_fullscreen_image(1);

    for(int i=0;;i+=3)
    {
        SDL_Keycode key = poll_for_key_press();
        if(key != SDLK_UNKNOWN)
        {
            if (key == SDLK_q || key == SDLK_ESCAPE)
            {
                if (quit_game_dialog())
                {
                    return QUIT_GAME;
                }
            }

            for(int return_to_title=0;!return_to_title;)
            {
                main_menu_dialog();
                key = wait_for_input(0x1c, 0x15);
                switch(key)
                {
                    case SDLK_ESCAPE :
                    case SDLK_q :
                        if(quit_game_dialog())
                        {
                            return QUIT_GAME;
                        }
                        break;

                    case SDLK_RETURN :
                    case SDLK_b :
                    case SDLK_SPACE :
                        stop_music();
                        return PLAY_GAME;

                    case SDLK_F11 :
                        if (cheat_mode_flag)
                        {
                            return RECORD_DEMO;
                        }
                        break;

                    case SDLK_o :
                        ordering_info_dialog();
                        break;

                    case SDLK_a :
                        apogee_bbs_dialog();
                        break;

                    case SDLK_d :
                        return PLAY_DEMO;

                    case SDLK_c :
                        display_fullscreen_image(2);
                        while(poll_for_key_press()==SDLK_UNKNOWN)
                        {}
                        break;

                    case SDLK_t :
                        return_to_title = 1;
                        break;

                    default : break;
                }

                display_fullscreen_image(1);
            }
        }
        else
        {
            if(i==600)
            {
                display_fullscreen_image(2);
            }
            if(i == 1200)
            {
                return PLAY_DEMO;
            }
        }
        cosmo_wait(3);
    }
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
    for(int cur_y = var_4;cur_y >= ((height & 1) ? 1 : 2) + y_offset; cur_y--)
    {
        cur_height += 2;
        draw_dialog_frame(dialog_x, cur_y, cur_height, width, "", "", 0);
        cosmo_wait(1);
    }

    return draw_dialog_frame(dialog_x, y_offset, height, width, top_message, bottom_message, 1);
}

void savegame_dialog()
{
    uint16 x = create_text_dialog_box(8, 10, 0x1c, "Save a game.", "Press ESC to quit.");
    display_dialog_text(x, 11, " What game number (1-9)?");
    display_dialog_text(x, 13, " NOTE: Game is saved at");
    display_dialog_text(x, 14, " BEGINNING of level.");
    SDL_Keycode keycode = wait_for_input(x + 0x18, 11);
    if(keycode == SDLK_ESCAPE || keycode == SDLK_SPACE || keycode == SDLK_RETURN)
    {
        return;
    }

    if(keycode >= SDLK_1 && keycode <= SDLK_9)
    {
        display_char(x + 0x18, 11, keycode);
        int tmp_num_bombs = num_bombs;
        uint16 tmp_num_stars_collected = num_stars_collected;
        uint16 tmp_current_level = current_level;
        uint8 tmp_num_health_bars = num_health_bars;
        uint32 tmp_score = score;
        uint8 tmp_health = health;

        load_savegame_file('T');
        write_savegame_file(keycode);

        health = tmp_health;
        num_bombs = tmp_num_bombs;
        //FIXME is this needed? word_2E1D6 = 0;
        num_stars_collected = tmp_num_stars_collected;
        current_level = tmp_current_level;
        score = tmp_score;
        num_health_bars = tmp_num_health_bars;
        x = create_text_dialog_box(7, 4, 0x14, "Game Saved.", "Press ANY key.");
        wait_for_input(x + 0x11, 9);
    }
    else
    {
        x = create_text_dialog_box(11, 4, 0x1c, "Invalid game number!", "Press ANY key.");
        wait_for_input(x + 0x19, 13);
    }
}

uint16 restore_savegame_dialog()
{
    uint16 x = create_text_dialog_box(11, 7, 0x1c, "Restore a game.", "Press ESC to quit.");
    display_dialog_text(x, 14, " What game number (1-9)?");
    SDL_Keycode character = wait_for_input(x + 0x18, 14);
    if(character != SDLK_ESCAPE && character != SDLK_SPACE && character != SDLK_RETURN)
    {
        if(character >= SDLK_1 && character <= SDLK_9)
        {
            display_char(x + 0x18, 14, character);
            if(load_savegame_file(character))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        x = create_text_dialog_box(11, 4, 0x1c, "Invalid game number!", "Press ANY key.");
        wait_for_input(x + 0x19, 13);
    }
    return 2;
}

void game_redefine()
{
    //FIXME
}

void missing_savegame_dialog()
{
    //FIXME
}

void hall_of_fame_dialog()
{
    //FIXME
}

void cosmic_hints_dialog(uint16 y_pos)
{
    //FIXME
}

void malformed_savegame_dialog()
{
    uint16 x = create_text_dialog_box(2, 4, 0x1c, "Altered file error!!", "Now exiting game!");
    wait_for_input(x + 0x19, 4);
}

uint16 help_menu_dialog()
{
    uint16 si = create_text_dialog_box(2, 12, 0x16, "HELP MENU", "Press ESC to quit.");
    display_dialog_text(si, 5, " S)ave your game");
    display_dialog_text(si, 6, " R)estore a game");
    display_dialog_text(si, 7, " H)elp");
    display_dialog_text(si, 8, " G)ame redefine");
    display_dialog_text(si, 9, " V)iew High Scores");
    display_dialog_text(si, 10, " Q)uit Game");

    for(;;)
    {
        uint16 status = 0;
        switch (wait_for_input(0x1d, 12))
        {
            case SDLK_g:
                game_redefine();
                return 0;

            case SDLK_s:
                savegame_dialog();
                return 0;

            case SDLK_r:
                status = restore_savegame_dialog();
                if(status == 1)
                {
                    load_level(current_level);
                    return 1;
                }
                if(status == 0)
                {
                    missing_savegame_dialog();
                }
                return 0;

            case SDLK_v:
                hall_of_fame_dialog();
                return 0;

            case SDLK_q:
                return 2;

            case SDLK_h:
                cosmic_hints_dialog(1);
                return 0;

            case SDLK_ESCAPE:
                return 0;

            default: break;
        }
    }
}

void a_game_by_dialog()
{
    uint16 si = create_text_dialog_box(4, 13, 0x1a, "A game by", "Copyright (c) 1992");
    display_dialog_text(si, 7, "     Todd J Replogle");
    display_dialog_text(si + 11, 9, "and");
    display_dialog_text(si, 11, "\xfd""027   Stephen A Hornback""\xfd""004");
    display_dialog_text(si, 13, "      Version 1.20");
    wait_for_time_or_key(0x2bc);
    fade_to_black_speed_3();
}
