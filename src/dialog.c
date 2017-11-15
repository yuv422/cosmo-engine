//
// Created by Eric Fry on 31/10/2017.
//


#include "game.h"
#include "dialog.h"

//Data
uint8 show_one_moment_screen_flag = 0;
uint8 byte_28BE3 = 0;
uint8 byte_2E21C = 0;

void you_havent_found_any_bombs_dialog() {

}

game_play_mode_enum main_menu() {
    set_initial_game_state();
    return PLAY_GAME;
}

void now_entering_level_n_dialog(uint16 level_number)
{

}

void ingame_hint_dialogs(uint16 hint_number) {

}

void power_up_module_dialog()
{

}

