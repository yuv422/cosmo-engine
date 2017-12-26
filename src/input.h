//
// Created by Eric Fry on 31/10/2017.
//

#ifndef COSMO_ENGINE_INPUT_H
#define COSMO_ENGINE_INPUT_H

#include <SDL_keycode.h>
#include "defines.h"

typedef enum
{
    QUIT,
    PAUSED,
    CONTINUE
} input_state_enum;

extern uint8 bomb_key_pressed;
extern uint8 jump_key_pressed;
extern uint8 up_key_pressed;
extern uint8 down_key_pressed;
extern uint8 left_key_pressed;
extern uint8 right_key_pressed;

extern uint8 byte_2E17C;

void wait_for_time_or_key(int delay_in_game_cycles);
input_state_enum read_input();
void reset_player_control_inputs();
SDL_Keycode poll_for_key_press();
void cosmo_wait(int delay);

#endif //COSMO_ENGINE_INPUT_H
