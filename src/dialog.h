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

void power_up_module_dialog();

void display_end_of_level_score_dialog(const char *header_text, const char *footer_text);

void end_game_dialog(uint16 dialog_number);

void monster_attack_hint_dialog();

uint16 create_text_dialog_box(uint16 y_offset, uint16 height, uint16 width, const char *top_message, const char *bottom_message);

#endif //COSMO_ENGINE_DIALOG_H
