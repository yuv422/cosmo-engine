/*
 *  Cosmo-Engine
 *  Copyright Eric Fry (c) 2017. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

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

uint16 help_menu_dialog();

void malformed_savegame_dialog();

void a_game_by_dialog();

uint16 create_text_dialog_box(uint16 y_offset, uint16 height, uint16 width, const char *top_message, const char *bottom_message);

int quit_game_dialog();

void enter_high_score_name_dialog(char *name_buffer, uint8 buf_length);

void display_high_score_dialog(bool use_fading);

void game_redefine();

void sound_toggle_dialog();
void music_toggle_dialog();
void hack_mover_toggle_dialog();
void god_mode_toggle_dialog();

int warp_mode_dialog();

void end_sequence();

void show_ingame_hint_dialog(int dialog_num);

void display_ingame_hint_dialog();

void commercial_ordering_information_dialog();

void cosmo_duke_dialog();

#endif //COSMO_ENGINE_DIALOG_H
