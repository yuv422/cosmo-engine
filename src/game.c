//
// Created by efry on 25/10/2017.
//

#include "palette.h"
#include "game.h"

typedef enum
{
    QUIT,
    PAUSED,
    CONTINUE
} input_state_enum;

input_state_enum read_input()
{
    //FIXME
    return CONTINUE;
}
void game_loop()
{
    int input_state = 0;

    for(;;)
    {
        do
        {
            //lock to 10 FPS here.

            update_palette_anim();

            input_state = read_input();
            if (input_state == QUIT)
                return;

        } while(input_state == PAUSED);


    }
}
