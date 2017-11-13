//
// Created by Eric Fry on 31/10/2017.
//

#ifndef COSMO_ENGINE_DIALOG_H
#define COSMO_ENGINE_DIALOG_H

#include "defines.h"
#include "game.h"

//data
extern uint8 show_one_moment_screen_flag;
extern uint8 byte_28BE3;
extern uint8 byte_2E21C;

game_play_mode_enum main_menu();

void you_havent_found_any_bombs_dialog();

void now_entering_level_n_dialog(uint16 level_number);

void ingame_hint_dialogs(uint16 hint_number);

#endif //COSMO_ENGINE_DIALOG_H
