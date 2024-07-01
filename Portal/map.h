#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "defines.h"
#include "structs.h"

void RenderMap(char map[ROWS][COLS], Models *wall_models, Models *spike_models, Models *exit_models);

void LoadMap(int *number, char (*map)[ROWS][COLS]);

void FirstReadMap(char map[ROWS][COLS], int *rendered, Enemy array_enemys[MAX_ENEMYS], int *qtd_enemys_max, Player *player, Lever levers[MAX_LEVERS], int *qtd_levers_max,
                  Model *enemy_model, int *fixed_enemy, Model *lever_model, int *fixed_lever, int *max_values, int *min_values);

void ResetHit(Player *player, Portal portals[2], Enemy enemys[MAX_ENEMYS], int qtd_inimigos);

void DrawFloor(int *max_values, int *min_values);

#endif // MAP_H_INCLUDED