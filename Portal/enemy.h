#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "structs.h"
#include "defines.h"

int ShouldMove(Entity entity, char map[ROWS][COLS], int holes);

void MoveIni(Enemy *enemy, char map[ROWS][COLS], Player *player, int *rendered, int pause, int *dead, int *reset, Sound *sfx_damage);

void RenderEnemys(Enemy enemys[MAX_ENEMYS], char map[ROWS][COLS], Player *player, int *rendered, int qtd_enemys_max, int pause, int *dead, int *reset, Sound *sfx_damage);

#endif // ENEMY_H_INCLUDED
