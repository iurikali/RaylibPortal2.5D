#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "defines.h"

void RenderMap(char map[ROWS][COLS]);

void LoadMap(int number, char (*map)[ROWS][COLS]);

#endif // MAP_H_INCLUDED