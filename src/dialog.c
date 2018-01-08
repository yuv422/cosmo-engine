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
#include "cartoon.h"
#include "high_scores.h"

//Data
uint8 show_one_moment_screen_flag = 0;
uint8 byte_28BE3 = 0;
uint8 byte_2E21C = 0;

int cleanup_and_exit();
uint16 restore_savegame_dialog();

SDL_Keycode wait_for_input_with_repeat(int spinner_x, int spinner_y, bool allow_key_repeat)
{
    video_update();
    reset_player_control_inputs();

    uint16 spinner_idx = 0;
    SDL_Keycode keycode = poll_for_key_press(allow_key_repeat);
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
        keycode = poll_for_key_press(allow_key_repeat);
    }
    return keycode;
}

SDL_Keycode wait_for_input(int spinner_x, int spinner_y)
{
    return wait_for_input_with_repeat(spinner_x, spinner_y, false);
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
    x += 3;
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

void foreign_orders_dialog()
{
    fade_to_black_speed_3();
    video_fill_screen_with_black();
    uint16 si = create_text_dialog_box(1, 0x13, 0x26, "FOREIGN CUSTOMERS", "Press ANY key.");
    si += 2;
    display_dialog_text(si, 3, "        -----------------");
    display_dialog_text(si, 5, " The following screens list our");
    display_dialog_text(si, 6, "   dealers outside the United");
    display_dialog_text(si, 7, " States, for Australia, Germany,");
    display_dialog_text(si, 8, " Canada and the United Kingdom.");
    display_dialog_text(si, 10, "   These are official Apogee");
    display_dialog_text(si, 11, "    dealers with the latest");
    display_dialog_text(si, 12, "\xfe""153000       games and updates.    ""\xfe""153001");
    display_dialog_text(si, 14, " If your country is not listed,");
    display_dialog_text(si, 15, "  you may order directly from");
    display_dialog_text(si, 0x10, "Apogee by phone: (214) 278-5655.");
    fade_in_from_black(1);
    wait_for_input(si + 0x21, 0x12);
    fade_to_black(1);
    video_fill_screen_with_black();

    si = create_text_dialog_box(1, 0x13, 0x26, "AUSTRALIAN CUSTOMERS", "Press ANY key.");
    si += 3;
    display_dialog_text(si, 4, "PRICE: $45 + $5 shipping.");
    display_dialog_text(si, 6, "BudgetWare");
    display_dialog_text(si, 7, "P.O. Box 496");
    display_dialog_text(si, 8, "Newtown, NSW  2042        \xfe""113000");
    display_dialog_text(si, 10, "Phone:      (02) 519-4233");
    display_dialog_text(si, 11, "Toll free:  (008) 022-064");
    display_dialog_text(si, 12, "Fax:        (02) 516-4236");
    display_dialog_text(si, 13, "CompuServe: 71520,1475");
    display_dialog_text(si, 15, "Use MasterCard, Visa, Bankcard,");
    display_dialog_text(si, 0x10, "cheques.");
    fade_in_from_black(1);
    wait_for_input(si + 0x20, 0x12);
    fade_to_black(1);
    video_fill_screen_with_black();

    si = create_text_dialog_box(1, 0x14, 0x26, "CANADIAN CUSTOMERS", "Press ANY key.");
    si += 3;
    display_dialog_text(si, 4, "PRICE: $42 Canadian.       \xfe""146000");
    display_dialog_text(si, 6, "Distant Markets");
    display_dialog_text(si, 7, "Box 1149");
    display_dialog_text(si, 8, "194 - 3803 Calgary Trail S.");
    display_dialog_text(si, 9, "Edmondton, Alb.  T6J 5M8");
    display_dialog_text(si, 10, "CANADA");
    display_dialog_text(si, 12, "Orders:    1-800-661-7383");
    display_dialog_text(si, 13, "Inquiries: (403) 436-3009");
    display_dialog_text(si, 14, "Fax:       (403) 435-0928  \xfe""086002");
    display_dialog_text(si, 0x10, "Use MasterCard, Visa or");
    display_dialog_text(si, 0x11, "money orders.");
    fade_in_from_black(1);
    wait_for_input(si + 0x20, 0x13);
    fade_to_black(1);
    video_fill_screen_with_black();

    si = create_text_dialog_box(1, 0x14, 0x26, "GERMAN CUSTOMERS", "Press ANY key.");
    si += 3;
    display_dialog_text(si, 4, "Price: 49,-- DM plus 10,-- DM");
    display_dialog_text(si, 5, "Total: 59,-- DM (Deutsche Mark)");
    display_dialog_text(si, 7, "CDV-Software");
    display_dialog_text(si, 8, "Ettlingerstr. 5");
    display_dialog_text(si, 9, "7500 Karlsruhe 1  GERMANY");
    display_dialog_text(si, 11, "Phone: 0721-22295");
    display_dialog_text(si, 12, "Fax:   0721-21314            \xfe""127004");
    display_dialog_text(si, 13, "Compuserve: 1000022,274");
    display_dialog_text(si, 15, "Use Visa, MasterCard, EuroCard,");
    display_dialog_text(si, 0x10, "American Express, cheque, money");
    display_dialog_text(si, 0x11, "order, or C.O.D.");
    fade_in_from_black(1);
    wait_for_input(si + 0x20, 0x13);
    fade_to_black(1);
    video_fill_screen_with_black();

    si = create_text_dialog_box(1, 0x14, 0x26, "UNITED KINGDOM CUSTOMERS", "Press ANY key.");
    si += 3;
    display_dialog_text(si, 4, "Price: /29 + VAT + 2 P&P     \xfe""085000");
    display_dialog_text(si, 6, "Precision Software Applications");
    display_dialog_text(si, 7, "Unit 3, Valley Court Offices");
    display_dialog_text(si, 8, "Lower Rd");
    display_dialog_text(si, 9, "Croydon, Near Royston");
    display_dialog_text(si, 10, "Herts. SG8 0HF, United Kingdom");
    display_dialog_text(si, 12, "Phone: +44 (0) 223 208 288");
    display_dialog_text(si, 13, "FAX:   +44 (0) 223 208 089");
    display_dialog_text(si, 15, "Credit cards, Access, cheques,");
    display_dialog_text(si, 0x10, "postal & Bankers orders.");
    display_dialog_text(si, 0x11, "Make cheques payable to PSA.");
    fade_in_from_black(1);
    wait_for_input(si + 0x20, 0x13);
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

void story_dialog()
{
    fade_to_black_speed_3();
    video_fill_screen_with_black();
    uint16 x = create_text_dialog_box(1, 0x17, 0x26, "STORY", "Press ANY key.");
    display_dialog_text(x + 1, 8, "\xfb""000");
    display_dialog_text(x + 1, 0x14, "\xfb""002");
    display_dialog_text(x + 0x10, 5, "Tomorrow is Cosmo's");
    display_dialog_text(x + 0x10, 7, "birthday, and his");
    display_dialog_text(x + 0x10, 9, "parents are taking");
    display_dialog_text(x + 0x10, 11, "him to the one place");
    display_dialog_text(x + 0x10, 13, "in the Milky Way");
    display_dialog_text(x + 0x10, 15, "galaxy that all kids");
    display_dialog_text(x + 0x10, 0x11, "would love to go to:");
    display_dialog_text(x + 0x10, 0x13, "   Disney World!");
    fade_in_from_black_with_delay_3();
    wait_for_input(x + 0x23, 0x16);
    fade_to_black_speed_3();
    video_fill_screen_with_black();

    x = create_text_dialog_box(1, 0x17, 0x26, "STORY", "Press ANY key.");
    display_dialog_text(x + 3, 12, "\xfb""003");
    display_dialog_text(x + 0x19, 12, "\xfb""004");
    display_dialog_text(x + 3, 5, "Suddenly a blazing comet zooms");
    display_dialog_text(x + 4, 7, "toward their ship--leaving no");
    display_dialog_text(x + 0x10, 10, "time");
    display_dialog_text(x + 0x11, 12, "to");
    display_dialog_text(x + 10, 15, "change course...");
    fade_in_from_black_with_delay_3();
    wait_for_input(x + 0x23, 0x16);
    fade_to_black_speed_3();
    video_fill_screen_with_black();

    x = create_text_dialog_box(1, 0x17, 0x26, "STORY", "Press ANY key.");
    display_dialog_text(x + 1 + 1, 7, "\xfb""005");
    display_dialog_text(x + 0x19, 0x14, "\xfb""006");
    display_dialog_text(x + 15, 7, "The comet slams into");
    display_dialog_text(x + 1, 10, "the ship and forces Cosmo's");
    display_dialog_text(x + 1, 13, "dad to make an");
    display_dialog_text(x + 1, 15, "emergency landing");
    display_dialog_text(x + 1, 0x11, "on an uncharted");
    display_dialog_text(x + 1, 0x13, "planet.");
    fade_in_from_black_with_delay_3();
    wait_for_input(x + 0x23, 0x16);
    fade_to_black_speed_3();
    video_fill_screen_with_black();

    x = create_text_dialog_box(1, 0x17, 0x26, "STORY", "Press ANY key.");
    display_dialog_text(x + 0x11, 9, "\xfb""007");
    display_dialog_text(x + 1, 0x14, "\xfb""008");
    display_dialog_text(x + 1 + 1, 5, "While Cosmo's");
    display_dialog_text(x + 1 + 1, 7, "dad repairs");
    display_dialog_text(x + 1 + 1, 9, "the ship,");
    display_dialog_text(x + 11, 15, "Cosmo heads off to");
    display_dialog_text(x + 11, 0x11, "explore and have");
    display_dialog_text(x + 11, 0x13, "some fun.");
    fade_in_from_black_with_delay_3();
    wait_for_input(x + 0x23, 0x16);
    fade_to_black_speed_3();
    video_fill_screen_with_black();

    x = create_text_dialog_box(1, 0x17, 0x26, "STORY", "Press ANY key.");
    display_dialog_text(x + 3, 15, "\xfb""009");
    display_dialog_text(x + 6, 7, "Returning an hour later,");
    display_dialog_text(x + 0x11, 11, "Cosmo cannot find");
    display_dialog_text(x + 0x11, 13, "his Mom or Dad.");
    display_dialog_text(x + 0x11, 15, "Instead, he finds");
    display_dialog_text(x + 8, 0x12, "strange foot prints...");
    fade_in_from_black_with_delay_3();
    wait_for_input(x + 0x23, 0x16);
    fade_to_black_speed_3();
    video_fill_screen_with_black();

    x = create_text_dialog_box(1, 0x17, 0x26, "STORY", "Press ANY key.");
    display_dialog_text(x + 0x15, 0x13, "\xfb""010");
    display_dialog_text(x + 1 + 1, 5, "...oh no!  Has his");
    display_dialog_text(x + 1 + 1, 7, "family been taken");
    display_dialog_text(x + 1 + 1, 9, "away by a hungry");
    display_dialog_text(x + 1 + 1, 11, "alien creature to");
    display_dialog_text(x + 1 + 1, 13, "be eaten?  Cosmo");
    display_dialog_text(x + 1 + 1, 15, "must rescue his");
    display_dialog_text(x + 1 + 1, 0x11, "parents before");
    display_dialog_text(x + 1 + 1, 0x13, "it's too late...!");
    fade_in_from_black_with_delay_3();
    wait_for_input(x + 0x23, 0x16);
}

void missing_savegame_dialog()
{
    uint16 x = create_text_dialog_box(5, 4, 0x14, "Can't find that", "game to restore! ");
    wait_for_input(x + 0x11, 7);
}

game_play_mode_enum main_menu() {
    set_initial_game_state();
    show_one_moment_screen_flag = 0;
    load_music(0x12);
    display_fullscreen_image(1);

    for(int i=0;;i+=3)
    {
        SDL_Keycode key = poll_for_key_press(false);
        if(key != SDLK_UNKNOWN)
        {
            if (key == SDLK_q || key == SDLK_ESCAPE)
            {
                if (quit_game_dialog())
                {
                    return QUIT_GAME;
                }
            }

            uint16 restore_status = 0;
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
                        show_one_moment_screen_flag = 1;
                        show_monster_attack_hint = 0;
                        play_sfx(0x30);
                        return PLAY_GAME;

                    case SDLK_r :
                        restore_status = restore_savegame_dialog();
                        if(restore_status == 1)
                        {
                            stop_music();
                            return PLAY_GAME;
                        }

                        if(restore_status == 0)
                        {
                            missing_savegame_dialog();
                        }
                        break;

                    case SDLK_s :
                        story_dialog();
                        break;

                    case SDLK_g :
                        game_redefine();
                        break;

                    case SDLK_F11 :
                        if (cheat_mode_flag)
                        {
                            return RECORD_DEMO;
                        }
                        break;

                    case SDLK_o :
                        ordering_info_dialog();
                        break;

                    case SDLK_f :
                        foreign_orders_dialog();
                        break;

                    case SDLK_a :
                        apogee_bbs_dialog();
                        break;

                    case SDLK_d :
                        return PLAY_DEMO;

                    case SDLK_h :
                        fade_to_black_speed_3();
                        video_fill_screen_with_black();
                        display_high_score_dialog(true);
                        break;

                    case SDLK_c :
                        display_fullscreen_image(2);
                        while(poll_for_key_press(false)==SDLK_UNKNOWN)
                        {}
                        break;

                    case SDLK_t :
                        return_to_title = 1;
                        i = 0;
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

void display_clear_tile_to_gray(uint16 x, uint16 y)
{
    video_draw_tile(map_get_bg_tile(1999), x * TILE_WIDTH, y * TILE_HEIGHT);
}

static const char score_text_tbl[][17] = {
        "    Not Bad!    ",
        "    Way Cool    ",
        "     Groovy     ",
        "    Radical!    ",
        "     Insane     ",
        "     Gnarly     ",
        "   Outrageous   ",
        "   Incredible   ",
        "    Awesome!    ",
        "   Brilliant!   ",
        "    Profound    ",
        "    Towering    ",
        "Rocket Scientist"
};

void display_score_from_level()
{
    stop_music();

    if(num_stars_collected == 0)
    {
        fade_in_from_black_with_delay_3();
        return;
    }

    fade_to_white(3);
    video_fill_screen_with_black();
    create_text_dialog_box(2, 0xe, 0x1e, "Super Star Bonus!!!!", "");

    display_actor_sprite_maybe(1, 2, 8, 8, 6);

    display_dialog_text(0xe, 7, "X 1000 =");

    display_number(0x1b, 7, num_stars_collected * 1000);

    cosmo_wait(0x32);
    display_dialog_text(0xa, 0xc, "YOUR SCORE =  ");
    display_number(0x1d, 0xc, score);

    fade_in_from_black_with_delay_3();

    cosmo_wait(0x64);

    int star_counter = 0;
    for(int i=num_stars_collected; i > 0; i--)
    {
        score += 1000;
        cosmo_wait(0xf);

        for(int j=0; j < 7; j++)
        {
            display_clear_tile_to_gray(0x17 + j, 0xc);
        }
        play_sfx(1);
        display_number(0x1d, 0xc, score);

        if (star_counter / 6 < 13)
        {
            star_counter++;
        }

        for(int j=0; j < 16; j++)
        {
            if(j < 7)
            {
                display_clear_tile_to_gray(0x16 + j, 7);
            }

            if((star_counter & 7) == 1)
            {
                display_clear_tile_to_gray(0xd + j, 0xe);

            }
        }

        display_number(0x1b, 7, i * 1000);

        video_update();

        if((star_counter & 7) == 1)
        {
            uint8 score_text_idx = (uint8)(star_counter/6);
            if(score_text_idx > 12)
            {
                score_text_idx = 12;
            }

            display_dialog_text(0xd, 0xe, score_text_tbl[score_text_idx]);
        }

        video_update();
    }

    cosmo_wait(0x190);
    num_stars_collected = 0;
}

void display_end_of_level_score_dialog(const char *header_text, const char *footer_text)
{
    fade_to_black_speed_3();
    video_fill_screen_with_black();
    uint16 x = create_text_dialog_box(6, 4, 0x1e, header_text, footer_text);
    fade_in_from_black_with_delay_3();
    wait_for_input(x + 0x1b, 8);
    display_score_from_level();
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
        uint16 tmp_num_bombs = num_bombs;
        uint32 tmp_num_stars_collected = num_stars_collected;
        uint16 tmp_current_level = current_level;
        uint8 tmp_num_health_bars = num_health_bars;
        uint32 tmp_score = score;
        uint8 tmp_health = health;

        load_savegame_file('T');
        write_savegame_file(keycode);

        health = tmp_health;
        num_bombs = tmp_num_bombs;
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
    uint16 si = create_text_dialog_box(4, 0xb, 0x16, "Game Redefine", "Press ESC to quit.");
    display_dialog_text(si, 7,  " K)eyboard redefine");
    display_dialog_text(si, 8,  " J)oystick redefine");
    display_dialog_text(si, 9,  " S)ound toggle");
    display_dialog_text(si, 10, " T)est sound");
    display_dialog_text(si, 11, " M)usic toggle");

    SDL_Keycode key = wait_for_input(0x1d, 0xd);

    switch (key)
    {
        //FIXME wireup functions.

        case SDLK_k :
            //FIXME keyboard_config()
            break;
        case SDLK_j :
            break;
        case SDLK_s :
            sound_toggle_dialog();
            break;
        case SDLK_t :
            break;
        case SDLK_m :
            music_toggle_dialog();
            break;
        default :
            break;
    }
}

void cosmic_hints_dialog(uint16 y_pos)
{
    uint16 y = y_pos - 1;
    uint16 x = create_text_dialog_box(y_pos, 0x12, 0x26, "Cosmic Hints", "Press ANY key.");
    display_dialog_text(x, y + 4, " * Usually jumping in the paths of");
    display_dialog_text(x, y + 5, "   bonus objects will lead you in");
    display_dialog_text(x, y + 6, "   the right direction.");
    display_dialog_text(x, y + 8, " * There are many secret bonuses in");
    display_dialog_text(x, y + 9, "   this game, such as bombing 15 of");
    display_dialog_text(x, y + 10, "   the Eye Plants.  (Registered");
    display_dialog_text(x, y + 11, "   players will get the full list.)");
    display_dialog_text(x, y + 13, " * When clinging to a wall, tap the");
    display_dialog_text(x, y + 14, "   jump key to let go and fall.  To");
    display_dialog_text(x, y + 15, "   re-cling to the wall, push");
    display_dialog_text(x, y + 0x10, "   yourself into the wall again.");
    wait_for_input(x + 0x23, y + 0x11);
    x = create_text_dialog_box(y_pos, 0x12, 0x26, "Key Definition Screen", "");
    display_dialog_text(x, y + 4, "                     Look");
    display_dialog_text(x, y + 5, "                      UP");
    display_dialog_text(x, y + 7, "              Walk            Walk");
    display_dialog_text(x, y + 8, "  Jump  Drop  LEFT            RIGHT");
    display_dialog_text(x, y + 9, "   UP   BOMB");
    display_dialog_text(x, y + 10, "                     \xfd""028");
    display_dialog_text(x, y + 11, "                     Look");
    display_dialog_text(x, y + 12, "                     DOWN");
    display_dialog_text(x, y + 13, "              \xfd""001                 ""\xfd""023");
    display_dialog_text(x, y + 14, "  \xfd""030      ""\xfd""037""\xfe""024000");
    display_dialog_text(x, y + 0x11, "                     \xfd""029");
    //FIXME need to display mapped keys here.
//    display_dialog_text(x + 0x18, y + 7, al * ax + 0xc44);
//    display_dialog_text(x + 0x18, y + 14, al * ax + "NULL");
//    display_dialog_text(x + 14, y + 14, al * ax + 0xc44);
//    display_dialog_text(x + 0x1e, y + 14, al * ax + 0xc44);
//    display_dialog_text(x + 1 + 1, y + 15, al * ax + 0xc44);
//    display_dialog_text(x + 8, y + 15, al * ax + 0xc44);
    wait_for_input(x + 0x23, y + 0x11);
    x = create_text_dialog_box(4, 11, 0x22, "During the game, you can...", "Press ANY key.");
    display_dialog_text(x, 7, " Press 'P' to PAUSE GAME");
    display_dialog_text(x, 8, " Press 'ESC' or 'Q' to QUIT game");
    display_dialog_text(x, 9, " Press 'S' to toggle SOUND");
    display_dialog_text(x, 10, " Press 'M' to toggle MUSIC");
    display_dialog_text(x, 11, " Press 'F1' to show HELP");
    wait_for_input(x + 0x1f, 13);
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
                display_high_score_dialog(false);
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
    uint16 x = create_text_dialog_box(4, 13, 0x1a, "A game by", "Copyright (c) 1992");
    display_dialog_text(x, 7, "     Todd J Replogle");
    display_dialog_text(x + 11, 9, "and");
    display_dialog_text(x, 11, "\xfd""027   Stephen A Hornback""\xfd""004");
    display_dialog_text(x, 13, "      Version 1.20");
    wait_for_time_or_key(0x2bc);
    fade_to_black_speed_3();
}

void enter_high_score_name_dialog(char *name_buffer, uint8 buf_length)
{
    memset(name_buffer, 0, buf_length);
    uint16 x = create_text_dialog_box(5, 7, 0x24, "You made it into the hall of fame!", "Press ESC to quit.");
    display_dialog_text(x, 8, "Enter your name:");
    fade_in_from_black_with_delay_3();
    play_sfx(0x34);

    int i = 0;
    for(; ; )
    {
        SDL_Keycode key = wait_for_input_with_repeat(x + i + 16, 8, true);
        display_clear_tile_to_gray(x + i + 16, 8);
        if((key >= SDLK_a && key <= SDLK_z) || key == SDLK_SPACE)
        {
            if(i < buf_length - 1)
            {
                name_buffer[i] =(char)toupper(key);
                display_char(x + i + 16, 8, (char)key);
                i++;
            }
        }
        if(key == SDLK_ESCAPE)
        {
            i = 0;
            break;
        }
        if(key == SDLK_RETURN)
        {
            break;
        }
        if(i > 0 && (key == SDLK_BACKSPACE || key == SDLK_DELETE))
        {
            i--;
            name_buffer[i] = ' ';
            display_clear_tile_to_gray(x + i + 16, 8);
        }
    }

    name_buffer[i] = '\0';
}

void display_high_score_dialog(bool use_fading)
{
    for(;;)
    {
        uint16 x = create_text_dialog_box(2, 0x11, 0x1e, "Hall of Fame", "any other key to exit.");

        for(int i = 0; i < NUM_HIGH_SCORE_ENTRIES; i++)
        {
            uint16 y = i + 5;
            HighScore high_score = get_high_score(i);
            display_number(x + 2, y, i + 1);
            display_dialog_text(x + 3, y, ".");
            display_number(x + 11, y, high_score.score);
            display_dialog_text(x + 13, y, high_score.name);
        }

        display_dialog_text(x + 3, 0x10, "Press 'F10' to erase or");

        if(use_fading)
        {
            fade_in_from_black_with_delay_3();
        }
        SDL_Keycode  keycode = wait_for_input(x + 0x1b, 0x11);
        if (keycode != SDLK_F10)
        {
            break;
        }

        x = create_text_dialog_box(5, 4, 0x1c, "Are you sure you want to", "ERASE High Scores?");
        keycode = wait_for_input(x + 0x16, 7);
        if (keycode == SDLK_y)
        {
            clear_high_score_table();
        }

        if(use_fading)
        {
            fade_to_black_speed_3();
            video_fill_screen_with_black();
        }
    }
}

void sound_toggle_dialog()
{
    uint16 x;
    if(sfx_on_flag)
    {
        sfx_on_flag = 0;
        x = create_text_dialog_box(2, 4, 0x18, "Sound Toggle", "The sound is now OFF!");
    }
    else
    {
        sfx_on_flag = 1;
        x = create_text_dialog_box(2, 4, 0x18, "Sound Toggle", "The sound is now ON!");
    }

    wait_for_input(x + 0x15, 4);
}

void music_toggle_dialog()
{
    uint16 x;
    if(music_on_flag)
    {
        music_on_flag = 0;
        x = create_text_dialog_box(2, 4, 0x18, "Music Toggle", "The music is now OFF!");
        stop_music();
    }
    else
    {
        music_on_flag = 1;
        x = create_text_dialog_box(2, 4, 0x18, "Music Toggle", "The music is now ON!");
        play_music();
    }

    wait_for_input(x + 0x15, 4);
}
