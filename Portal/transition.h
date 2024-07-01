#ifndef TRANSITION_H_INCLUDED
#define TRANSITION_H_INCLUDED

#include "structs.h"
#include "defines.h"
#include "raylib.h"

Transition NewTransition(int type, Color color);

//Funcao de logica
void TransitionUpdate(Transition *tran);

void DrawTransition(Transition tran);


#endif // TRANSITION_H_INCLUDED