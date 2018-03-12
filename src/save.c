//
// Created by efry on 4/11/2017.
//

#include <stdlib.h>
#include "save.h"
#include "defines.h"
#include "player.h"
#include "game.h"
#include "map.h"
#include "dialog.h"

int cleanup_and_exit();

typedef struct SaveGameData {
    uint8 health;
    uint32 score;
    uint16 num_stars_collected;
    uint16 current_level;
    uint16 num_bombs;
    uint8 num_health_bars;
    uint16 cheats_used_flag;
    uint16 has_had_bomb_flag;
    uint8 show_monster_attack_hint;
    uint8 knows_about_powerups_flag;
} SaveGameData;

static SaveGameData temp_save;

uint16 cheats_used_flag = 0;

void write_savegame_file(char suffix)
{
    if(suffix == 'T')
    {
        temp_save.health = health;
        temp_save.score = score;
        temp_save.num_stars_collected = num_stars_collected;
        temp_save.current_level = current_level;
        temp_save.num_bombs = num_bombs;
        temp_save.num_health_bars = num_health_bars;
        temp_save.cheats_used_flag = cheats_used_flag;
        temp_save.has_had_bomb_flag = has_had_bomb_flag;
        temp_save.show_monster_attack_hint = show_monster_attack_hint;
        temp_save.knows_about_powerups_flag = knows_about_powerups_flag;
    }
    else
    {
        char filename[13];
        sprintf(filename, "COSMO%d.SV%c", get_episode_number(), suffix);
        File savefile;
        if(!file_open(filename, "wb", &savefile))
        {
            printf("Error: saving file %s\n", filename);
            return;
        }

        file_write2(health, &savefile);
        file_write4(score, &savefile);
        file_write2(num_stars_collected, &savefile);
        file_write2(current_level, &savefile);
        file_write2(num_bombs, &savefile);
        file_write2(num_health_bars, &savefile);
        file_write2(cheats_used_flag, &savefile);
        file_write2(has_had_bomb_flag, &savefile);
        file_write2(show_monster_attack_hint, &savefile);
        file_write2(knows_about_powerups_flag, &savefile);
        uint16 checksum = (uint16)(health + num_stars_collected + current_level + num_bombs + num_health_bars);
        file_write2(checksum, &savefile);

        file_close(&savefile);
    }
}

bool load_savegame_file(char suffix)
{
    if(suffix == 'T')
    {
         health = temp_save.health;
         score = temp_save.score;
         num_stars_collected = temp_save.num_stars_collected;
         current_level = temp_save.current_level;
         num_bombs = temp_save.num_bombs;
         num_health_bars = temp_save.num_health_bars;
         cheats_used_flag = temp_save.cheats_used_flag;
//         has_had_bomb_flag = temp_save.has_had_bomb_flag;
//         show_monster_attack_hint = temp_save.show_monster_attack_hint;
//         knows_about_powerups_flag = temp_save.knows_about_powerups_flag;
    }
    else
    {
        File file;
        char filename[13];
        sprintf(filename, "COSMO%d.SV%c", get_episode_number(), suffix);

        if(!file_open(filename, "rb", &file))
        {
            return false;
        }

        health = (uint8)file_read2(&file);
        score = file_read4(&file);
        num_stars_collected = file_read2(&file);
        current_level = file_read2(&file);
        num_bombs = file_read2(&file);
        num_health_bars = (uint8)file_read2(&file);
        cheats_used_flag = file_read2(&file);
        has_had_bomb_flag = file_read2(&file);;
        show_monster_attack_hint = (uint8)file_read2(&file);;
        knows_about_powerups_flag = (uint8)file_read2(&file);;

        uint16 checksum = file_read2(&file);

        file_close(&file);

        if(checksum != health + num_stars_collected + current_level + num_bombs + num_health_bars)
        {
            malformed_savegame_dialog();
            exit(cleanup_and_exit());
        }
    }

    return true;
}
