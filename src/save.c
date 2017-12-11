//
// Created by efry on 4/11/2017.
//

#include "save.h"
#include "defines.h"
#include "player.h"
#include "game.h"
#include "map.h"

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
    //TODO save game here.
}

void load_savegame_file(char suffix)
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
         has_had_bomb_flag = temp_save.has_had_bomb_flag;
         show_monster_attack_hint = temp_save.show_monster_attack_hint;
         knows_about_powerups_flag = temp_save.knows_about_powerups_flag;
    }
    //TODO load game here.
}
