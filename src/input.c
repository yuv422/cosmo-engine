//
// Created by Eric Fry on 31/10/2017.
//


#include <SDL_events.h>
#include <sound/sfx.h>
#include <SDL_timer.h>
#include "input.h"
#include "map.h"
#include "game.h"
#include "player.h"
#include "status.h"

uint8 bomb_key_pressed = 0;
uint8 jump_key_pressed = 0;
uint8 up_key_pressed = 0;
uint8 down_key_pressed = 0;
uint8 left_key_pressed = 0;
uint8 right_key_pressed = 0;

//This is needed because the game manipulates up_key_pressed as part of the hover board logic. This is the actual
//key pressed state.
uint8 sdl_up_key_pressed = 0;

uint8 byte_2E17C; //modifies the left, right and jump key presses

void wait_for_time_or_key(int delay_in_game_cycles)
{
    //TODO
}

void cosmo_wait(int delay)
{
    SDL_Delay((Uint32)(8 * delay));
}

input_state_enum handle_key_down(SDL_KeyboardEvent event)
{
    switch(event.keysym.sym)
    {
        case SDLK_LEFT :
            left_key_pressed = 1;
            break;
        case SDLK_RIGHT :
            right_key_pressed = 1;
            break;
        case SDLK_UP :
            sdl_up_key_pressed = 1;
            break;
        case SDLK_DOWN :
            down_key_pressed = 1;
            break;
        case SDLK_a :
            jump_key_pressed = 1;
            break;
        case SDLK_b :
            num_bombs++;
            display_num_bombs_left();
            break;
        case SDLK_n :
            finished_level_flag_maybe = 1; //FIXME remove. only needed for testing
            break;
        case SDLK_s :
            bomb_key_pressed = 1;
            break;
        case SDLK_q :
            return QUIT;
        case SDLK_i :
            printf("player info x_pos =%d; y_pos = %d;\n", player_x_pos, player_y_pos);
            break;
        default : break;
    }
    up_key_pressed = sdl_up_key_pressed;
    return CONTINUE;
}

input_state_enum handle_key_up(SDL_KeyboardEvent event)
{
    static int sfx_idx = 1;
    switch(event.keysym.sym)
    {
        case SDLK_LEFT :
            left_key_pressed = 0;
            break;
        case SDLK_RIGHT :
            right_key_pressed = 0;
            break;
        case SDLK_UP :
            sdl_up_key_pressed = 0;
            break;
        case SDLK_DOWN :
            down_key_pressed = 0;
            break;
        case SDLK_a :
            jump_key_pressed = 0;
            break;
        case SDLK_s :
            bomb_key_pressed = 0;
            break;
        case SDLK_p :
            play_sfx(sfx_idx);
            break;
        case SDLK_i :
            play_sfx(--sfx_idx);
            break;
        case SDLK_o :
            play_sfx(++sfx_idx);
            break;
        default : break;
    }
    up_key_pressed = sdl_up_key_pressed;
    return CONTINUE;
}

input_state_enum read_input()
{
    //FIXME
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return QUIT;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            return handle_key_down(event.key);
        }
        else if (event.type == SDL_KEYUP)
        {
            return handle_key_up(event.key);
        }
    }

    up_key_pressed = sdl_up_key_pressed;

    return CONTINUE;
}

void reset_player_control_inputs()
{
    up_key_pressed = 0;
    sdl_up_key_pressed = 0;
    down_key_pressed = 0;
    left_key_pressed = 0;
    right_key_pressed = 0;
    bomb_key_pressed = 0;
    jump_key_pressed = 0;
}

uint8 poll_for_key_press()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
            return true;
    }
    return false;
}