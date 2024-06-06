#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "defines.h"
#include "structs.h"

int ThereIsFile(char dir[]);

int LoadGame(char (*map)[ROWS][COLS], Player *player, Lever levers[MAX_LEVERS], Enemy enemys[MAX_ENEMYS], int *exit_opened, int *level, int *turn,
                 Portal portals[2]);

int SaveGame(Player player, Enemy enemys[MAX_ENEMYS], Lever levers[MAX_LEVERS], int level, int exit_opened, int turn, Portal portals[2]);

void InicialMenu(Rectangle a, Rectangle b, Rectangle c, int *menu, Font f1, Texture2D background[3], int *first_time, int *img, int *number_map,
                  char (*map)[ROWS][COLS], int *load, Player *player, Lever levers[MAX_LEVERS], Enemy enemys[MAX_ENEMYS], int *exit_opened, int *turn,
                  Portal portals[2], int *there_is_file, int *there_is_map, int *load_map_menu);

void MenuPause(Rectangle a, Rectangle b, Rectangle c, Rectangle d, Rectangle e, int *pause, Font fp, int *menu, int *load,
                Player *player, Enemy enemys[MAX_ENEMYS], Lever levers[MAX_LEVERS], int *level, int *exit_opened, char (*map)[ROWS][COLS], int *rendered,
                int *qtd_levers, int *qtd_enemys, int *turn, Portal portals[2], int *saved, int *there_is_file);


#endif // MENU_H_INCLUDED