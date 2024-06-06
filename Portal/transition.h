#ifndef TRANSITION_H_INCLUDED
#define TRANSITION_H_INCLUDED

#include "structs.h"
#include "defines.h"
#include "raylib.h"

Transition NewTransition(int type, Color color);

//Funcao de logica
void TransitionUpdate(Transition *tran/*, int *exit_opened, Portal *portals, char (*mapa)[LINHAS][COLUNAS], int *renderizado, int *num_mapa, int *qtd_alavancas, int *qtd_inimigos_max*/);

void DrawTransition(Transition tran);


#endif // TRANSITION_H_INCLUDED