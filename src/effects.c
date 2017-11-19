//
// Created by efry on 12/11/2017.
//

#include <stdlib.h>
#include "effects.h"
#include "defines.h"
#include "actor.h"
#include "player.h"
#include "map.h"

#define MAX_EFFECT_SPRITES 10

typedef struct effect_sprite
{
    int is_active_flag;
    int actorInfoIndex;
    int frame_num;
    int x;
    int y;
    int field_A;
    int counter;
} effect_sprite;

effect_sprite static_effect_sprites[MAX_EFFECT_SPRITES];
uint16 effect_frame_num_tbl[MAX_EFFECT_SPRITES];

int struct6_1B4FC(int actorInfoIndex, int frame_num, int x_pos, int y_pos)
{
    return 0;
}

int sub_1BAAD(int actorInfoIndex, int frame_num, int x_pos, int y_pos)
{
    return 0;
}

void effect_add_sprite(int actorInfoIndex, int frame_num, int x_pos, int y_pos, int arg_8, int counter)
{
    for(int i=0;i<MAX_EFFECT_SPRITES;i++)
    {
        effect_sprite *sprite = &static_effect_sprites[i];
        if(!sprite->is_active_flag)
        {
            sprite->is_active_flag = 1;
            sprite->actorInfoIndex = actorInfoIndex;
            sprite->frame_num = frame_num;
            sprite->x = x_pos;
            sprite->y = y_pos;
            sprite->field_A = arg_8;
            sprite->counter = counter;
            effect_frame_num_tbl[i] = 0;
        }
    }
}

void effect_update_sprites()
{
    for(int i=0; i < MAX_EFFECT_SPRITES; i++)
    {
        effect_sprite *sprite = &static_effect_sprites[i];

        if(sprite->is_active_flag)
        {
            if(is_sprite_on_screen(sprite->actorInfoIndex, sprite->frame_num, sprite->x, sprite->y))
            {

                if(sprite->actorInfoIndex == 0x63)
                {
                    
                    display_actor_sprite_maybe(sprite->actorInfoIndex, effect_frame_num_tbl[i], sprite->x, sprite->y, 5);
                }
                else
                {
                    display_actor_sprite_maybe(sprite->actorInfoIndex, effect_frame_num_tbl[i], sprite->x, sprite->y, 0);
                }
                
                if(sprite->actorInfoIndex == 0x1b)
                {
                    sprite->x--;
                    sprite->y = sprite->y + (rand() % 3);
                }
                sprite->x = sprite->x + player_x_offset_tbl[sprite->field_A];
                sprite->y = sprite->y + player_y_offset_tbl[sprite->field_A];
                effect_frame_num_tbl[i]++;
                if(effect_frame_num_tbl[i] == sprite->frame_num)
                {
                    effect_frame_num_tbl[i] = 0;
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

void effect_clear_sprites()
{
    for(int i=0; i < MAX_EFFECT_SPRITES; i++)
    {
        static_effect_sprites[i].is_active_flag = 0;
    }
}

void sub_1BA0F(int x_pos, int y_pos)
{

}

void struct4_add_sprite(int actorInfoIndex, int frame_num, int x_pos, int y_pos)
{

}

void update_rain_effect() //FIXME this rain doesn't look quite right. It seems to come down in lines. :(
{

    int x = (rand() % 38) + mapwindow_x_offset;
    int y = (rand() % 18) + mapwindow_y_offset;
    int map_tile_cell = map_get_tile_cell(x, y);

    if((rand() & 1) != 0)
    {
        if((tileattr_mni_data[map_tile_cell / 8] & TILE_ATTR_SLIPPERY) != 0)
        {
            effect_add_sprite(0x63, 5, x, y, 0, 1);
        }
    }
    if(rain_flag != 0)
    {
        y = mapwindow_y_offset + 1;

        if(map_get_tile_cell(x, y) == 0)
        {
            effect_add_sprite(0x1b, 1, x, y, 6, 0x14);
        }
    }
    return;
}
