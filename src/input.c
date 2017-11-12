//
// Created by Eric Fry on 31/10/2017.
//


#include <SDL_events.h>
#include "input.h"
#include "map.h"

uint8 bomb_key_pressed = 0;
uint8 jump_key_pressed = 0;
uint8 up_key_pressed = 0;
uint8 down_key_pressed = 0;
uint8 left_key_pressed = 0;
uint8 right_key_pressed = 0;

uint8 byte_2E17C; //modifies the left, right and jump key presses

void wait_for_time_or_key(int delay_in_game_cycles)
{

}

void cosmo_wait(int delay)
{
    //FIXME
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
            up_key_pressed = 1;
            break;
        case SDLK_DOWN :
            down_key_pressed = 1;
            break;
        case SDLK_a :
            jump_key_pressed = 1;
            break;
        case SDLK_q :
            return QUIT;
        default : break;
    }
    return CONTINUE;
}

input_state_enum handle_key_up(SDL_KeyboardEvent event)
{
    switch(event.keysym.sym)
    {
        case SDLK_LEFT :
            left_key_pressed = 0;
            break;
        case SDLK_RIGHT :
            right_key_pressed = 0;
            break;
        case SDLK_UP :
            up_key_pressed = 0;
            break;
        case SDLK_DOWN :
            down_key_pressed = 0;
            break;
        case SDLK_a :
            jump_key_pressed = 0;
            break;
        default : break;
    }
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

    return CONTINUE;
}