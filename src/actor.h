#ifndef COSMO_ENGINE_ACTOR_H
#define COSMO_ENGINE_ACTOR_H

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

void actor_add_new(int image_index, int x_pos, int y_pos);
int actor_init(int actor_num, int image_index, int x, int y_pos);

#endif //COSMO_ENGINE_ACTOR_H