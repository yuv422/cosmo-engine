//
// cosmo_engine created on 12/Nov/2017.
//
#ifndef COSMO_ENGINE_EFFECTS_H
#define COSMO_ENGINE_EFFECTS_H

int struct6_1B4FC(int actorInfoIndex, int frame_num, int x_pos, int y_pos);
int sub_1BAAD(int actorInfoIndex, int frame_num, int x_pos, int y_pos);
void effect_add_sprite(int actorInfoIndex, int frame_num, int x_pos, int y_pos, int arg_8, int counter);

void effect_update_sprites();
void effect_clear_sprites();

void struct4_add_sprite(int actorInfoIndex, int frame_num, int x_pos, int y_pos);
void struct4_update_sprites();
void struct4_clear_sprites();

void sub_1BA0F(int x_pos, int y_pos);

void update_rain_effect();

#endif //COSMO_ENGINE_EFFECTS_H
