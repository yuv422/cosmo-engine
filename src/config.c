//
// cosmo_engine created on 31/Dec/2017.
//

#include <SDL_keycode.h>
#include <files/file.h>
#include <sound/music.h>
#include <sound/sfx.h>
#include "config.h"
#include "high_scores.h"

SDL_Keycode cfg_up_key;
SDL_Keycode cfg_down_key;
SDL_Keycode cfg_left_key;
SDL_Keycode cfg_right_key;
SDL_Keycode cfg_jump_key;
SDL_Keycode cfg_bomb_key;

#define MAX_SCORE_STRING_LENGTH 13

uint32 read_score(File *file)
{
    uint32 cur_pos = file_get_current_position(file);
    uint32 file_len = file_get_filesize(file);
    char buf[MAX_SCORE_STRING_LENGTH+1];
    memset(buf, 0, MAX_SCORE_STRING_LENGTH+1);
    for(int i=0; i < MAX_SCORE_STRING_LENGTH && cur_pos + i < file_len; i++)
    {
        char c = file_read1(file);
        if(c == ' ')
        {
            break;
        }
        buf[i] = c;
    }

    return (uint32)strtol(buf, NULL, 10);
}

void read_score_name(File *file, char *buf, uint16 buf_size)
{
    uint32 cur_pos = file_get_current_position(file);
    uint32 file_len = file_get_filesize(file);
    memset(buf, 0, buf_size);
    for(int i=0; i < buf_size-1 && cur_pos + i < file_len; i++)
    {
        char c = file_read1(file);
        if(c == 0xa)
        {
            break;
        }
        buf[i] = c;
    }
}

void load_config_file(const char *filename)
{
    File file;
    clear_high_score_table();

    if(file_open(filename, "rb", &file))
    {
        //FIXME key redefine.
        file_seek(&file, 6);

        music_on_flag = file_read1(&file);
        sfx_on_flag = file_read1(&file);

        for(int i=0; i < NUM_HIGH_SCORE_ENTRIES; i++)
        {
            uint32 s = read_score(&file);
            char name_buf[HIGH_SCORE_MAX_NAME_LENGTH+1];
            read_score_name(&file, name_buf, HIGH_SCORE_MAX_NAME_LENGTH+1);

            add_high_score_with_name(s, name_buf);
        }
        file_close(&file);
    }
    else
    {
        cfg_up_key = SDLK_UP;
        cfg_down_key = SDLK_DOWN;
        cfg_left_key = SDLK_LEFT;
        cfg_right_key = SDLK_RIGHT;
        cfg_jump_key = SDLK_LCTRL;
        cfg_bomb_key = SDLK_LALT;
        music_on_flag = 1;
        sfx_on_flag = 1;

        add_high_score_with_name(0xf4240, "BART");
        add_high_score_with_name(0xdbba0, "LISA");
        add_high_score_with_name(0xc3500, "MARGE");
        add_high_score_with_name(0xaae60, "ITCHY");
        add_high_score_with_name(0x927c0, "SCRATCHY");
        add_high_score_with_name(0x7a120, "MR. BURNS");
        add_high_score_with_name(0x61a80, "MAGGIE");
        add_high_score_with_name(0x493e0, "KRUSTY");
        add_high_score_with_name(0x30d40, "HOMER");
    }
}

void write_config_file(const char *filename)
{
    File file;
    if(!file_open(filename, "wb", &file))
    {
        return;
    }

    //FIXME need to write actual dos scancodes here.
    file_write1(0, &file);
    file_write1(0, &file);
    file_write1(0, &file);
    file_write1(0, &file);
    file_write1(0, &file);
    file_write1(0, &file);
    file_write1(music_on_flag, &file);
    file_write1(sfx_on_flag, &file);

    for(int i=0; i < NUM_HIGH_SCORE_ENTRIES; i++)
    {
        char buf[32];
        HighScore high_score = get_high_score(i);
        sprintf(buf, "%d %s", high_score.score, high_score.name);
        for(int j=0;j < strlen(buf); j++)
        {
            file_write1((uint8)buf[j], &file);
        }
        file_write1(0xa, &file);
    }
    file_close(&file);
}
