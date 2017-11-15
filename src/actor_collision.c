//
// Created by efry on 14/11/2017.
//

#include "actor_collision.h"
#include "actor.h"
#include "sfx.h"
#include "player.h"
#include "effects.h"
#include "game.h"
#include "status.h"
#include "input.h"
#include "hud.h"
#include "tile.h"

int actor_update_impl(ActorData *actor, int actorInfoIndex, int frame_num, int x_pos, int y_pos)
{
    if(is_sprite_on_screen(actorInfoIndex, frame_num, x_pos, y_pos) == 0)
    {
        return 1;
    }

    uint16 sprite_height = actor_get_tile_info(actorInfoIndex, frame_num)->height;
    uint16 sprite_width = actor_get_tile_info(actorInfoIndex, frame_num)->width;

    word_2E1E8 = 0;
    if(actorInfoIndex != 0x66)
    {
        int ax = word_2E180 <= 3 ? 0 : 1;

        if(ax + y_pos - sprite_height + 1 >= player_y_pos && y_pos - sprite_height <= player_y_pos && player_x_pos + 1 + 1 >= x_pos && x_pos + sprite_width - 1 >= player_x_pos && word_32B88 == 0)
        {
            word_2E1E8 = 1;
        }
    }
    else
    {
        sprite_height = 7;
        if(y_pos - sprite_height + 5 >= player_y_pos && y_pos - sprite_height <= player_y_pos && player_x_pos + 1 + 1 >= x_pos && x_pos + sprite_width - 1 >= player_x_pos)
        {
            word_2E1E8 = 1;
        }
    }

/*
    switch (actorInfoIndex)
    {
// node ffffffff-00000000 #insn=0 use={} def={} in={} out={} pred={} 
// node 0001be4d-0001be55 #insn=3 use={} def={bx} in={} out={bx} pred={ FFFFFFFF} CONDJUMP target=0001be5a follow=0001c590
        case 2: //33 PLAT:   Floor Spring
            if (actor->data_5 == 0)
            {
                if (actor->count_down_timer == 0 && player_bounce_in_the_air(0x28) != 0)
                {
                    play_sfx(6);
                    if (word_2E246 == 0)
                    {
                        word_2E246 = 1;
                        actor_add_new(0xf4, player_x_pos - 1, player_y_pos - 5);
                    }
                    actor->data_1 = 3;
                }
                return 0;
            }
            break;

// node 0001bea8-0001d0f6 #insn=4 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
        case 16: //47 OBJECT: Blue Mobile Trampoline Car
            if (actor->count_down_timer == 0 && player_bounce_in_the_air(0x14) != 0)
            {
                play_sfx(0x2b);
                actor->data_1 = 3;
            }
            return 0;

// node 0001becc-0001bed4 #insn=2 use={} def={bx} in={} out={} pred={ FFFFFFFF} CONDJUMP target=0001bee7 follow=0001c31a
        case 25: //56 HAZARD: Green Pruny Cabbage Ball
            if (actor->count_down_timer == 0 && player_bounce_in_the_air(7) != 0)
            {
                actor->count_down_timer = 5;
                play_sfx(6);
                actor_tile_display_func_index = 2;

                actor->data_1 = actor->data_1 - 1;
                if (actor->data_1 == 0)
                {
                    actor->is_deactivated_flag_maybe = 1;
                    player_add_score_for_actor(0x19);

                    sub_1BA0F(actor->x, actor->y);
                    return 1;
                }
            }
            else
            {
                if (actor->count_down_timer == 0 && player_check_collision_with_actor(actorInfoIndex, frame_num, x_pos, y_pos) != 0)
                {
                    player_decrease_health();
                }
            }
            return 0;

// node 0001bee7-0001d0f6 #insn=7 use={} def={} in={} out={} pred={ 1BECC} FALLTHROUGH follow=0001d0f6

// node 0001bf1e-0001d0f6 #insn=4 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
        case 0:  //31 Unknown.
        case 29: //60 BARREL: Power Up    (health/12800)
            if (actor->count_down_timer == 0 && player_bounce_in_the_air(5) != 0)
            {
                sub_1BBFE(actor);
                player_add_to_score(0x64);

                actor_add_new(0xb1, actor->x, actor->y);
                return 1;
            }
            return 0;

// node 0001bf44-0001bf4c #insn=2 use={} def={bx} in={} out={} pred={ FFFFFFFF} CONDJUMP target=0001bf5f follow=0001c31a
        case 51: // 82 ENEMY:  Ghost
        case 54: // 85 ENEMY:  Angry Moon (blue floating characters)
            if (actor->count_down_timer == 0 && player_bounce_in_the_air(7) != 0)
            {
                actor->count_down_timer = 3;
                play_sfx(6);

                actor->data_5 = actor->data_5 - 1;
                actor_tile_display_func_index = 2;
                if(actor->data_5 != 0)
                {
                    return 0;
                }
                actor->is_deactivated_flag_maybe = 1;
                if(actorInfoIndex == 0x33)
                {
                    actor_add_new(0x41, actor->x, actor->y);
                }

                sub_1BA0F(actor->x - 1, actor->y + 1);
                player_add_score_for_actor(0x33);
                return 1;
            }
            else
            {
                if (actor->count_down_timer == 0 && player_check_collision_with_actor(actorInfoIndex, frame_num, x_pos, y_pos) != 0)
                {
                    player_decrease_health();
                }
            }
            return 0;

// node 0001bfc2-0001bfca #insn=2 use={} def={bx} in={} out={} pred={ FFFFFFFF} CONDJUMP target=0001bfdd follow=0001c327
        case 65: // 96 ENEMY:  Mini Ghost (jumps)
        case 106: // 137 ENEMY:  Suction-Cup-Legged Alien
        case 187: // 218 ENEMY:  Blue Bird
            if (actor->count_down_timer == 0 && player_bounce_in_the_air(7) != 0) goto loc_1BFDD;

// node 0001c00a-0001d0f6 #insn=7 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
        case 74:
        case 75:
            if (actor->count_down_timer != 0)
            {
                return 0;
            }
            if (player_bounce_in_the_air(7) == 0)
            {
                return 0;
            }
            play_sfx(0x21);

            if (actor->data_2 != 0)
            {
                actor->data_2 = 1;
                default :ax = 0;
            }
            else
            {
                actor->data_2 = 10;
                default :ax = 0;
            }
            break;

// node 0001c04b-0001c053 #insn=2 use={} def={bx} in={} out={} pred={ FFFFFFFF} CONDJUMP target=0001c066 follow=0001c31a
        case 86:if (actor->count_down_timer == 0 && player_bounce_in_the_air(7) != 0) goto loc_1C066;

// node 0001c066-0001d0f6 #insn=9 use={} def={} in={} out={} pred={ 1C04B} FALLTHROUGH follow=0001d0f6
            play_sfx(6);

            actor->data_3 = 0;
            actor->count_down_timer = 3;
            actor->data_5 = actor->data_5 - 1;
            if (actor->data_1 != 0 || actor->falling_counter != 0)
            {
                loc_1C08D:
                actor->data_5 = 0;
            }

            if (actor->data_5 == 0)
            {
                sub_1BA0F(actor->x, actor->y);

                actor->is_deactivated_flag_maybe = 1;
                if (actor->data_1 > 0)
                {
                    player_add_to_score(0xc80);

                    actor_add_new(0xb6, actor->x, actor->y);
                    default :ax = 0;
                    return ax;
                }
                if (actor->falling_counter == 0)
                {
                    player_add_to_score(0x320);
                    default :ax = 0;
                }
                else
                {
                    player_add_to_score(0x3200);

                    actor_add_new(0xb8, actor->x, actor->y);
                    default :ax = 0;
                }
            }
            else
            {
                actor_tile_display_func_index = 2;

                if (actor->data_1 == 0)
                {
                    actor->data_2 = 0;
                    actor->data_1 = (sub_1106F() & 1) + 1;
                    default :ax = 0;
                }
                else
                {
                    default :ax = 0;
                }
            }
            break;

// node 0001c14d-0001c155 #insn=2 use={} def={bx} in={} out={} pred={ FFFFFFFF} CONDJUMP target=0001c168 follow=0001c31a
        case 101:if (actor->count_down_timer == 0 && player_bounce_in_the_air(15) != 0) goto loc_1C168;

// node 0001c168-0001d0f6 #insn=6 use={} def={} in={} out={} pred={ 1C14D} FALLTHROUGH follow=0001d0f6
            play_sfx(6);

            actor->count_down_timer = 6;
            actor->data_5 = actor->data_5 - 1;
            if (actor->data_5 != 0)
            {
                actor_tile_display_func_index = 2;
                default :ax = 0;
            }
            else
            {
                actor_add_new(1, actor->x, actor->y);

                sub_1BA0F(actor->x, actor->y);
                actor->is_deactivated_flag_maybe = 1;
                ax = 1;
            }
            break;

// node 0001c1b9-0001c1c1 #insn=2 use={} def={bx} in={} out={} pred={ FFFFFFFF} CONDJUMP target=0001c1d4 follow=0001c31a
        case 113:
        case 118:
        case 126:if (actor->count_down_timer == 0 && player_bounce_in_the_air(7) != 0) goto loc_1C1D4;

// node 0001c1d4-0001d0f6 #insn=6 use={} def={} in={} out={} pred={ 1C1B9} FALLTHROUGH follow=0001d0f6
            actor->count_down_timer = 3;
            play_sfx(6);
            actor_tile_display_func_index = 2;
            if (actorInfoIndex != 0x76)
            {
                actor->data_5 = actor->data_5 - 1;
            }
            if (actor->data_5 == 0 || actorInfoIndex == 0x76)
            {

                actor->is_deactivated_flag_maybe = 1;
                player_add_score_for_actor(actor);

                sub_1BA0F(actor->x, actor->y);
                ax = 1;
            }
            else
            {
                default :ax = 0;
            }
            break;

// node 0001c22f-0001d0f6 #insn=4 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
        case 124:
            if (actor->count_down_timer != 0)
            {
                return 0;
            }
            if (player_bounce_in_the_air(7) != 0)
            {
                player_add_score_for_actor(0x7c);
                play_sfx(6);

                sub_1BA0F(actor->x, actor->y);

                actor->is_deactivated_flag_maybe = 1;
                actor_add_new(0x80, actor->x, actor->y);
                ax = 1;
            }
            else
            {
                default :ax = 0;
            }
            break;

// node 0001c288-0001c28d #insn=2 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001c31a
        case 127:
            if ((word_2E4CE == 0 && obj_switch_151_flag != 0 || word_2E4CE != 0 && obj_switch_151_flag == 0) &&
                actor->count_down_timer == 0 && player_bounce_in_the_air(15) != 0)
            {
                actor->count_down_timer = 3;
                play_sfx(6);

                if (actor->data_1 == 0)
                {
                    actor->frame_num = 8;
                    default :ax = 0;
                }
                else
                {
                    actor->frame_num = 7;
                    default :ax = 0;
                }
                return ax;
            }

// node 0001c2ed-0001c2f5 #insn=2 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001c31a
        case 129:
        case 145:
            if (actor->count_down_timer == 0 && player_bounce_in_the_air(7) != 0)
            {
                num_hits_since_touching_ground = 0;
                play_sfx(6);
                actor->count_down_timer = 5;
                return 0;
            }

            //FIXME remove this, 5 usages remaining
            if (actor->count_down_timer == 0 && player_check_collision_with_actor(actorInfoIndex, frame_num, x_pos, y_pos) != 0)
            {
                player_decrease_health();
            }
//// node 0001c31a-0001c322 #insn=2 use={} def={} in={} out={} pred={ 1BECC 1BF44 1C04B 1C14D 1C1B9 1C288 1C2ED} FALLTHROUGH follow=0001c327
//        loc_1C31A:
//
//            if (actor->count_down_timer != 0)
//            {
//                return 0;
//            }
//
//// node 0001c327-0001d0f6 #insn=2 use={} def={} in={} out={} pred={ 1BFC2 1C31A} FALLTHROUGH follow=0001d0f6
//            if (player_check_collision_with_actor(actorInfoIndex, frame_num, x_pos, y_pos) != 0)
//            {
//                case 62:
//                case 110:
//                case 111:
//                case 127:
//                case 201:player_decrease_health();
//                default :ax = 0;
//            }
//            else
//            {
//                default :ax = 0;
//            }
//            break;

// node 0001c344-0001d0f6 #insn=6 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
        case 188:

            if (actor->x != player_x_pos)
            {
                return 0;
            }
            if (actor->count_down_timer != 0)
            {
                return 0;
            }
            if (player_bounce_in_the_air(5) != 0)
            {
                play_sfx(6);
                default :ax = 0;
            }
            else
            {
                default :ax = 0;
            }
            break;

// node 0001c376-0001d0f6 #insn=10 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
        case 152:

            if (actor->has_moved_right_flag != 0)
            {
                actor->has_moved_right_flag = actor->has_moved_right_flag - 1;
                if (actor->has_moved_right_flag != 0)
                {
                    default :ax = 0;
                    return ax;
                }
                byte_2E2E4 = 1;
                word_2E1E8 = 1;
                if (actor->count_down_timer != 0 || player_bounce_in_the_air(0x14) == 0)
                {
                }
                play_sfx(6);
                byte_2E17C = 0;
                word_2E1F8 = 0;
                word_2E180 = 0;

                actor->has_moved_left_flag = 1;
                actor->data_2 = 0;
                actor->data_1 = 1;
                player_y_pos = player_y_pos - 2;
                if (word_2E236 == 0)
                {
                    word_2E236 = 1;
                    actor_add_new(0xf4, player_x_pos - 1, player_y_pos - 5);
                    default :ax = 0;
                }
                else
                {
                    default :ax = 0;
                }
                return 0;
            }

            if (actor->has_moved_left_flag != 0)
            {
                return 0;
            }
            if (actor->x + 1 > player_x_pos)
            {
                return 0;
            }
            if (actor->x + 5 < player_x_pos + 1 + 1)
            {
                return 0;
            }
            if (actor->y - 1 != player_y_pos && actor->y - 2 != player_y_pos)
            {
                return 0;
            }
            if (byte_2E2E4 != 0)
            {

                actor->has_moved_right_flag = 0x14;
                word_2E1E8 = 0;
                player_bounce_height_counter = 0;
                byte_2E2E4 = 0;
                byte_2E17C = 1;
                word_2E1F8 = 1;
                actor->has_moved_left_flag = 1;
                actor->data_2 = 0;
                actor->data_1 = 1;
                play_sfx(0x3e);
                default :ax = 0;
            }
            else
            {
                default :ax = 0;
            }
            break;

// node 0001c48c-0001d0f6 #insn=6 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
        case 102:

            if (actor->has_moved_right_flag != 0)
            {
                return 1;
            }
            if (actor->data_5 == 12)
            {
                return 1;
            }
            if (actor->count_down_timer == 0 && player_bounce_in_the_air(7) != 0)
            {
                play_sfx(6);

                actor->data_5 = actor->data_5 + 1;
                actor->has_moved_left_flag = 10;
                actor->count_down_timer = 7;
                if (actor->data_1 != 2)
                {
                    actor->data_1 = 2;
                    actor->data_2 = 0x1f;
                    actor->data_3 = 0;
                    actor->data_4 = 1;
                    actor->can_fall_down_flag = 0;
                    actor->falling_counter = 0;
                }

                if (actor->data_5 == 4)
                {
                    struct4_add_sprite(0x66, 1, actor->x, actor->y - 4);
                    play_sfx(0x37);
                }

                struct7_add_sprite(0x61, 6, actor->x, actor->y, 8, 1);

                struct7_add_sprite(0x61, 6, actor->x + 3, actor->y, 2, 1);
                ax = 1;
            }
            else
            {
                if (actor->count_down_timer != 0)
                {
                    return 1;
                }
                if (player_check_collision_with_actor(actorInfoIndex, frame_num, x_pos, y_pos) != 0)
                {
                    player_decrease_health();
                    ax = 1;
                }
                else
                {
                    ax = 1;
                }
            }
            break;
    }
// node 0001c590-0001c5a5 #insn=2 use={} def={} in={} out={} pred={ 1BE4D} FALLTHROUGH follow=0001c5aa
        loc_1C590:
            if(player_check_collision_with_actor(actorInfoIndex, frame_num, x_pos, y_pos) == 0)
            {
                return 0;
            }

// node 0001c5aa-0001c5ba #insn=2 use={} def={} in={} out={} pred={ 1C590} FALLTHROUGH follow=0001d0f6
        loc_1C5AA:
            switch (actorInfoIndex - 1)
            {
// node ffffffff-00000000 #insn=0 use={} def={} in={} out={} pred={} 
// node 0001c7e9-0001d0f6 #insn=6 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 2:
                case 3:
                case 4:
                case 5:
                case 19:
                case 40:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 48:
                case 49:
                case 67:
                case 77:
                case 79:
                case 91:
                case 150:
                    player_decrease_health();
                    
                    if(actor == 0x44)
                    {
                        actor->is_deactivated_flag_maybe = 1;
                        default :
                            ax = 0;
                    }
                    else
                    {
                        default :
                            ax = 0;
                    }
                    break;
                    break;

// node 0001c802-0001d0f6 #insn=4 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 232:
                case 233:
                    if(actor->frame_num > 1)
                    {
                        case 62:
                        case 110:
                        case 111:
                        case 127:
                        case 201:
                            player_decrease_health();
                        default :
                            ax = 0;
                    }
                    else
                    {
                        default :
                            ax = 0;
                    }
                    break;
                    break;

// node 0001c812-0001d0f6 #insn=6 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 42:
                case 236:
                    
                    if(actor->data_5 != 0)
                    {
                        actor->y = actor->data_2;
                        actor->data_4 = 0;
                        if(actor->y > player_y_pos + 0xfffc || actor->frame_num == 6)
                        {
                            player_decrease_health();
                            actor->frame_num = 0;
                            default :
                                ax = 0;
                        }
                        else
                        {
                            actor->frame_num = 0;
                            default :
                                ax = 0;
                        }
                        return ax;
                    }
                    if(actor->y > player_y_pos + 0xfffc)
                    {
                        case 62:
                        case 110:
                        case 111:
                        case 127:
                        case 201:
                            player_decrease_health();
                        default :
                            ax = 0;
                    }
                    else
                    {
                        default :
                            ax = 0;
                    }
                    break;
                    break;

// node 0001c862-0001d0f6 #insn=4 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 82:
                case 83:
                    if(actor->frame_num != 0)
                    {
                        case 62:
                        case 110:
                        case 111:
                        case 127:
                        case 201:
                            player_decrease_health();
                        default :
                            ax = 0;
                    }
                    else
                    {
                        default :
                            ax = 0;
                    }
                    break;
                    break;

// node 0001c872-0001d0f6 #insn=5 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 6:
                case 7:
                case 8:
                case 9:
                    
                    if(actor->frame_num == 0)
                    {
                        actor->y = actor->y - 1;
                        actor->frame_num = 1;
                        default :
                            ax = 0;
                    }
                    else
                    {
                        default :
                            ax = 0;
                    }
                    break;
                    break;

// node 0001c88c-0001d0f6 #insn=4 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 16:
                case 17:
                case 86:
                case 87:
                case 88:
                    if(actor->frame_num <= 1)
                    {
                        case 62:
                        case 110:
                        case 111:
                        case 127:
                        case 201:
                            player_decrease_health();
                        default :
                            ax = 0;
                    }
                    else
                    {
                        ax = 1;
                    }
                    break;
                    break;

// node 0001c89c-0001d0f6 #insn=9 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 27:
                    actor->is_deactivated_flag_maybe = 1;
                    play_sfx(1);
                    
                    struct7_add_sprite(15, 4, actor->x, actor->y, 0, 3);
                    if(knows_about_powerups_flag == 0)
                    {
                        knows_about_powerups_flag = 1;
                        power_up_module_dialog();
                    }
                    if(health > num_health_bars)
                    {
                        player_add_to_score(0x3200);
                        
                        actor_add_new(0xb8, actor->x, actor->y);
                        ax = 1;
                    }
                    else
                    {
                        health = health + 1;
                        // Low-level instruction of type call    )%(00021ACBupdate_health_bar_display%) 
                        // push 0 
                        player_add_to_score(0x64);
                        
                        actor_add_new(0xb1, actor->x, actor->y);
                        ax = 1;
                    }
                    break;
                    break;

// node 0001c959-0001d0f6 #insn=5 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 84:
                case 93:
                case 133:
                case 134:
                case 135:
                case 136:
                case 137:
                case 138:
                case 139:
                case 140:
                case 145:
                case 146:
                case 167:
                case 169:
                case 171:
                case 222:
                case 225:
                case 228:
                case 231:
                    actor->is_deactivated_flag_maybe = 1;
                    if(actorInfoIndex != 0x92 && actorInfoIndex != 0xdf && actorInfoIndex != 0x55 && actorInfoIndex != 0x8d)
                    {
                        player_add_to_score(0x190);
                        actor_add_new(0xb3, x_pos, y_pos);
                        
                        struct7_add_sprite(15, 4, actor->x, actor->y, 0, 3);
                        play_sfx(13);
                        ax = 1;
                    }
                    else
                    {
                        player_add_to_score(0x320);
                        actor_add_new(0xb4, x_pos, y_pos);
                        
                        struct7_add_sprite(15, 4, actor->x, actor->y, 0, 3);
                        play_sfx(13);
                        ax = 1;
                    }
                    break;
                    break;

// node 0001ca4c-0001d0f6 #insn=4 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 56:
                    if(num_bombs <= 8)
                    {
                        actor->is_deactivated_flag_maybe = 1;
                        num_bombs++;
                        has_had_bomb_flag = 1;
                        player_add_to_score(0x64);
                        
                        actor_add_new(0xb1, actor->x, actor->y);
                        display_num_bombs_left();
                        
                        struct7_add_sprite(15, 4, actor->x, actor->y, 0, 3);
                        play_sfx(13);
                        ax = 1;
                    }
                    else
                    {
                        default :
                            ax = 0;
                    }
                    break;
                    break;

// node 0001cb03-0001d0f6 #insn=20 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 68:
                    var_8 = sub_1106F() & 3;
                    if(actor->count_down_timer != 0)
                    {
                        return 0;
                    }
                    // push REGISTER_31 
                    ax = & var_10;
                    // push ax 
                    // push REGISTER_32 
                    // push 0x534 
                    // Low-level instruction of type call    )(00010F8FSCOPY@) 
                    actor->count_down_timer = 10;
                    if(player_bounce_in_the_air(7) == 0)
                    {
                        player_hanging_on_wall_direction = 0;
                    }
                    else
                    {
                        play_sfx(6);
                    }
                    
                    struct5_add_new_actor_sprite(* ((var_8 << 1) + & var_10), actor->x, actor->y + 1);
                    play_sfx(0x11);
                    actor_tile_display_func_index = 2;
                    
                    actor->data_2 = actor->data_2 - 1;
                    if(actor->data_2 == 0)
                    {
                        actor->is_deactivated_flag_maybe = 1;
                        sub_1BA0F(actor->x - 1, actor->y + 1);
                        default :
                            ax = 0;
                    }
                    else
                    {
                        default :
                            ax = 0;
                    }
                    break;
                    break;

// node 0001cba7-0001cbac #insn=2 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001cbb1
                case 69:
                case 70:
                case 71:
                case 72:
                    if(player_in_pneumatic_tube_flag == 0)
                    {
                        return 1;
                    }

// node 0001cbb1-0001cbc0 #insn=2 use={} def={} in={} out={} pred={ 1CBA7} FALLTHROUGH follow=0001cc27
                loc_1CBB1:
                    switch (actorInfoIndex - 0x46)
                    {
// node ffffffff-00000000 #insn=0 use={} def={} in={} out={} pred={} 
// node 0001cbcd-0001cc27 #insn=3 use={} def={} in={} out={} pred={ FFFFFFFF} JUMP target=0001cc27
                        case 0:
                            push_player_around(1, 0x64, 2, 0xff, 0, 0);
                            break;

// node 0001cbe4-0001cc27 #insn=3 use={} def={} in={} out={} pred={ FFFFFFFF} JUMP target=0001cc27
                        case 1:
                            push_player_around(5, 0x64, 2, 0xff, 0, 0);
                            break;

// node 0001cbfb-0001cc27 #insn=3 use={} def={} in={} out={} pred={ FFFFFFFF} JUMP target=0001cc27
                        case 2:
                            push_player_around(7, 0x64, 2, 0xff, 0, 0);
                            break;

// node 0001cc12-0001cc27 #insn=3 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001cc27
                        case 3:
                            push_player_around(3, 0x64, 2, 0xff, 0, 0);
                            break;

// node 0001cc27-00000000 #insn=0 use={} def={} in={} out={} pred={ 1CBCD 1CBE4 1CBFB 1CC12} 
                    }

// node 0001cc31-0001d0f6 #insn=10 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 104:
                    
                    if(actor->data_2 == 0 && (actor->y + 3 == player_y_pos || actor->y + 1 + 1 == player_y_pos))
                    {
                        if(player_is_being_pushed_flag == 0)
                        {
                            return 0;
                        }
                        player_x_pos = actor->x;
                        word_32EB2 = 1;
                        player_in_pneumatic_tube_flag = 0;
                        player_reset_push_variables();
                        if(word_2E24C == 0)
                        {
                            word_2E24C = 1;
                            actor_add_new(0xf4, player_x_pos - 1, player_y_pos - 5);
                            default :
                                ax = 0;
                        }
                        else
                        {
                            default :
                                ax = 0;
                        }
                        return ax;
                    }
                    if(byte_2E2E4 != 0 && player_bounce_flag_maybe == 0)
                    {
                        return 0;
                    }
                    if(jump_key_pressed == 0 && player_bounce_flag_maybe == 0)
                    {
                        return 0;
                    }
                    
                    if(actor->x != player_x_pos)
                    {
                        return 0;
                    }
                    if(actor->y + 3 == player_y_pos || actor->y + 1 + 1 == player_y_pos)
                    {
                        player_in_pneumatic_tube_flag = 1;
                        default :
                            ax = 0;
                    }
                    else
                    {
                        default :
                            ax = 0;
                    }
                    break;
                    break;

// node 0001ccf7-0001d0f6 #insn=6 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 107:
                    if(teleporter_counter != 0)
                    {
                        return 1;
                    }
                    
                    if(actor->x > player_x_pos || actor->x + 4 < player_x_pos + 1 + 1 || actor->y != player_y_pos)
                    {
                        player_is_teleporting_flag = 0;
                        ax = 1;
                    }
                    else
                    {
                        if(up_key_pressed != 0)
                        {
                            teleporter_state_maybe = actor->data_5;
                            teleporter_counter = 15;
                            byte_2E2E4 = 0;
                        }
                        player_is_teleporting_flag = 1;
                        ax = 1;
                    }
                    break;
                    break;

// node 0001cd5b-0001d0f6 #insn=16 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 113:
                    if(byte_2E2E4 == 0)
                    {
                        return 0;
                    }
                    
                    if(actor->y != player_y_pos && actor->y + 1 != player_y_pos)
                    {
                        return 0;
                    }
                    word_32B88 = 4;
                    play_sfx(3);
                    player_reset_push_variables();
                    byte_2E2E4 = 0;
                    word_2E180 = 0;
                    player_bounce_flag_maybe = 0;
                    word_2E1E8 = 0;
                    player_bounce_height_counter = 0;
                    num_hits_since_touching_ground = 0;
                    if(word_2E232 == 0)
                    {
                        word_2E232 = 1;
                        actor_add_new(0xf4, player_x_pos - 1, player_y_pos - 5);
                        default :
                            ax = 0;
                    }
                    else
                    {
                        default :
                            ax = 0;
                    }
                    break;
                    break;

// node 0001cdc8-0001d0f6 #insn=9 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 148:
                    
                    if(actor->data_4 != 0)
                    {
                        actor->data_4 = actor->data_4 - 1;
                        if(actor->data_4 != 0)
                        {
                            actor->frame_num = 0;
                            ax = 1;
                        }
                        else
                        {
                            finished_level_flag_maybe = 1;
                            actor->frame_num = 0;
                            default :
                                ax = 0;
                        }
                        return ax;
                    }
                    
                    if(actor->data_1 == 0)
                    {
                        return 1;
                    }
                    if(actor->y != player_y_pos)
                    {
                        return 1;
                    }
                    if(actor->x <= player_x_pos)
                    {
                        actor->frame_num = 0;
                        actor->data_5 = 0;
                        actor->data_4 = 5;
                        word_2E1F8 = 1;
                        byte_2E17C = 1;
                        play_sfx(0x27);
                        ax = 1;
                    }
                    else
                    {
                        ax = 1;
                    }
                    break;
                    break;

// node 0001cf0b-0001cf13 #insn=3 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001cf5d
                case 161:
                    
                    if(actor->data_2 == 0 && actor->x == player_x_pos && actor->y == player_y_pos)
                    {
                        actor->data_2 = 1;
                        byte_2E17C = 1;
                        if(word_2E220 == 0)
                        {
                            word_2E220 = 1;
                            actor_add_new(0xf5, player_x_pos - 1, player_y_pos - 5);
                            default :
                                ax = 0;
                        }
                        else
                        {
                            default :
                                ax = 0;
                        }
                        return ax;
                    }

// node 0001cf5d-0001d0f6 #insn=10 use={} def={} in={} out={} pred={ FFFFFFFF 1CF0B} FALLTHROUGH follow=0001d0f6
                case 185:
                    
                    if(actor->frame_num != 0)
                    {
                        return 0;
                    }
                    if(actor->x >= player_x_pos)
                    {
                        return 0;
                    }
                    if(actor->x + 5 <= player_x_pos)
                    {
                        return 0;
                    }
                    if(actor->y - 2 <= player_y_pos)
                    {
                        return 0;
                    }
                    if(actor->y - 5 >= player_y_pos)
                    {
                        return 0;
                    }
                    if(byte_2E2E4 != 0)
                    {
                        actor->data_5 = 1;
                        byte_2E17C = 1;
                        word_2E1F8 = 1;
                        actor->frame_num = 1;
                        play_sfx(0x27);
                        default :
                            ax = 0;
                    }
                    else
                    {
                        default :
                            ax = 0;
                    }
                    break;
                    break;

// node 0001c799-0001d0f6 #insn=12 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} JUMP target=0001d0f6
                case 0:
                    struct7_add_sprite(0x17, 8, x_pos, y_pos, 0, 1);
                    num_stars_collected++;
                    // Low-level instruction of type adc     )(0002E1D6word_2E1D6)	,	 *0* 
                    actor->is_deactivated_flag_maybe = 1;
                    play_sfx(1);
                    player_add_score_for_actor(actorInfoIndex);
                    actor_add_new(0xb2, x_pos, y_pos);
                    display_num_stars_collected();
                    ax = 1;
                    break;
                    break;

// node 0001c9bb-0001d0f6 #insn=13 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} JUMP target=0001d0f6
                case 81:
                    actor->is_deactivated_flag_maybe = 1;
                    player_add_to_score(0x3200);
                    actor_add_new(0xb8, x_pos, y_pos);
                    
                    struct7_add_sprite(15, 4, actor->x, actor->y, 0, 3);
                    play_sfx(13);
                    if(num_health_bars < 5)
                    {
                        num_health_bars++;
                    }
                    if(word_2E22A == 0)
                    {
                        actor_add_new(0xf4, player_x_pos - 1, player_y_pos - 5);
                        word_2E22A = 1;
                    }
                    // Low-level instruction of type call    )%(00021ACBupdate_health_bar_display%) 
                    ax = 1;
                    break;
                    break;

// node 0001cc27-0001d0f6 #insn=4 use={} def={ax} in={} out={ax} pred={ 1CBB1} JUMP target=0001d0f6
                    play_sfx(0x16);
                    ax = 1;
                    break;
                    break;

// node 0001c931-0001d0f6 #insn=10 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} JUMP target=0001d0f6
                case 31:
                case 33:
                case 35:
                case 37:
                    actor->is_deactivated_flag_maybe = 1;
                    player_add_to_score(0xc8);
                    actor_add_new(0xb2, x_pos, y_pos);
                    
                    struct7_add_sprite(15, 4, actor->x, actor->y, 0, 3);
                    play_sfx(13);
                    ax = 1;
                    break;
                    break;

// node 0001cfd2-0001d0f6 #insn=9 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} JUMP target=0001d0f6
                case 188:
                    actor->is_deactivated_flag_maybe = 1;
                    actor_add_new(0xc9, player_x_pos - 1, player_y_pos + 1);
                    struct7_add_sprite(0x17, 8, x_pos, y_pos, 0, 1);
                    actor_add_new(0xb8, x_pos, y_pos);
                    play_sfx(1);
                    ax = 1;
                    break;
                    break;

// node 0001ce49-0001d0f6 #insn=10 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} JUMP target=0001d0f6
                case 152:
                case 173:
                case 175:
                    
                    actor->is_deactivated_flag_maybe = 1;
                    struct7_add_sprite(15, 4, actor->x, actor->y, 0, 3);
                    player_add_to_score(0xc80);
                    actor_add_new(0xb6, x_pos, y_pos);
                    play_sfx(13);
                    ax = 1;
                    break;
                    break;

// node 0001ce87-0001d0f6 #insn=10 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} JUMP target=0001d0f6
                case 153:
                case 154:
                    
                    actor->is_deactivated_flag_maybe = 1;
                    struct7_add_sprite(15, 4, actor->x, actor->y, 0, 3);
                    player_add_to_score(0x640);
                    actor_add_new(0xb5, x_pos, y_pos);
                    play_sfx(13);
                    ax = 1;
                    break;
                    break;

// node 0001cec5-0001d0f6 #insn=10 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} JUMP target=0001d0f6
                case 193:
                case 195:
                case 197:
                case 199:
                case 219:
                    
                    actor->is_deactivated_flag_maybe = 1;
                    struct7_add_sprite(15, 4, actor->x, actor->y, 0, 3);
                    player_add_to_score(0x320);
                    actor_add_new(0xb4, x_pos, y_pos);
                    play_sfx(13);
                    ax = 1;
                    break;
                    break;

// node 0001d09a-0001d0f6 #insn=5 use={} def={} in={} out={} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 1:
                    
                    if(actor->data_5 == 0)
                    {
                        default :
                            ax = 0;
                    }
                    else
                    {
                        if(actor->count_down_timer != 0)
                        {
                            default :
                                ax = 0;
                        }
                        else
                        {
                            if(word_32B88 != 0)
                            {
                                default :
                                    ax = 0;
                            }
                            else
                            {
                                if(byte_2E2E4 != 0 && player_bounce_flag_maybe == 0)
                                {
                                    default :
                                        ax = 0;
                                }
                                else
                                {
                                    actor->count_down_timer = 2;
                                    play_sfx(6);
                                    actor->data_1 = 3;
                                    player_bounce_height_counter = 0;
                                    player_bounce_flag_maybe = 0;
                                    byte_2E2E4 = 1;
                                    word_2E180 = 4;
                                    byte_2E182 = 0;
                                    default :
                                        ax = 0;
                                }
                            }
                        }
                    }
                    break;
                    break;

// node 0001d0f4-0001d0f6 #insn=4 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                default :
                    ax = 0;
                    break;
                    break;

// node 0001ca37-0001d0f6 #insn=6 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 38:
                    finished_level_flag_maybe = 1;
                default :
                    ax = 0;
                    break;
                    break;

// node 0001caab-0001d0f6 #insn=15 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 59:
                    
                    if(actor->data_1 >= 4)
                    {
                        return 0;
                    }
                    if(actor->data_4 != 0)
                    {
                        return 0;
                    }
                    byte_2E2E4 = 1;
                    sub_11062();
                    player_bounce_in_the_air(3);
                    
                    actor->data_1 = actor->data_1 + 1;
                    if(actor->data_2 != 0)
                    {
                        actor->data_3 = 0;
                    }
                    else
                    {
                        actor->data_3 = 0x40;
                        actor->data_2 = 1;
                    }
                    actor->data_4 = 1;
                default :
                    ax = 0;
                    break;
                    break;

// node 0001d021-0001d0f6 #insn=8 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 63:
                    if(word_2E234 == 0)
                    {
                        word_2E234 = 1;
                        actor_add_new(0xf5, player_x_pos - 1, player_y_pos - 5);
                    }
                    if(actor->x != player_x_pos + 1 + 1)
                    {
                        if(actor->x + 1 + 1 != player_x_pos)
                        {
                            return 0;
                        }
                        push_player_around(3, 5, 2, 0x11, 0, 1);
                    }
                    else
                    {
                        push_player_around(7, 5, 2, 0x28, 0, 1);
                    }
                    play_sfx(0x14);
                default :
                    ax = 0;
                    break;
                    break;

// node 0001cd54-0001d0f6 #insn=6 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 62:
                case 110:
                case 111:
                case 127:
                case 201:
                    player_decrease_health();
                default :
                    ax = 0;
                    break;
                    break;

// node 0001ca40-0001d0f6 #insn=8 use={} def={ax} in={} out={ax} pred={ FFFFFFFF} FALLTHROUGH follow=0001d0f6
                case 54:
                    actor->data_1 = 1;
                case 62:
                case 110:
                case 111:
                case 127:
                case 201:
                    player_decrease_health();
                default :
                    ax = 0;
                    break;
                    break;

// node 0001d0f6-00000000 #insn=0 use={} def={} in={} out={} pred={ 1C7E9 1C802 1C812 1C862 1C872 1C88C 1C89C 1C959 1CA4C 1CB03 1CC31 1CCF7 1CD5B 1CDC8 1CF5D 1C799 1C9BB 1CC27 1C931 1CFD2 1CE49 1CE87 1CEC5 1D09A 1D0F4 1CA37 1CAAB 1D021 1CD54 1CA40} 
            }

// node 0001bfdd-0001d0f6 #insn=7 use={} def={ax} in={} out={ax} pred={ 1BFC2} JUMP target=0001d0f6
            play_sfx(6);
            
            actor->is_deactivated_flag_maybe = 1;
            sub_1BA0F(actor->x, actor->y);
            player_add_score_for_actor(actor);
            ax = 1;
            break;

// node 0001d0f6-00000000 #insn=0 use={} def={} in={} out={} pred={ 1BE5A 1BEA8 1BEE7 1BF1E 1C00A 1C066 1C168 1C1D4 1C22F 1C327 1C344 1C376 1C48C 1C5AA 1BF5F 1BFDD} 
//    }

// node 0001d0f6-0001d0f9 #insn=4 use={ax} def={si, di} in={ax} out={} pred={ 1BDD4} RETURN
    loc_1D0F6:
    // pop  
    // pop
    */
    return 0; //FIXME
}