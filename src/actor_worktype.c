//
// Created by efry on 12/11/2017.
//

#include <stdlib.h>
#include "actor_worktype.h"
#include "player.h"
#include "effects.h"

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
            struct7_add_sprite(0x17, 8, rand() % actor->data_1 + actor->x, rand() % actor->data_2 + actor->y, 0, 1);
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

void actor_wt_hint_dialog(ActorData *actor)
{

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

void actor_wt_red_chomper_alien(ActorData *actor)
{

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

void actor_wt_unknown_177_184(ActorData *actor)
{

}

void actor_wt_unknown_1888E(ActorData *actor)
{

}

void actor_wt_unknown_232(ActorData *actor)
{

}
