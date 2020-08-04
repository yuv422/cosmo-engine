//
// Created by efry on 25/10/2017.
//

#include <stdlib.h>
#include "util.h"
#include "defines.h"


int cosmo_rand()
{
    //FIXME
    return rand() % 0xffff;
}

uint16 cosmo_strnlen(const char *str, uint16 maxLength) {
    uint16 c = 0;
    for (; c < maxLength; c++) {
        if (str[c] == 0) {
            break;
        }
    }
    return c;
}
