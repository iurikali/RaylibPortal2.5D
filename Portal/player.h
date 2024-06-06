#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "structs.h"
#include "defines.h"

Player NewPlayer();

void PlayerUpdate(Player *player);

void CheckingCollisionWall(Player *player, char map[ROWS][COLS]);

void RenderPlayer(Player *player);

void RenderAim(Models *aim_models, float theta, Player player);

#endif // PLAYER_H_INCLUDED
