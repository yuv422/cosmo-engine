#ifndef COSMO_ENGINE_ACTOR_H
#define COSMO_ENGINE_ACTOR_H

#include "defines.h"

#define MAX_ACTORS 410

typedef struct
{
    int actorInfoIndex;
    int frame_num;
    int x;
    int y;
    int update_while_off_screen_flag;
    int can_update_if_goes_off_screen_flag;
    int non_blocking_flag_maybe;
    int can_fall_down_flag;
    int has_moved_left_flag;
    int has_moved_right_flag;
    int data_1;
    int data_2;
    int data_3;
    int data_4;
    int data_5;
    int is_deactivated_flag_maybe;
    int falling_counter;
    int count_down_timer;
    int func_offset;
    int func_seg;
} ActorData;

typedef struct
{
    uint16 x;
    uint16 y;
    uint16 map_tiles[5];
} MovingPlatform;

typedef struct
{
    uint16 x;
    uint16 y;
    uint16 direction;
    uint16 length_counter;
    uint16 current_height;
    uint16 max_height;
    uint16 pause_counter;
} MudFountain;

typedef struct
{
    int type;
    int x;
    int y;
} Brightness;

//Data
extern int total_num_actors;
extern uint16 word_2E22A;
extern uint16 word_2E236;
extern uint16 word_2E228;
extern uint16 word_2E220;
extern uint16 word_2E238;
extern uint16 word_2E21E;
extern uint16 word_2E24C;
extern uint16 word_2E23C;
extern uint16 word_2E232;
extern uint16 word_2E234;
extern uint16 word_2E246;

extern uint8 byte_32EB8;

extern uint16 word_32EC2;

extern uint8 energy_beam_enabled_flag;

extern uint16 word_2E1E4;

extern uint16 word_2E1E2;

extern uint16 num_moving_platforms;
extern uint16 num_mud_fountains;
extern uint16 num_brightness_objs;
extern uint16 word_2E4CE;
extern uint16 obj_switch_151_flag;

extern MovingPlatform moving_platform_tbl[10];

void actor_add_new(int image_index, int x_pos, int y_pos);
int actor_init(int actor_num, int image_index, int x, int y_pos);
void load_actor(int actor_num, int actorType, int x_pos, int y_pos);
void actor_load_tiles();

#endif //COSMO_ENGINE_ACTOR_H