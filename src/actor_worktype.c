//
// Created by efry on 12/11/2017.
//

#include <stdlib.h>
#include "actor_worktype.h"
#include "player.h"
#include "effects.h"
#include "game.h"
#include "dialog.h"
#include "input.h"
#include "sfx.h"
#include "tile.h"
#include "map.h"

void actor_wt_133_boss_purple_15411(ActorData *actor)
{

}

void actor_wt_159_unknown(ActorData *actor)
{

}

void actor_wt_acid(ActorData *actor)
{

}

void actor_wt_alien_eating_space_plant(ActorData *actor)
{

}

void actor_wt_angry_moon(ActorData *actor)
{

}

void actor_wt_big_red_jumper_frozen(ActorData *actor)
{

}

void actor_wt_big_red_plant(ActorData *actor)
{

}

void actor_wt_big_saw_blade(ActorData *actor)
{

}

void actor_wt_big_yellow_spike(ActorData *actor)
{

}

void actor_wt_blue_ball(ActorData *actor)
{

}

void actor_wt_blue_bird(ActorData *actor)
{

}

void actor_wt_blue_cube_platform(ActorData *actor)
{

}

void actor_wt_blue_mobile_trampoline_car(ActorData *actor)
{

}

void actor_wt_blue_platform(ActorData *actor)
{

}

void actor_wt_blue_turret_alien(ActorData *actor)
{

}

void actor_wt_bomb(ActorData *actor)
{

}

void actor_wt_bonus_bomb(ActorData *actor)
{

}

void actor_wt_bonus_item(ActorData *actor)
{
    if(actor->data_1 != 0)
    {
        actor_tile_display_func_index = 4;
    }
    
    if (actor->data_4 == 0)
    {
        actor->frame_num = actor->frame_num + 1;
    }
    else
    {
        actor->data_3 = (actor->data_3 ? -1 : 0) + 1;
        if (actor->data_3 != 0)
        {
            actor->frame_num = actor->frame_num + 1;
        }
    }

    if(actor->frame_num == actor->data_5)
    {
        actor->frame_num = 0;
    }
    
    if(actor->data_5 == 1 && actor->actorInfoIndex != 0xca && actor->data_4 == 0)
    {
        if((rand() & 0x3f) == 0)
        {
            effect_add_sprite(0x17, 8, rand() % actor->data_1 + actor->x, rand() % actor->data_2 + actor->y, 0,
                              1);
        }
    }

    return;
}

void actor_wt_clam_trap(ActorData *actor)
{

}

void actor_wt_container(ActorData *actor)
{

}

void actor_wt_crate_bomb_box(ActorData *actor)
{

}

void actor_wt_cyan_spitting_plant(ActorData *actor)
{

}

void actor_wt_destructable_pedestal(ActorData *actor)
{

}

void actor_wt_door(ActorData *actor)
{

}

void actor_wt_dragonfly(ActorData *actor)
{

}

void actor_wt_egg_head(ActorData *actor)
{

}

void actor_wt_end_of_level_marker(ActorData *actor)
{
    if(actor->y <= player_y_pos && actor->data_1 == 0)
    {
        finished_level_flag_maybe = 1;
    }
    else
    {
        if(actor->y >= player_y_pos && actor->data_1 != 0)
        {
            finished_game_flag_maybe = 1;
        }
    }

    actor_tile_display_func_index = 1;
    return;
}

void actor_wt_energy_beam(ActorData *actor)
{

}

void actor_wt_extending_arrow(ActorData *actor)
{

}

void actor_wt_frozen_duke_nukum(ActorData *actor)
{

}

void actor_wt_ghost(ActorData *actor)
{

}

void actor_wt_green_plant(ActorData *actor)
{

}

void actor_wt_green_pruny_cabbage_ball(ActorData *actor)
{

}

void actor_wt_green_roamer_worm(ActorData *actor)
{

}

const uint8 byte_28EFE[] = { 0, 4, 5, 6, 5, 4};

void actor_wt_hint_dialog(ActorData *actor)
{
    actor->data_4 = (actor->data_4 ? -1 : 0) + 1;
    if(actor->data_4 != 0)
    {
        actor->data_3 = actor->data_3 + 1;
    }
    
    display_actor_sprite_maybe(0x7d, byte_28EFE[actor->data_3 % 6], actor->x, actor->y - 2, 0);
    
    actor->data_2 = actor->data_2 + 1;
    if(actor->data_2 == 4)
    {
        actor->data_2 = 1;
    }
    
    display_actor_sprite_maybe(0x7d, actor->data_2, actor->x, actor->y, 0);
    actor_tile_display_func_index = 1;
    
    if(player_check_collision_with_actor(0x7d, 0, actor->x, actor->y - 2) != 0)
    {
        word_32EAC = 1;
        if(game_play_mode != 0)
        {
            byte_2E21C = 1;
        }
        if(up_key_pressed != 0 && word_32B88 == 0 || byte_2E21C == 0)
        {
            play_sfx(0x1e);
            ingame_hint_dialogs(actor->data_5);
        }
        byte_2E21C = 1;
    }
    return;
}

void actor_wt_horizontal_flame(ActorData *actor)
{

}

void actor_wt_hoverboard(ActorData *actor)
{

}

void actor_wt_invisible_exit_marker_right(ActorData *actor)
{

}

void actor_wt_jaws_and_tongue(ActorData *actor)
{

}

void actor_wt_jumping_bullet_head(ActorData *actor)
{

}

void actor_wt_mini_ghost(ActorData *actor)
{

}

void actor_wt_pink_eye_plant(ActorData *actor)
{
    actor_tile_display_func_index = actor->data_5;
    actor->data_2 = rand() % 0x28;
    if(actor->data_2 <= 0x25)
    {
        actor->data_2 = 0;
    }
    else
    {
        actor->data_2 = 3;
    }
    
    if(actor->x - 2 > player_x_pos)
    {
        actor->frame_num = actor->data_2;
        return;
    }
    
    if(actor->x + 1 >= player_x_pos)
    {
        actor->frame_num = actor->data_2 + 1;
    }
    else
    {
        actor->frame_num = actor->data_2 + 2;
    }

    return;
}

void actor_wt_pink_slug(ActorData *actor)
{

}

void actor_wt_pipe_transit_direction(ActorData *actor)
{

}

void actor_wt_plasma_energy_blue_sprite(ActorData *actor)
{

}

void actor_wt_plasma_fireball(ActorData *actor)
{

}

void actor_wt_pneumatic_pipe(ActorData *actor)
{

}

void actor_wt_projectile_unknown(ActorData *actor)
{

}

void actor_wt_question_mark_block(ActorData *actor)
{

}

void actor_wt_red_blue_plant(ActorData *actor)
{

}

const uint8 word_28EE6[] = { 8, 9, 10, 10, 9, 8};
const uint8 word_28EF2[] = { 10, 9, 8, 8, 9, 10};

void actor_wt_red_chomper_alien(ActorData *actor)
{
    actor->data_4 = (actor->data_4 ? -1 : 0) + 1;

    if(sub_1106F() % 0x5f != 0)
    {
        if(sub_1106F() % 0x64 == 0)
        {
            actor->data_5 = 11;
        }
    }
    else
    {
        actor->data_5 = 10;
    }
    
    if(actor->data_5 < 11 && actor->data_5 != 0)
    {
        actor->data_5 = actor->data_5 - 1;
        if(actor->data_5 <= 8)
        {
            
            if(actor->data_5 != 8)
            {
                
                actor->data_2 = (actor->data_2 ? -1 : 0) + 1;

                actor->frame_num = actor->data_2 + 6;
            }
            else
            {
                actor->frame_num = 5;
            }
        }
        else
        {
            actor->frame_num = 6;
        }
        if(actor->data_5 != 0)
        {
            return;
        }

        if((sub_1106F() & 1) == 0)
        {
            return;
        }

        if(actor->x < player_x_pos)
        {
            actor->data_1 = 1;
        }
        else
        {
            actor->data_1 = 0;
        }
    }
    else
    {
        
        if(actor->data_5 > 10)
        {
            if(actor->data_1 != 0)
            {
                actor->frame_num = word_28EF2[actor->data_5 - 11];
            }
            else
            {
                actor->frame_num = word_28EE6[actor->data_5 - 11];
            }
            
            actor->data_5 = actor->data_5 + 1;
            if(actor->data_5 == 0x11)
            {
                actor->data_5 = 0;
            }
            return;
        }
        
        if(actor->data_1 == 0)
        {
            if(actor->data_4 != 0)
            {
                actor->frame_num = (actor->frame_num ? -1 : 0) + 1;
                actor->x = actor->x - 1;
                check_actor_move_left_or_right(actor, LEFT);
                
                if(actor->has_moved_left_flag == 0)
                {
                    actor->data_1 = 1;
                    actor->frame_num = 4;
                }
            }
            return;
        }
        
        if(actor->data_4 != 0)
        {
            actor->data_3 = (actor->data_3 ? -1 : 0) + 1;
            actor->frame_num = actor->data_3 + 2;
            actor->x++;
            check_actor_move_left_or_right(actor, RIGHT);
            
            if(actor->has_moved_right_flag == 0)
            {
                actor->data_1 = 0;
                actor->frame_num = 4;
            }
        }
    }
    return;
}

void actor_wt_retracting_spikes(ActorData *actor)
{

}

void actor_wt_robot_with_blue_arc(ActorData *actor)
{

}

void actor_wt_robotic_spike_ceiling(ActorData *actor)
{

}

void actor_wt_robotic_spike_ground(ActorData *actor)
{

}

void actor_wt_rocket(ActorData *actor)
{

}

void actor_wt_rubber_wall(ActorData *actor)
{

}

void actor_wt_satellite(ActorData *actor)
{

}

void actor_wt_security_robot(ActorData *actor)
{

}

void actor_wt_short_dialog(ActorData *actor)
{

}

void actor_wt_silver_robot(ActorData *actor)
{

}

void actor_wt_small_flame(ActorData *actor)
{

}

void actor_wt_small_red_plant(ActorData *actor)
{

}

void actor_wt_smoke_rising(ActorData *actor)
{

}

void actor_wt_spark(ActorData *actor)
{

}

void actor_wt_spear_vertical(ActorData *actor)
{

}

void actor_wt_spring(ActorData *actor)
{
    if(actor->data_1 <= 0)
    {
        actor->frame_num = 0;
    }
    else
    {
        actor->frame_num = 1;
        actor->data_1 = actor->data_1 - 1;
    }
    
    if(actor->data_5 != 0)
    {
        actor_tile_display_func_index = 4;
        if(actor->frame_num != 0)
        {
            actor->y = actor->data_4;
        }
        else
        {
            actor->y = actor->data_3;
        }
    }
    return;
}

void actor_wt_stone_head(ActorData *actor)
{

}

void actor_wt_suction_cup_alien_enemy(ActorData *actor)
{

}

void actor_wt_switch(ActorData *actor)
{

}

void actor_wt_switch_multi_use(ActorData *actor)
{

}

void actor_wt_teleporter(ActorData *actor)
{

}

void actor_wt_two_tons(ActorData *actor)
{

}

const sint8 score_effect_x_tbl[] = {
        -2, -1, 0, 1, 2, 2, 1, 0, -1, -2
};
void actor_wt_floating_score_effect(ActorData *actor)
{
    actor_tile_display_func_index = 1;
    actor->data_1 = actor->data_1 + 1;
    actor->frame_num = (actor->frame_num ? -1 : 0) + 1;
    if(actor->data_1 > 0x1f)
    {
        actor->y = actor->y - 1;
        actor->x = actor->x + score_effect_x_tbl[(actor->data_1 - 32) % 10];
    }

    if(actor->data_1 < 4)
    {
        actor->y = actor->y - 1;
    }

    if(actor->data_1 == 0x64 || is_sprite_on_screen(actor->actorInfoIndex, actor->frame_num, actor->x, actor->y) == 0)
    {
        actor->is_deactivated_flag_maybe = 1;
        actor_tile_display_func_index = 1;
    }

    display_actor_sprite_maybe(actor->actorInfoIndex, actor->frame_num, actor->x, actor->y, 5);
    return;
}

void actor_wt_speech_bubble(ActorData *actor)
{
    actor_tile_display_func_index = 1;
    if(actor->data_1 == 0)
    {
        play_sfx(0x39);
        if(actor->actorInfoIndex == 0xf6)
        {
            player_add_to_score(0xc350);
        }
    }
    
    actor->data_1 = actor->data_1 + 1;
    if(actor->data_1 != 0x14)
    {
        display_actor_sprite_maybe(actor->actorInfoIndex, 0, player_x_pos - 1, player_y_pos - 5, 5);
    }
    else
    {
        actor->is_deactivated_flag_maybe = 1;
    }

    return;
}

void actor_wt_unknown_232(ActorData *actor)
{

}

void check_actor_move_left_or_right(ActorData *actor, Direction direction_of_movement)
{
    uint16 sprite_width = actor_get_tile_info(actor->actorInfoIndex, actor->frame_num)->width;

    if(direction_of_movement == LEFT)
    {
        BlockingType block_status = sprite_blocking_check(2, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y);
        
        actor->has_moved_left_flag = (block_status != NOT_BLOCKED ? -1 : 0) + 1;
        if(actor->has_moved_left_flag == 0 && block_status != SLOPE)
        {
            actor->x = actor->x + 1;
            return;
        }
        if(block_status != SLOPE)
        {
            if(sprite_blocking_check(1, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y + 1) == 0)
            {
                uint8 tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x + sprite_width, actor->y + 1) / 8];
                if((tile_attr & TILE_ATTR_SLOPED) != 0)
                {

                    tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x + sprite_width - 1, actor->y + 1 + 1) / 8];
                    if((tile_attr & TILE_ATTR_SLOPED) != 0)
                    {

                        tile_attr = tileattr_mni_data[ map_get_tile_cell(actor->x + sprite_width - 1, actor->y + 1) / 8];
                        if((tile_attr & TILE_ATTR_BLOCK_DOWN) != 0)
                        {
                            return;
                        }

                        actor->has_moved_left_flag = 1;

                        if((tile_attr & TILE_ATTR_SLOPED) == 0)
                        {
                            actor->y = actor->y + 1;
                        }
                        return;
                    }
                }
                if(actor->has_moved_left_flag == 0)
                {
                    actor->x = actor->x + 1;
                    return;
                }

                if(actor->non_blocking_flag_maybe != 0 || sprite_blocking_check(2, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y + 1) != 0)
                {
                    return;
                }

                tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x + sprite_width - 1, actor->y + 1)/ 8];
                if((tile_attr & TILE_ATTR_SLOPED) == 0)
                {
                    actor->x = actor->x + 1;
                    actor->has_moved_left_flag = 0;
                }
            }
            else
            {
                actor->has_moved_left_flag = 1;
            }
        }
        else
        {
            actor->has_moved_left_flag = 1;
            actor->y = actor->y - 1;
        }
    }
    else
    {
        BlockingType block_status = sprite_blocking_check(3, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y);
        
        actor->has_moved_right_flag = (block_status != NOT_BLOCKED ? -1 : 0) + 1;
        if(actor->has_moved_right_flag == 0 && block_status != SLOPE)
        {
            actor->x = actor->x - 1;
            return;
        }
        if(block_status != SLOPE)
        {
            if(sprite_blocking_check(1, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y + 1))
            {
                uint8 tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x - 1, actor->y + 1) /8];
                if((tile_attr & TILE_ATTR_SLOPED) != 0)
                {

                    tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x, actor->y + 1 + 1) / 8];
                    if((tile_attr & TILE_ATTR_SLOPED) != 0)
                    {

                        tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x, actor->y + 1) / 8];
                        if((tile_attr & TILE_ATTR_BLOCK_DOWN) != 0)
                        {
                            return;
                        }

                        actor->has_moved_right_flag = 1;
                        tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x, actor->y + 1) / 8];
                        if((tile_attr & TILE_ATTR_SLOPED) == 0)
                        {
                            actor->y = actor->y + 1;
                            return;
                        }
                        return;
                    }
                }
                if(actor->has_moved_right_flag == 0)
                {
                    actor->x = actor->x - 1;
                    return;
                }

                if(actor->non_blocking_flag_maybe == 0 && sprite_blocking_check(3, actor->actorInfoIndex, actor->frame_num, actor->x, actor->y + 1) == 0)
                {

                    tile_attr = tileattr_mni_data[map_get_tile_cell(actor->x, actor->y + 1) / 8];
                    if((tile_attr & TILE_ATTR_SLOPED) == 0)
                    {

                        actor->x = actor->x - 1;
                        actor->has_moved_right_flag = 0;
                        return;
                    }
                    return;
                }
            }
            else
            {
                actor->has_moved_right_flag = 1;
            }
        }
        else
        {
            actor->has_moved_right_flag = 1;
            actor->y = actor->y - 1;
        }
    }

    return;
}
