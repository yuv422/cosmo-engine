//
// Created by Eric Fry on 31/10/2017.
//


#include <SDL.h>
#include <SDL_events.h>
#include "sound/sfx.h"
#include <SDL_timer.h>
#include "input.h"
#include "game.h"
#include "player.h"
#include "status.h"
#include "dialog.h"
#include "demo.h"
#include "config.h"

SDL_GameController* gamepad;

SDL_Keycode cfg_up_key;
SDL_Keycode cfg_down_key;
SDL_Keycode cfg_left_key;
SDL_Keycode cfg_right_key;
SDL_Keycode cfg_jump_key;
SDL_Keycode cfg_bomb_key;

uint8 bomb_key_pressed = 0;
uint8 jump_key_pressed = 0;
uint8 up_key_pressed = 0;
uint8 down_key_pressed = 0;
uint8 left_key_pressed = 0;
uint8 right_key_pressed = 0;

//This is needed because the game manipulates up_key_pressed as part of the hover board logic. This is the actual
//key pressed state.
uint8 input_up_key_pressed = 0;

uint8 byte_2E17C; //modifies the left, right and jump key presses TODO this isn't wired up yet. It might disable player input.

static SDL_Keycode gamecontroller_to_keyboard(SDL_Event *event)
{
    SDL_Keycode kb_button;
    SDL_ControllerButtonEvent e = event->cbutton;
    switch (e.button)
    {
    case SDL_CONTROLLER_BUTTON_A:
        kb_button = cfg_jump_key;
        break;
    case SDL_CONTROLLER_BUTTON_B:
    case SDL_CONTROLLER_BUTTON_X:
        kb_button = cfg_bomb_key;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
        kb_button = cfg_up_key;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        kb_button = cfg_down_key;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        kb_button = cfg_left_key;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        kb_button = cfg_right_key;
        break;
    case SDL_CONTROLLER_BUTTON_START:
        kb_button = SDLK_RETURN;
        break;
    case SDL_CONTROLLER_BUTTON_BACK:
        kb_button = SDLK_q;
        break;
    case SDL_CONTROLLER_BUTTON_Y:
        kb_button = SDLK_ESCAPE;
        break;
    default:
        kb_button = SDLK_UNKNOWN;
        break;
    }
    return kb_button;
}

void input_init()
{
    flush_input();
    if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
    {
        printf("ERROR: intialising gamecontroller!\n");
        return;
    }

    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        gamepad = SDL_GameControllerOpen(i);
        if (gamepad != NULL)
            return;
    }
}

void input_shutdown()
{
    if (gamepad != NULL)
        SDL_GameControllerClose(gamepad);

    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
}

void wait_for_time_or_key(int delay_in_game_cycles)
{
    reset_player_control_inputs();
    for(int i=0;i < delay_in_game_cycles; i++)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if ((event.type == SDL_KEYDOWN && !event.key.repeat) ||
                 event.type == SDL_CONTROLLERBUTTONDOWN)
            {
                return;
            }
        }
        cosmo_wait(1);
    }
}

void cosmo_wait(int delay)
{
    SDL_Delay((Uint32)(8 * delay));
}

input_state_enum handle_demo_input()
{
    if(poll_for_key_press(false) != SDLK_UNKNOWN)
    {
        return QUIT;
    }

    if(read_input_from_demo())
    {
        return QUIT;
    }

    return CONTINUE;
}

InputCommand get_input_command_from_keycode(SDL_Keycode keycode)
{
    if (keycode == cfg_up_key)
    {
        return CMD_KEY_UP;
    }
    if (keycode == cfg_down_key)
    {
        return CMD_KEY_DOWN;
    }
    if (keycode == cfg_left_key)
    {
        return CMD_KEY_LEFT;
    }
    if (keycode == cfg_right_key)
    {
        return CMD_KEY_RIGHT;
    }
    if (keycode == cfg_jump_key)
    {
        return CMD_KEY_JUMP;
    }
    if (keycode == cfg_bomb_key)
    {
        return CMD_KEY_BOMB;
    }

    return CMD_KEY_OTHER;
}

input_state_enum handle_key_down(SDL_Keycode key)
{
    InputCommand command = get_input_command_from_keycode(key);

    switch(command)
    {
        case CMD_KEY_UP :
            input_up_key_pressed = 1;
            break;
        case CMD_KEY_DOWN :
            down_key_pressed = 1;
            break;
        case CMD_KEY_LEFT :
            left_key_pressed = 1;
            break;
        case CMD_KEY_RIGHT :
            right_key_pressed = 1;
            break;
        case CMD_KEY_JUMP :
            jump_key_pressed = 1;
            break;
        case CMD_KEY_BOMB :
            bomb_key_pressed = 1;
            break;
        default :
            switch(key)
            {
                case SDLK_b : //FIXME testing code
                    num_bombs++;
                    display_num_bombs_left();
                    break;
                case SDLK_g :
                    god_mode_toggle_dialog(); //TODO should be protected by cheat mode
                    break;
                case SDLK_m :
                    music_toggle_dialog();
                    break;
                case SDLK_w :
                    warp_mode_dialog(); //FIXME remove this. Only here for testing.
                    break;
                case SDLK_s :
                    sound_toggle_dialog();
                    break;
                case SDLK_q :
                    if (quit_game_dialog())
                    {
                        return QUIT;
                    }
                    break;
                case SDLK_h :
                    hack_mover_toggle_dialog();
                    break;
                case SDLK_i : //FIXME testing code
                    printf("player info x_pos =%d; y_pos = %d;\n", player_x_pos, player_y_pos);
                    break;
                case SDLK_F1 :
                case SDLK_ESCAPE :
                    switch(help_menu_dialog())
                    {
                        case 0 : break;
                        case 1 : break;
                        case 2 : return QUIT;
                        default : break;
                    }
                default : break;
            }
            break;
    }

    up_key_pressed = input_up_key_pressed;
    return CONTINUE;
}

input_state_enum handle_key_up(SDL_Keycode key)
{
    InputCommand command = get_input_command_from_keycode(key);

    switch(command)
    {
        case CMD_KEY_UP :
            input_up_key_pressed = 0;
            break;
        case CMD_KEY_DOWN :
            down_key_pressed = 0;
            break;
        case CMD_KEY_LEFT :
            left_key_pressed = 0;
            break;
        case CMD_KEY_RIGHT :
            right_key_pressed = 0;
            break;
        case CMD_KEY_JUMP :
            jump_key_pressed = 0;
            break;
        case CMD_KEY_BOMB :
            bomb_key_pressed = 0;
            break;
        default : break;
    }
    up_key_pressed = input_up_key_pressed;
    return CONTINUE;
}

input_state_enum read_input()
{
    if(game_play_mode ==  PLAY_DEMO)
    {
        return handle_demo_input();
    }

    //FIXME handle cheats.
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return QUIT;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if(handle_key_down(event.key.keysym.sym) == QUIT)
                return QUIT;
        }
        else if (event.type == SDL_KEYUP)
        {
            handle_key_up(event.key.keysym.sym);
        }
        else if (event.type == SDL_CONTROLLERBUTTONDOWN)
        {
            if(handle_key_down(gamecontroller_to_keyboard(&event)) == QUIT)
                return QUIT;
        }
        else if (event.type == SDL_CONTROLLERBUTTONUP)
        {
            handle_key_up(gamecontroller_to_keyboard(&event));
        }
    }

    up_key_pressed = input_up_key_pressed;

    return CONTINUE;
}

void reset_player_control_inputs()
{
    up_key_pressed = 0;
    input_up_key_pressed = 0;
    down_key_pressed = 0;
    left_key_pressed = 0;
    right_key_pressed = 0;
    bomb_key_pressed = 0;
    jump_key_pressed = 0;
}

SDL_Keycode poll_for_key_press(bool allow_key_repeat)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN && (allow_key_repeat || !event.key.repeat))
            return event.key.keysym.sym;
        if (event.type == SDL_CONTROLLERBUTTONDOWN)
            return gamecontroller_to_keyboard(&event);
    }
    return SDLK_UNKNOWN;
}

void set_input_command_key(InputCommand command, SDL_Keycode keycode)
{
    switch (command)
    {
        case CMD_KEY_UP : cfg_up_key = keycode; break;
        case CMD_KEY_DOWN : cfg_down_key = keycode; break;
        case CMD_KEY_LEFT : cfg_left_key = keycode; break;
        case CMD_KEY_RIGHT : cfg_right_key = keycode; break;
        case CMD_KEY_JUMP : cfg_jump_key = keycode; break;
        case CMD_KEY_BOMB : cfg_bomb_key = keycode; break;
        case CMD_KEY_OTHER : break;
        default : break;
    }
}

SDL_Keycode get_input_command_key(InputCommand command)
{
    switch (command)
    {
        case CMD_KEY_UP : return cfg_up_key;
        case CMD_KEY_DOWN : return cfg_down_key;
        case CMD_KEY_LEFT : return cfg_left_key;
        case CMD_KEY_RIGHT : return cfg_right_key;
        case CMD_KEY_JUMP : return cfg_jump_key;
        case CMD_KEY_BOMB : return cfg_bomb_key;
        case CMD_KEY_OTHER : break;
        default : break;
    }

    return SDLK_UNKNOWN;
}

const char *get_command_key_string(InputCommand command)
{
    switch (command)
    {
        case CMD_KEY_UP : return scancode_to_string(keycode_to_scancode(cfg_up_key));
        case CMD_KEY_DOWN : return scancode_to_string(keycode_to_scancode(cfg_down_key));
        case CMD_KEY_LEFT : return scancode_to_string(keycode_to_scancode(cfg_left_key));
        case CMD_KEY_RIGHT : return scancode_to_string(keycode_to_scancode(cfg_right_key));
        case CMD_KEY_JUMP : return scancode_to_string(keycode_to_scancode(cfg_jump_key));
        case CMD_KEY_BOMB : return scancode_to_string(keycode_to_scancode(cfg_bomb_key));
        case CMD_KEY_OTHER : break;
        default : break;
    }

    return scancode_to_string(0);
}

void flush_input()
{
    SDL_PumpEvents();
    SDL_FlushEvents(SDL_KEYDOWN, SDL_KEYUP);
}

bool is_return_key(SDL_Keycode key)
{
    return (key == SDLK_RETURN || key == SDLK_KP_ENTER || key == SDLK_RETURN2);
}
