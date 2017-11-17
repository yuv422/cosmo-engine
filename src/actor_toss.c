//
// Created by Eric Fry on 17/11/2017.
//

#include "actor_toss.h"
#include "actor.h"

#define MAX_TOSSED_ACTORS 6

typedef struct ActorToss
{
int actorInfoIndex;
int x;
int y;
int counter;
} ActorToss;

ActorToss actorToss[MAX_TOSSED_ACTORS];

void actor_toss_add_new(int actorInfoIndex, int x_pos, int y_pos) {
    for(int i=0;i<MAX_TOSSED_ACTORS;i++)
    {
        if(actorToss[i].actorInfoIndex == 0)
        {
            actorToss[i].actorInfoIndex = actorInfoIndex;
            actorToss[i].x = x_pos;
            actorToss[i].y = y_pos;
            actorToss[i].counter = 0;
        }
    }
}

void actor_toss_update() {
    for(int i=0;i<MAX_TOSSED_ACTORS;i++)
    {
        ActorToss *at = &actorToss[i];
        if (at->actorInfoIndex == 0)
            continue;
        
//        // node 0001b5c8-0001b5dd #insn=5 use={si} def={bx} in={ax, si} out={ax, bx, si} pred={ 1B6B9} CONDJUMP target=0001b5e2 follow=0001b6b8
//        loc_1B5C8:
//        bx = (si << 3) + stru_2E2EE;
//        var_4[2] = REGISTER_29;
//        var_4 = bx;
//        if (at->actorInfoIndex != 0) goto loc_1B5E2;

// node 0001b5e2-0001b602 #insn=5 use={bx} def={ax} in={bx, si} out={ax, si} pred={ 1B5C8} CONDJUMP target=0001b62c follow=0001b604
        loc_1B5E2:
        at->counter = at->counter + 1;
        at->y--;
        if (sprite_blocking_check(0, at->actorInfoIndex, 0, at->x, at->y) == NOT_BLOCKED)
        {
            // node 0001b604-0001b60c #insn=2 use={} def={bx} in={ax, si} out={ax, bx, si} pred={ 1B5E2} CONDJUMP target=0001b660 follow=0001b60e
            if (at->counter >= 9 || sprite_blocking_check(0, at->actorInfoIndex, 0, at->x, --at->y) == NOT_BLOCKED)
            {
                if(at->counter != 11)
                {
                    display_actor_sprite_maybe(at->actorInfoIndex, 0, at->x, at->y, 4);
                }
                else
                {
                    actor_add_new(at->actorInfoIndex, at->x, at->y);
                    display_actor_sprite_maybe(at->actorInfoIndex, 0, at->x, at->y, 4);
                    at->actorInfoIndex = 0;
                }
            }
            else
            {
                actor_add_new(at->actorInfoIndex, at->x, at->y + 1);
                display_actor_sprite_maybe(at->actorInfoIndex, 0, at->x, at->y + 1, 0);
                at->actorInfoIndex = 0;
            }
        }
        else
        {
            // node 0001b62c-0001b69d #insn=8 use={} def={bx} in={ax, si} out={ax, si} pred={ 1B5E2 1B60E} JUMP target=0001b6b8
            actor_add_new(at->actorInfoIndex, at->x, at->y + 1);
            display_actor_sprite_maybe(at->actorInfoIndex, 0, at->x, at->y + 1, 0);
            at->actorInfoIndex = 0;
        }




//// node 0001b6b8-0001b6b8 #insn=2 use={si} def={si} in={ax, si} out={ax, si} pred={ 1B5C8 1B660 1B62C} FALLTHROUGH follow=0001b6b9
//        loc_1B6B8:
//        si = si + 1;

    }
//    si = 0;
//    goto loc_1B6B9;
//
//
//// node 0001b6b9-0001b6bd #insn=2 use={si} def={} in={ax, si} out={ax, si} pred={ 1B5BE 1B6B8} CONDJUMP target=0001b6c2 follow=0001b5c8
//    loc_1B6B9:
//    if (si >= MAX_TOSSED_ACTORS) goto loc_1B6C2;
//
//// node 0001b6c2-0001b6c4 #insn=3 use={ax} def={si} in={ax} out={} pred={ 1B6B9} RETURN
//    loc_1B6C2:
//    /* pop  */
//    return ax;
}

void actor_toss_clear_all() {
    for(int i=0;i<MAX_TOSSED_ACTORS;i++)
    {
        actorToss[i].actorInfoIndex = 0;
    }
}
