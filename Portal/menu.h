#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "defines.h"
#include "structs.h"

int ThereIsFile(char dir[]);

void InicialMenu(Rectangle b, Rectangle c, int *menu, Font f1, Texture2D background[3], int *first_time, int *img,
                  char (*map)[ROWS][COLS], int *there_is_map, int *close_game);

void MenuPause(Rectangle b, Rectangle c, int *pause, Font fp, int *close_game);

void EndGame(Rectangle b, int *menu, Font f1, int *won, int *dead, Font f2, Texture2D background_over, Texture2D background_win, Music *music, Music *music_win);

#endif // MENU_H_INCLUDED