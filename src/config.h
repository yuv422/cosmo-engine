//
// cosmo_engine created on 31/Dec/2017.
//
#ifndef COSMO_ENGINE_CONFIG_H
#define COSMO_ENGINE_CONFIG_H

//Data
extern SDL_Keycode cfg_up_key;
extern SDL_Keycode cfg_down_key;
extern SDL_Keycode cfg_left_key;
extern SDL_Keycode cfg_right_key;
extern SDL_Keycode cfg_jump_key;
extern SDL_Keycode cfg_bomb_key;

void load_config_file(const char *filename);
void write_config_file(const char *filename);

#endif //COSMO_ENGINE_CONFIG_H
