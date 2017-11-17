//
// Created by efry on 12/11/2017.
//

#include <stdlib.h>
#include "effects.h"
#include "defines.h"
#include "actor.h"
#include "player.h"

#define MAX_STRUCT7_SPRITES 10

typedef struct struc_7
{
    int is_active_flag;
    int actorInfoIndex;
    int frame_num;
    int x;
    int y;
    int field_A;
    int counter;
} struc_7;

struc_7 struc7_sprites[MAX_STRUCT7_SPRITES];
uint16 struct7_frame_num_tbl[MAX_STRUCT7_SPRITES];

int struct6_1B4FC(int actorInfoIndex, int frame_num, int x_pos, int y_pos)
{
    return 0;
}

int sub_1BAAD(int actorInfoIndex, int frame_num, int x_pos, int y_pos)
{
    return 0;
}

void struct7_add_sprite(int actorInfoIndex, int frame_num, int x_pos, int y_pos, int arg_8, int counter)
{
    for(int i=0;i<MAX_STRUCT7_SPRITES;i++)
    {
        struc_7 *sprite = &struc7_sprites[i];
        if(!sprite->is_active_flag)
        {
            sprite->is_active_flag = 1;
            sprite->actorInfoIndex = actorInfoIndex;
            sprite->frame_num = frame_num;
            sprite->x = x_pos;
            sprite->y = y_pos;
            sprite->field_A = arg_8;
            sprite->counter = counter;
            struct7_frame_num_tbl[i] = 0;
        }
    }
}

void struct7_update_sprites()
{
    for(int i=0; i < MAX_STRUCT7_SPRITES; i++)
    {
        struc_7 *sprite = &struc7_sprites[i];

        if(sprite->is_active_flag)
        {
            if(is_sprite_on_screen(sprite->actorInfoIndex, sprite->frame_num, sprite->x, sprite->y))
            {

                if(sprite->actorInfoIndex == 0x63)
                {
                    
                    display_actor_sprite_maybe(sprite->actorInfoIndex, struct7_frame_num_tbl[i], sprite->x, sprite->y, 5);
                }
                else
                {
                    display_actor_sprite_maybe(sprite->actorInfoIndex, struct7_frame_num_tbl[i], sprite->x, sprite->y, 0);
                }
                
                if(sprite->actorInfoIndex == 0x1b)
                {
                    sprite->x--;
                    sprite->y = sprite->y + (rand() % 3);
                }
                sprite->x = sprite->x + player_x_offset_tbl[sprite->field_A];
                sprite->y = sprite->y + player_y_offset_tbl[sprite->field_A];
                struct7_frame_num_tbl[i]++;
                if(struct7_frame_num_tbl[i] == sprite->frame_num)
                {
                    struct7_frame_num_tbl[i] = 0;
                    if(sprite->counter != 0)
                    {
                        sprite->counter--;
                        if(sprite->counter == 0)
                        {
                            sprite->is_active_flag = 0;
                        }
                    }
                }
            }
            else
            {
                sprite->is_active_flag = 0;
            }
        }
    }
 
    return;
}

void struct7_clear_sprites()
{
    for(int i=0; i < MAX_STRUCT7_SPRITES; i++)
    {
        struc7_sprites[i].is_active_flag = 0;
    }
}

void sub_1BA0F(int x_pos, int y_pos)
{

}

void struct4_add_sprite(int actorInfoIndex, int frame_num, int x_pos, int y_pos)
{

}
