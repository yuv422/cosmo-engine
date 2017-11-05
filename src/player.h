
#ifndef COSMO_ENGINE_PLAYER_H
#define COSMO_ENGINE_PLAYER_H

//Data
extern int player_is_grabbing_wall_flag;
extern int player_death_counter;
extern int player_walk_anim_index;
extern int player_is_being_pushed_flag;
extern int player_hanging_on_wall_direction;

extern int player_y_pos;
extern int player_x_pos;
extern int player_direction;
extern int player_direction_related_32E98;

extern int player_sprite_dir_frame_offset;
extern int player_input_jump_related_flag;

extern int player_bounce_height_counter;
extern int player_bounce_flag_maybe;

extern int is_standing_slipry_slope_left_flg;
extern int is_standing_slipry_slope_right_flg;

extern int num_bombs;
extern int has_had_bomb_flag;

extern int teleporter_state_maybe;
extern int player_is_teleporting_flag;
extern int teleporter_counter;

extern uint8 player_in_pneumatic_tube_flag;

extern int player_invincibility_counter;

extern int player_fall_off_map_bottom_counter;

extern int num_hits_since_touching_ground;

extern uint8 word_28BEA;
extern int word_28F7E;
extern int word_28F94;
extern int word_2E180;
extern int word_2E1F8;
extern int word_2E1DE;
extern int word_2E214;
extern int word_32B88;
extern int word_32EAC;
extern int word_32EB2;

extern unsigned char byte_2E182;
extern unsigned char byte_2E2E4;


void handle_player_input_maybe();

void sub_11062(); //resets variables

void player_reset_push_variables();

#endif //COSMO_ENGINE_PLAYER_H
