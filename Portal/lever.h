#ifndef LEVER_H_INCLUDED
#define LEVER_H_INCLUDED

#include "structs.h"
#include "defines.h"

void LeverUpdate(Lever levers[MAX_LEVERS], Player *player, char (*map)[ROWS][COLS], int *qtd_levers, int qtd_levers_max, Sound *sfx_active);

int ExitUpdate(Lever levers[MAX_LEVERS], int qtd_levers_max, Sound *sfx_exit);

void leaving(Player *player, Transition *tran, char map[ROWS][COLS]);

#endif // LEVER_H_INCLUDED