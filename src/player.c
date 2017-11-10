#include "actor.h"
#include "dialog.h"
#include "hud.h"
#include "sfx.h"
#include "map.h"
#include "input.h"
#include "tile.h"
#include "util.h"

int player_is_grabbing_wall_flag = 0;
int player_death_counter = 0;
int player_walk_anim_index = 0;
int player_is_being_pushed_flag = 0;
int player_hanging_on_wall_direction = 0;

int player_y_pos = 0;
int player_x_pos = 0;
int player_direction = 0;
int player_direction_related_32E98 = 0;

int player_sprite_dir_frame_offset = 0;
int player_input_jump_related_flag = 0;

int player_bounce_height_counter = 0;
int player_bounce_flag_maybe = 0;

int is_standing_slipry_slope_left_flg = 0;
int is_standing_slipry_slope_right_flg = 0;

int num_bombs = 0;
int has_had_bomb_flag = 0;

int teleporter_state_maybe = 0;
int player_is_teleporting_flag = 0;
int teleporter_counter = 0;

uint8 player_in_pneumatic_tube_flag = 0;

int player_invincibility_counter = 0;

int player_fall_off_map_bottom_counter = 0;
int num_hits_since_touching_ground = 0;

uint16 player_push_direction = 0;
uint16 player_push_anim_duration_maybe = 0;
uint16 player_push_anim_counter = 0;
uint16 player_push_duration = 0;
uint16 player_push_frame_num = 0;
uint16 player_dont_push_while_jumping_flag = 0;

uint8 word_28BEA;
int word_28F7E;
int word_28F94;
int word_2E180;
int word_2E1F8;
int word_2E1DE;
int word_2E214;
int word_32B88;
int word_32EAC;
int word_32EB2;

unsigned char byte_2E182;
unsigned char byte_2E2E4;

Tile *player_tiles;

typedef enum {
    NOT_BLOCKED = 0,
    BLOCKED = 1,
    SLOPE = 2
} BlockingType;

BlockingType player_check_movement(int direction, int x_pos, int y_pos)
{
// node 00011b54-00011b78 #insn=7 use={} def={} in={} out={} pred={} FALLTHROUGH follow=00011e3f
        is_standing_slipry_slope_left_flg = 0;
        is_standing_slipry_slope_right_flg = 0;
        switch (direction) {
// node ffffffff-00000000 #insn=0 use={} def={} in={} out={} pred={}
// node 00011b85-00011bc1 #insn=7 use={cx, di, cl} def={ax, cx, bx, si} in={cx, di, cl} out={si} pred={ FFFFFFFF} JUMP target=00011be2
            case 0:
                if (player_y_pos - 3 == 0 || player_y_pos - 2 == 0) {
                    return BLOCKED;
                }

                for(int i=0;i<3;i++)
                {
                    tileattr_mni_data[map_get_tile_cell(x_pos, y_pos - 4) / 8] & TILE_ATTR_BLOCK_UP
                }
                map_data_ptr[2] = REGISTER_29;
                map_data_ptr = &temp_data_buffer + (y_pos - 4 << cl << 1) + (x_pos << 1);
                si = 0;
                goto loc_11BE2;

// node 00011bc3-00011be1 #insn=3 use={si} def={si} in={si} out={si} pred={ 11BE2} FALLTHROUGH follow=00011be2
            loc_11BC3:
                if ((*(&tileattr_mni_data + (*(map_data_ptr + (si << 1)) >> 3)) & 2) != 0) {
                    ax = 1;
                    return ax;
                }
                si = si + 1;

// node 00011be2-00011be5 #insn=2 use={si} def={} in={si} out={si} pred={ 11B85 11BC3} CONDJUMP target=00011bc3 follow=00011e3d
            loc_11BE2:
                if (si < 3) goto loc_11BC3;

// node 00011bea-00011bf4 #insn=2 use={} def={ax} in={cx, di, cl} out={cx, di, cl} pred={ FFFFFFFF} CONDJUMP target=00011bf9 follow=00011e3d
            case 1:
                if (map_max_y_offset + 0x12 != player_y_pos) goto loc_11BF9;

// node 00011bf9-00011ca2 #insn=9 use={} def={si} in={} out={si} pred={ 11BEA} JUMP target=00011ced
            loc_11BF9:
                bx = &temp_data_buffer + (y_pos << cl << 1) + (x_pos << 1);
                map_data_ptr[2] = REGISTER_29;
                map_data_ptr = bx;
                ax = *bx >> 3;
                if ((*(&tileattr_mni_data + ax) & 1) == 0 && (*(&tileattr_mni_data + (*map_data_ptr >> 3)) & 0x40) != 0 &&
                    (*(&tileattr_mni_data + (*map_data_ptr >> 3)) & 0x10) != 0) {
                    is_standing_slipry_slope_left_flg = 1;
                }
                if ((*(&tileattr_mni_data + (*(map_data_ptr + 4) >> 3)) & 1) == 0 &&
                    (*(&tileattr_mni_data + (*(map_data_ptr + 4) >> 3)) & 0x40) != 0 &&
                    (*(&tileattr_mni_data + (*(map_data_ptr + 4) >> 3)) & 0x10) != 0) {
                    is_standing_slipry_slope_right_flg = 1;
                }
                si = 0;
                goto loc_11CED;

// node 00011ca4-00011cbd #insn=2 use={si} def={ax, bx} in={si} out={si} pred={ 11CED} CONDJUMP target=00011cc8 follow=00011cbf
            loc_11CA4:
                if ((*(&tileattr_mni_data + (*(map_data_ptr + (si << 1)) >> 3)) & 0x40) == 0) goto loc_11CC8;

// node 00011cbf-00011cc5 #insn=2 use={} def={} in={} out={} pred={ 11CA4} JUMP target=00011e2a
                num_hits_since_touching_ground = 0;
                goto loc_11E2A;

// node 00011cc8-00011cec #insn=3 use={si} def={si} in={si} out={si} pred={ 11CA4} FALLTHROUGH follow=00011ced
            loc_11CC8:
                if ((*(&tileattr_mni_data + (*(map_data_ptr + (si << 1)) >> 3)) & 1) != 0) {
                    num_hits_since_touching_ground = 0;
                    ax = 1;
                    return ax;
                }
                si = si + 1;

// node 00011ced-00011cf0 #insn=2 use={si} def={} in={si} out={si} pred={ 11BF9 11CC8} CONDJUMP target=00011ca4 follow=00011e3d
            loc_11CED:
                if (si < 3) goto loc_11CA4;

// node 00011cf5-00011d34 #insn=8 use={cx, di, al, cl} def={ax, cx, bx, si} in={cx, di, al, cl} out={si} pred={ FFFFFFFF} JUMP target=00011d8f
            case 2:
                bx = &temp_data_buffer + (y_pos << cl << 1) + (x_pos << 1);
                map_data_ptr[2] = REGISTER_29;
                map_data_ptr = bx;
                ax = *(bx - (map_width_in_tiles << 1 << 1)) >> 3;
                player_is_grabbing_wall_flag = al & 0x80;
                si = 0;
                goto loc_11D8F;

// node 00011d36-00011d50 #insn=3 use={si} def={} in={si} out={si} pred={ 11D8F} CONDJUMP target=00011d86 follow=00011e2a
            loc_11D36:
                if ((*(&tileattr_mni_data + (*map_data_ptr >> 3)) & 4) != 0) {
                    ax = 1;
                    return ax;
                }
                if (si != 0 || (*(&tileattr_mni_data + (*map_data_ptr >> 3)) & 0x40) == 0 ||
                    (*(&tileattr_mni_data + (*(map_data_ptr - (map_width_in_tiles << 1)) >> 3)) & 4) != 0)
                    goto loc_11D86;

// node 00011d86-00011d8e #insn=3 use={si} def={ax, si} in={si} out={si} pred={ 11D36} FALLTHROUGH follow=00011d8f
            loc_11D86:
                map_data_ptr = map_data_ptr - (map_width_in_tiles << 1);
                si = si + 1;

// node 00011d8f-00011d92 #insn=2 use={si} def={} in={si} out={si} pred={ 11CF5 11D86} CONDJUMP target=00011d36 follow=00011e3d
            loc_11D8F:
                if (si < 5) goto loc_11D36;

// node 00011d97-00011dd9 #insn=8 use={cx, di, al, cl} def={ax, cx, bx, si} in={cx, di, al, cl} out={si} pred={ FFFFFFFF} JUMP target=00011e38
            case 3:
                bx = &temp_data_buffer + (y_pos << cl << 1) + (x_pos << 1) + 4;
                map_data_ptr[2] = REGISTER_29;
                map_data_ptr = bx;
                ax = *(bx - (map_width_in_tiles << 1 << 1)) >> 3;
                player_is_grabbing_wall_flag = al & 0x80;
                si = 0;
                goto loc_11E38;

// node 00011ddb-00011df7 #insn=3 use={si} def={} in={si} out={si} pred={ 11E38} CONDJUMP target=00011e2f follow=00011e2a
            loc_11DDB:
                if ((*(&tileattr_mni_data + (*map_data_ptr >> 3)) & 8) != 0) {
                    return BLOCKED;
                }
                if (si != 0 || (*(&tileattr_mni_data + (*map_data_ptr >> 3)) & 0x40) == 0 ||
                    (*(&tileattr_mni_data + (*(map_data_ptr - (map_width_in_tiles << 1)) >> 3)) & 8) != 0)
                    goto loc_11E2F;

// node 00011e2a-00011e3f #insn=2 use={} def={ax} in={} out={ax} pred={ 11CBF 11D36 11DDB} JUMP target=00011e3f
                ax = SLOPE;
                break;

// node 00011e2f-00011e37 #insn=3 use={si} def={ax, si} in={si} out={si} pred={ 11DDB} FALLTHROUGH follow=00011e38
            loc_11E2F:
                map_data_ptr = map_data_ptr - (map_width_in_tiles << 1);
                si = si + 1;

// node 00011e38-00011e3b #insn=2 use={si} def={} in={si} out={si} pred={ 11D97 11E2F} CONDJUMP target=00011ddb follow=00011e3d
            loc_11E38:
                if (si < 5) goto loc_11DDB;

// node 00011e3d-00011e3f #insn=2 use={} def={ax} in={} out={ax} pred={ 11BE2 11BEA 11CED 11D8F 11E38} FALLTHROUGH follow=00011e3f
                ax = NOT_BLOCKED;
                break;

// node 00011e3f-00000000 #insn=0 use={} def={} in={} out={} pred={ 11E2A 11E3D}
        }

// node 00011e3f-00011e42 #insn=4 use={ax} def={si, di} in={ax} out={} pred={ 11B54} RETURN
        loc_11E3F:
/* pop  */
/* pop  */
        return ax;
    }

void push_player()
{
    //FIXME
}

sint16 word_28F80[10] = {-2, -1, -1, -1, -1, -1, -1, 0, 0, 0};

void handle_player_input_maybe()
{
    static int local_bomb_key_counter = 0;
    int var_4=0;
    int top_bomb_check_flag = 0;
    BlockingType player_movement_status = NOT_BLOCKED;

    int si = 0;
    player_is_grabbing_wall_flag = 0;
    if(player_death_counter != 0 || teleporter_state_maybe != 0 || word_32B88 != 0 || player_walk_anim_index != 0 || word_2E1F8 != 0)
    {
        return;
    }
    word_28F94 = word_28F94 + 1;
    push_player();
    if(player_is_being_pushed_flag != 0)
    {
        player_hanging_on_wall_direction = 0;
        return;
    }
    if(player_hanging_on_wall_direction != 0)
    {
        int tile_cell = 0;
        if(player_hanging_on_wall_direction != 2)
        {
            tile_cell = map_get_tile_cell(player_x_pos + 3, player_y_pos - 2);
        }
        else
        {
            tile_cell = map_get_tile_cell(player_x_pos - 1, player_y_pos - 2);
        }
        if((tileattr_mni_data[tile_cell >> 3] & TILE_ATTR_SLIPPERY) != 0 & (tileattr_mni_data[tile_cell >> 3] & TILE_ATTR_CAN_GRAB_WALL) != 0)
        {
            if(player_check_movement(1, player_x_pos, player_y_pos + 1) == NOT_BLOCKED)
            {
                player_y_pos = player_y_pos + 1;
                si = 1;
                if(player_hanging_on_wall_direction != 2)
                {
                    tile_cell = map_get_tile_cell(player_x_pos + 3, player_y_pos - 2);
                }
                else
                {
                    tile_cell = map_get_tile_cell(player_x_pos - 1, player_y_pos - 2);
                }

                if((tileattr_mni_data[tile_cell >> 3] & TILE_ATTR_SLIPPERY) == 0)
                {
                    if((tileattr_mni_data[tile_cell >> 3] & TILE_ATTR_CAN_GRAB_WALL) == 0)
                    {
                        player_hanging_on_wall_direction = 0;
                        si = 0;
                        //goto loc_1DD63;
                    }
                }
            }
            else
            {
                player_hanging_on_wall_direction = 0;
            }
        }
        else
        {
            if((tileattr_mni_data[tile_cell >> 3] & TILE_ATTR_CAN_GRAB_WALL) == 0)
            {
                player_hanging_on_wall_direction = 0;
            }
        }
    }
    if(player_hanging_on_wall_direction == 0)
    {
        if(bomb_key_pressed == 0)
        {
            local_bomb_key_counter = 0;
        }
        if(bomb_key_pressed != 0 && local_bomb_key_counter == 0)
        {
            local_bomb_key_counter = 2;
        }
        if(local_bomb_key_counter != 0 && local_bomb_key_counter != 1)
        {
            local_bomb_key_counter = local_bomb_key_counter - 1;
            if(local_bomb_key_counter == 1)
            {
                if(player_direction == 0)
                {
                    uint8 tile_attr = tileattr_mni_data[map_get_tile_cell(player_x_pos - 1, player_y_pos - 2) >> 3];
                    top_bomb_check_flag = tile_attr & TILE_ATTR_BLOCK_LEFT;
                    tile_attr = tileattr_mni_data[map_get_tile_cell(player_x_pos - 2, player_y_pos - 2) >> 3];
                    int bottom_bomb_check_flag = tile_attr & TILE_ATTR_BLOCK_LEFT;

                    if(num_bombs != 0 || has_had_bomb_flag != 0)
                    {
                        if(top_bomb_check_flag != 0)
                        {
                            play_sfx(0x1c);
                        }
                        else
                        {
                            if(bottom_bomb_check_flag != 0)
                            {
                                play_sfx(0x1c);
                            }
                            else
                            {
                                if(num_bombs <= 0)
                                {
                                    play_sfx(0x1c);
                                }
                                else
                                {
                                    actor_add_new(0x18, player_x_pos - 2, player_y_pos - 2);
                                    num_bombs = num_bombs - 1;
                                    display_num_bombs_left();
                                    play_sfx(0x1d);
                                }
                            }
                        }
                    }
                    else
                    {
                        has_had_bomb_flag = 1;
                        you_havent_found_any_bombs_dialog();
                    }
                }
                else
                {
                    uint8 tile_attr = tileattr_mni_data[map_get_tile_cell(player_x_pos + 3, player_y_pos - 2) >> 3];
                    top_bomb_check_flag = tile_attr & TILE_ATTR_BLOCK_RIGHT;
                    tile_attr = tileattr_mni_data[map_get_tile_cell(player_x_pos + 4, player_y_pos - 2) >> 3];
                    int bottom_bomb_check_flag = tile_attr & TILE_ATTR_BLOCK_RIGHT;

                    if(num_bombs == 0 && has_had_bomb_flag == 0)
                    {
                        has_had_bomb_flag = 1;
                        you_havent_found_any_bombs_dialog();
                    }
                    if(top_bomb_check_flag != 0)
                    {
                        play_sfx(0x1c);
                    }
                    else
                    {
                        if(bottom_bomb_check_flag == 0)
                        {
                            if(num_bombs > 0)
                            {
                                actor_add_new(0x18, player_x_pos + 3, player_y_pos - 2);
                                num_bombs = num_bombs - 1;
                                display_num_bombs_left();
                                play_sfx(0x1d);
                            }
                            else
                            {
                                play_sfx(0x1c);
                            }
                        }
                        else
                        {
                            play_sfx(0x1c);
                        }
                    }
                }
            }
        }
        else
        {
            bomb_key_pressed = 0;
        }
    }
    if(byte_2E182 != 0 || bomb_key_pressed == 0 || byte_2E2E4 != 0 || player_hanging_on_wall_direction != 0 || jump_key_pressed != 0 && player_input_jump_related_flag == 0)
    {
        word_2E214 = 0;
        //ax = player_check_movement(1, player_x_pos, player_y_pos + 1);
        if(is_standing_slipry_slope_left_flg == 0 || is_standing_slipry_slope_right_flg == 0)
        {
            if(is_standing_slipry_slope_right_flg != 0)
            {
                if(player_hanging_on_wall_direction == 0)
                {
                    player_x_pos = player_x_pos - 1;
                }
                if(player_check_movement(1, player_x_pos, player_y_pos + 1) == 0 && player_hanging_on_wall_direction == 0)
                {
                    player_y_pos = player_y_pos + 1;
                }
                if(player_y_pos - mapwindow_y_offset > 14)
                {
                    mapwindow_y_offset = mapwindow_y_offset + 1;
                }
                if(player_x_pos - mapwindow_x_offset < 12 && mapwindow_x_offset > 0)
                {
                    mapwindow_x_offset = mapwindow_x_offset - 1;
                }
                player_hanging_on_wall_direction = 0;
            }
            if(is_standing_slipry_slope_left_flg != 0)
            {
                if(player_hanging_on_wall_direction == 0)
                {
                    player_x_pos = player_x_pos + 1;
                }
                if(player_check_movement(1, player_x_pos, player_y_pos + 1) == 0 && player_hanging_on_wall_direction == 0)
                {
                    player_y_pos = player_y_pos + 1;
                }
                if(player_y_pos - mapwindow_y_offset > 14)
                {
                    mapwindow_y_offset = mapwindow_y_offset + 1;
                }
                if(player_x_pos - mapwindow_x_offset > 0x17)
                {
                    if(map_width_in_tiles - 38 > mapwindow_x_offset)
                    {
                        mapwindow_x_offset = mapwindow_x_offset + 1;
                    }
                }
                player_hanging_on_wall_direction = 0;
            }
        }
        if(left_key_pressed != 0 && player_hanging_on_wall_direction == 0 && right_key_pressed == 0)
        {
            BlockingType di = player_check_movement(1, player_x_pos, player_y_pos + 1);

            if(player_direction_related_32E98 != 2)
            {
                player_direction_related_32E98 = 2;
            }
            else
            {
                player_x_pos = player_x_pos - 1;
            }
            player_direction = 0;
            if(player_x_pos >= 1)
            {
                player_movement_status = player_check_movement(2, player_x_pos, player_y_pos);
                if(player_movement_status == BLOCKED)
                {
                    player_x_pos = player_x_pos + 1;
                    if(player_check_movement(1, player_x_pos, player_y_pos + 1) == NOT_BLOCKED && player_is_grabbing_wall_flag != 0)
                    {
                        player_hanging_on_wall_direction = 2;
                        player_bounce_flag_maybe = 0;
                        player_bounce_height_counter = 0;
                        play_sfx(4);
                        byte_2E2E4 = 0;
                        byte_2E182 = 0;
                        word_2E180 = 0;
                        if(jump_key_pressed == 0)
                        {
                            player_input_jump_related_flag = 0;
                        }
                        else
                        {
                            player_input_jump_related_flag = 1;
                        }
                    }
                }
            }
            else
            {
                player_x_pos = player_x_pos + 1;
            }
            if(player_movement_status != 2)
            {
                if(di == SLOPE)
                {
                    if(player_check_movement(1, player_x_pos, player_y_pos + 1) == NOT_BLOCKED)
                    {
                        byte_2E2E4 = 0;
                        byte_2E182 = 0;
                        player_y_pos = player_y_pos + 1;
                    }
                }
            }
            else
            {
                player_y_pos = player_y_pos - 1;
            }
        }
        if(right_key_pressed != 0 && player_hanging_on_wall_direction == 0 && left_key_pressed == 0)
        {
            BlockingType di = player_check_movement(1, player_x_pos, player_y_pos + 1);
            if(player_direction_related_32E98 != 3)
            {
                player_direction_related_32E98 = 3;
            }
            else
            {
                player_x_pos = player_x_pos + 1;
            }
            player_direction = 0x17;
            if(map_width_in_tiles - 4 >= player_x_pos)
            {
                player_movement_status = player_check_movement(3, player_x_pos, player_y_pos);
                if(player_movement_status == BLOCKED)
                {
                    player_x_pos = player_x_pos - 1;
                    if(player_check_movement(1, player_x_pos, player_y_pos + 1) == NOT_BLOCKED && player_is_grabbing_wall_flag != 0)
                    {
                        player_hanging_on_wall_direction = 3;
                        player_bounce_flag_maybe = 0;
                        player_bounce_height_counter = 0;
                        play_sfx(4);
                        byte_2E182 = 0;
                        byte_2E2E4 = 0;
                        word_2E180 = 0;
                        if(jump_key_pressed == 0)
                        {
                            player_input_jump_related_flag = 0;
                        }
                        else
                        {
                            player_input_jump_related_flag = 1;
                        }
                    }
                }
            }
            else
            {
                player_x_pos = player_x_pos - 1;
            }
            if(player_movement_status != 2)
            {
                if(di == SLOPE)
                {
                    if(player_check_movement(1, player_x_pos, player_y_pos + 1) == NOT_BLOCKED)
                    {
                        byte_2E2E4 = 0;
                        word_2E180 = 0;
                        player_y_pos = player_y_pos + 1;
                    }
                }
            }
            else
            {
                player_y_pos = player_y_pos - 1;
            }
        }
        if(player_hanging_on_wall_direction != 0 && player_input_jump_related_flag != 0 && jump_key_pressed == 0)
        {
            player_input_jump_related_flag = 0;
        }
        if(player_bounce_height_counter != 0 || jump_key_pressed != 0 && byte_2E2E4 == 0 && player_input_jump_related_flag == 0 || player_hanging_on_wall_direction != 0 && jump_key_pressed != 0 && player_input_jump_related_flag == 0)
        {
            if(player_bounce_flag_maybe != 0 && player_bounce_height_counter > 0)
            {
                player_bounce_height_counter = player_bounce_height_counter - 1;
                if(player_bounce_height_counter < 10)
                {
                    word_2E1DE = 0;
                }
                if(player_bounce_height_counter > 1)
                {
                    player_y_pos = player_y_pos - 1;
                }
                if(player_bounce_height_counter > 13)
                {
                    player_bounce_height_counter = player_bounce_height_counter - 1;
                    if(player_check_movement(0, player_x_pos, player_y_pos) != 0)
                    {
                        word_2E1DE = 0;
                    }
                    else
                    {
                        player_y_pos = player_y_pos - 1;
                    }
                }
                var_4 = 0;
                if(player_bounce_height_counter == 0)
                {
                    byte_2E182 = 0;
                    player_bounce_flag_maybe = 0;
                    word_2E180 = 0;
                    word_2E1DE = 0;
                    player_input_jump_related_flag = 1;
                }
            }
            else
            {
                if(player_hanging_on_wall_direction == 2)
                {
                    if(left_key_pressed == 0)
                    {
                        if(right_key_pressed != 0)
                        {
                            player_direction = 0x17;
                        }
                    }
                    else
                    {
                        player_hanging_on_wall_direction = 0;
                    }
                }
                if(player_hanging_on_wall_direction == 3)
                {
                    if(right_key_pressed == 0)
                    {
                        if(left_key_pressed != 0)
                        {
                            player_direction = 0;
                        }
                    }
                    else
                    {
                        player_hanging_on_wall_direction = 0;
                    }
                }
                if(player_hanging_on_wall_direction == 0)
                {
                    player_y_pos = player_y_pos + word_28F80[byte_2E182];
                }
                if(byte_2E182 == 0 && player_check_movement(0, player_x_pos, player_y_pos + 1) != 0)
                {
                    player_y_pos = player_y_pos + 1;
                }
                player_bounce_flag_maybe = 0;
                var_4 = 1;
            }
            player_hanging_on_wall_direction = 0;
            BlockingType blockingCheck = player_check_movement(0, player_x_pos, player_y_pos);
            if(blockingCheck == NOT_BLOCKED)
            {
                if(var_4 != 0 && byte_2E182 == 0)
                {
                    play_sfx(2);
                }
            }
            else
            {
                if(byte_2E182 > 0 || player_bounce_flag_maybe != 0)
                {
                    //loc_1E420:
                    play_sfx(5);
                }
                player_bounce_height_counter = 0;
                player_bounce_flag_maybe = 0;
                blockingCheck = player_check_movement(0, player_x_pos, player_y_pos + 1);
                if(blockingCheck != NOT_BLOCKED)
                {
                    player_y_pos = player_y_pos + 1;
                }
                player_y_pos = player_y_pos + 1;
                byte_2E2E4 = 1;
                if(jump_key_pressed != 0)
                {
                    player_input_jump_related_flag = 1;
                }
                word_2E180 = 0;
                word_2E1DE = 0;
            }
            if(player_bounce_flag_maybe == 0)
            {
                if(byte_2E182 > 6)
                {
                    byte_2E2E4 = 1;
                    if(jump_key_pressed != 0)
                    {
                        player_input_jump_related_flag = 1;
                    }
                    word_2E180 = 0;
                }
                byte_2E182++;
            }
        }
        if(player_hanging_on_wall_direction == 0)
        {
            if(byte_2E2E4 != 0 && jump_key_pressed != 0)
            {
                player_input_jump_related_flag = 1;
            }
            if((jump_key_pressed == 0 || player_input_jump_related_flag != 0) && byte_2E2E4 == 0)
            {
                byte_2E2E4 = 1;
                word_2E180 = 0;
            }
            if(byte_2E2E4 != 0 && player_bounce_flag_maybe == 0)
            {
                player_y_pos = player_y_pos + 1;
                if(player_check_movement(1, player_x_pos, player_y_pos) != NOT_BLOCKED)
                {
                    if(word_2E180 != 0)
                    {
                        play_sfx(3);
                    }
                    byte_2E2E4 = 0;
                    player_y_pos = player_y_pos - 1;
                    byte_2E182 = 0;
                    if(jump_key_pressed == 0)
                    {
                        player_input_jump_related_flag = 0;
                    }
                    else
                    {
                        player_input_jump_related_flag = 1;
                    }
                    word_2E180 = 0;
                }
                if(word_2E180 > 3)
                {
                    player_y_pos = player_y_pos + 1;
                    mapwindow_y_offset = mapwindow_y_offset + 1;
                    if(player_check_movement(1, player_x_pos, player_y_pos) != NOT_BLOCKED)
                    {
                        play_sfx(3);
                        byte_2E2E4 = 0;
                        player_y_pos = player_y_pos - 1;
                        mapwindow_y_offset = mapwindow_y_offset - 1;
                        byte_2E182 = 0;
                        if(jump_key_pressed == 0)
                        {
                            player_input_jump_related_flag = 0;
                        }
                        else
                        {
                            player_input_jump_related_flag = 1;
                        }
                        word_2E180 = 0;
                    }
                }
                if(word_2E180 < 0x19)
                {
                    word_2E180 = word_2E180 + 1;
                }
            }
            if(byte_2E2E4 != 0 && word_2E180 == 1 && player_bounce_flag_maybe == 0)
            {
                player_y_pos = player_y_pos - 1;
            }
        }
    }
    else
    {
        if(left_key_pressed == 0)
        {
            if(right_key_pressed == 0)
            {
                if(player_direction_related_32E98 != 2)
                {
                    if(player_direction_related_32E98 == 3)
                    {
                        word_2E214 = 3;
                    }
                }
                else
                {
                    word_2E214 = 2;
                }
            }
            else
            {
                player_direction_related_32E98 = 3;
                word_2E214 = 3;
                player_direction = 0x17;
            }
        }
        else
        {
            player_direction_related_32E98 = 2;
            word_2E214 = 2;
            player_direction = 0;
        }
    }
    if (word_2E214 == 0) //goto loc_1E5DC;
    {
// node 0001e5dc-0001e5e1 #insn=2 use={} def={} in={ax, si, al, dl} out={ax, si, al, dl} pred={ 1DC0F} CONDJUMP target=0001e615 follow=0001e6bd
        //loc_1E5DC:
        if ((up_key_pressed != 0 || down_key_pressed != 0) && left_key_pressed == 0 && right_key_pressed == 0 &&
            byte_2E2E4 == 0 && jump_key_pressed == 0)
        {
// node 0001e615-0001e6a9 #insn=6 use={} def={} in={} out={} pred={ 1E5DC} FALLTHROUGH follow=0001e96f
            //loc_1E615:
            word_28F7E = 0;
            if (up_key_pressed != 0 && player_is_teleporting_flag == 0 && word_32EAC == 0)
            {
                if (mapwindow_y_offset > 0 && player_y_pos - mapwindow_y_offset < 0x11)
                {
                    mapwindow_y_offset = mapwindow_y_offset - 1;
                }
                if (si != 0)
                {
                    mapwindow_y_offset = mapwindow_y_offset + 1;
                }
                if (player_hanging_on_wall_direction == 0)
                {
                    player_sprite_dir_frame_offset = 5;
                }
                else
                {
                    player_sprite_dir_frame_offset = 11;
                }
                return;
            }
            if (down_key_pressed == 0)
            {
                return;
            }
            if (mapwindow_y_offset + 3 < player_y_pos)
            {
                mapwindow_y_offset = mapwindow_y_offset + 1;
                if ((si != 0 || is_standing_slipry_slope_left_flg != 0 || is_standing_slipry_slope_right_flg != 0) &&
                    mapwindow_y_offset + 3 < player_y_pos)
                {
                    mapwindow_y_offset = mapwindow_y_offset + 1;
                }
            }
            if (player_hanging_on_wall_direction == 0)
            {
                player_sprite_dir_frame_offset = 6;
            }
            else
            {
                player_sprite_dir_frame_offset = 12;
            }
            return;
        }

        // node 0001e6bd-0001e6c2 #insn=2 use={} def={} in={} out={} pred={ 1E5DC} FALLTHROUGH follow=0001e8d8
        //loc_1E6BD:
        if(player_hanging_on_wall_direction != 2)
        {
            if(player_hanging_on_wall_direction != 3)
            {
                if((byte_2E2E4 == 0 || player_bounce_flag_maybe != 0) && (byte_2E182 <= 6 || byte_2E2E4 != 0))
                {
                    if((jump_key_pressed == 0 || player_input_jump_related_flag != 0) && player_bounce_flag_maybe == 0)
                    {
                        if(left_key_pressed == right_key_pressed)
                        {
                            uint8 rvalue = (uint8)(_rand() % 0x32);

                            player_sprite_dir_frame_offset = 4;
                            if(left_key_pressed == 0 && right_key_pressed == 0 && byte_2E2E4 == 0)
                            {
                                word_28F7E = word_28F7E + 1;
                                if(word_28F7E <= 0x64 || word_28F7E >= 0x6e)
                                {
                                    if(word_28F7E <= 0x8b || word_28F7E >= 0x96)
                                    {
                                        if(word_28F7E == 0xb4)
                                        {
                                            player_sprite_dir_frame_offset = 0x13;
                                        }
                                        else
                                        {
                                            if(word_28F7E == 0xb5)
                                            {
                                                player_sprite_dir_frame_offset = 0x14;
                                            }
                                            else
                                            {
                                                if(word_28F7E != 0xb6)
                                                {
                                                    if(word_28F7E != 0xb7)
                                                    {
                                                        if(word_28F7E != 0xb8)
                                                        {
                                                            if(word_28F7E == 0xb9)
                                                            {
                                                                word_28F7E = 0;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            player_sprite_dir_frame_offset = 0x13;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        player_sprite_dir_frame_offset = 0x14;
                                                    }
                                                }
                                                else
                                                {
                                                    player_sprite_dir_frame_offset = 0x15;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        player_sprite_dir_frame_offset = 6;
                                    }
                                }
                                else
                                {
                                    player_sprite_dir_frame_offset = 5;
                                }
                            }
                            if(player_sprite_dir_frame_offset != 5 && player_sprite_dir_frame_offset != 6 && (rvalue == 0 || rvalue == 0x1f))
                            {
                                //loc_1E89B:
                                player_sprite_dir_frame_offset = 0x12;
                                //goto loc_1E8D8;
                            }
                        }
                        else
                        {
                            if(byte_2E2E4 == 0)
                            {
                                word_28F7E = 0;
                                if((word_28F94 & 1) != 0)
                                {
                                    if((player_sprite_dir_frame_offset & 1) != 0)
                                    {
                                        play_sfx(0x13);
                                    }
                                    player_sprite_dir_frame_offset = player_sprite_dir_frame_offset + 1;
                                }
                                if(player_sprite_dir_frame_offset > 3)
                                {
                                    player_sprite_dir_frame_offset = 0;
                                }
                            }
                        }
                    }
                    else
                    {
                        word_28F7E = 0;
                        player_sprite_dir_frame_offset = 7;
                        if(player_bounce_flag_maybe != 0 && word_2E1DE != 0)
                        {
                            player_sprite_dir_frame_offset = 0x16;
                        }
                        if(player_bounce_height_counter < 3 && player_bounce_flag_maybe != 0)
                        {
                            player_sprite_dir_frame_offset = 8;
                        }
                    }
                }
                else
                {
                    word_28F7E = 0;
                    if(player_bounce_flag_maybe != 0 || byte_2E2E4 != 0 || byte_2E182 <= 6)
                    {
                        if(word_2E180 < 10 || word_2E180 >= 0x19)
                        {
                            if(word_2E180 != 0x19)
                            {
                                if(byte_2E2E4 != 0)
                                {
                                    player_sprite_dir_frame_offset = 8;
                                }
                                else
                                {
                                    player_sprite_dir_frame_offset = 7;
                                }
                            }
                            else
                            {
                                player_sprite_dir_frame_offset = 0x10;
                                word_32EB2 = 1;
                            }
                        }
                        else
                        {
                            player_sprite_dir_frame_offset = 13;
                        }
                    }
                    else
                    {
                        player_sprite_dir_frame_offset = 8;
                    }
                }
            }
            else
            {
                word_28F7E = 0;
                if(left_key_pressed == 0)
                {
                    player_sprite_dir_frame_offset = 9;
                }
                else
                {
                    player_sprite_dir_frame_offset = 10;
                }
            }
        }
        else
        {
            word_28F7E = 0;
            if(right_key_pressed != 0)
            {
                player_sprite_dir_frame_offset = 10;
            }
            else
            {
                player_sprite_dir_frame_offset = 9;
            }
        }
    }
    else
    {
        // node 0001e5cd-0001e5d9 #insn=3 use={} def={} in={si} out={si} pred={ 1DC0F} JUMP target=0001e8d8
        word_28F7E = 0;
        player_sprite_dir_frame_offset = 14;
        //goto loc_1E8D8;
    }



// node 0001e8d8-0001e962 #insn=5 use={} def={} in={} out={} pred={ 1E5CD 1E6BD} FALLTHROUGH follow=0001e96f
    //loc_1E8D8:
    if(player_y_pos - mapwindow_y_offset > 14)
    {
        mapwindow_y_offset = mapwindow_y_offset + 1;
    }
    if(si == 0 || player_y_pos - mapwindow_y_offset <= 14)
    {
        if(player_bounce_height_counter > 10 && player_y_pos - mapwindow_y_offset < 7 && mapwindow_y_offset > 0)
        {
            mapwindow_y_offset = mapwindow_y_offset - 1;
        }
        if(player_y_pos - mapwindow_y_offset < 7 && mapwindow_y_offset > 0)
        {
            mapwindow_y_offset = mapwindow_y_offset - 1;
        }
    }
    else
    {
        mapwindow_y_offset = mapwindow_y_offset + 1;
    }
    if(player_x_pos - mapwindow_x_offset > 0x17 && map_width_in_tiles - 38 > mapwindow_x_offset && map_stride_bit_shift_amt > 5)
    {
        mapwindow_x_offset = mapwindow_x_offset + 1;
        return;
    }
    if(player_x_pos - mapwindow_x_offset < 12 && mapwindow_x_offset > 0)
    {
        mapwindow_x_offset = mapwindow_x_offset - 1;
        return;
    }

// node 0001e96f-0001e972 #insn=4 use={} def={si, di} in={} out={} pred={ 1E615 1E8D8} RETURN
    //loc_1E96F:
    /* pop  */
    /* pop  */
    return ;
}

void sub_11062()
{
    word_32EB2 = 0;
    player_walk_anim_index = 0;
    return;
}

void player_reset_push_variables()
{
    player_is_being_pushed_flag = 0;
    player_push_direction = 0;
    player_push_anim_duration_maybe = 0;
    player_push_anim_counter = 0;
    player_push_duration = 0;
    player_push_frame_num = 0;
    player_dont_push_while_jumping_flag = 0;
    player_bounce_flag_maybe = 0;
    player_bounce_height_counter = 0;
    byte_2E2E4 = 1;
    word_2E180 = 0;
    return;
}

void player_load_tiles()
{
    uint16 num_tiles;
    player_tiles = load_tiles("PLAYERS.MNI", TRANSPARENT, &num_tiles);
    printf("Loading %d player tiles.\n", num_tiles);
}