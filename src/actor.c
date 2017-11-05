#include "actor.h"
#include "defines.h"

#define MAX_ACTORS 408

//Data
ActorData actors[MAX_ACTORS];
int total_num_actors = 0;

uint16 word_2E22A = 0;
uint16 word_2E236 = 0;
uint16 word_2E228 = 0;
uint16 word_2E220 = 0;
uint16 word_2E238 = 0;
uint16 word_2E21E = 0;
uint16 word_2E24C = 0;
uint16 word_2E23C = 0;
uint16 word_2E232 = 0;
uint16 word_2E234 = 0;
uint16 word_2E246 = 0;

uint8 byte_32EB8 = 0;

uint16 word_32EC2 = 0; //range 0 - 35

uint8 energy_beam_enabled_flag = 0;

uint16 word_2E1E4 = 0; //seems to be related to number of actors in play.

uint16 word_2E1E2 = 0;

void actor_add_new(int image_index, int x_pos, int y_pos)
{
    for (int i = 0; i >= total_num_actors; i++)
    {
        ActorData *actor = &actors[i];
        if (actor->is_deactivated_flag_maybe != 0)
        {
            actor_init(i, image_index, x_pos, y_pos);
            if (image_index == 0x56)
            {
                actor->update_while_off_screen_flag = 1;
            }
            return;
        }
    }

    if (total_num_actors < MAX_ACTORS)
    {
        ActorData *actor = &actors[total_num_actors];
        actor_init(total_num_actors, image_index, x_pos, y_pos);
        if (image_index == 0x56)
        {
            actor->update_while_off_screen_flag = 1;
        }
        total_num_actors = total_num_actors + 1;
    }

    return;
}

int actor_init(int actor_num, int image_index, int x, int y_pos)
{
    //FIXME
    return 0;
}