//
// Created by efry on 12/11/2017.
//

#include "effects.h"

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
        }
    }
}

void struct7_update_sprites()
{

}

void sub_1BA0F(int x_pos, int y_pos)
{

}

void struct4_add_sprite(int actorInfoIndex, int frame_num, int x_pos, int y_pos)
{

}
