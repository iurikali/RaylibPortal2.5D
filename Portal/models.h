#ifndef MODELS_H_INCLUDED
#define MODELS_H_INCLUDED

#include "raylib.h"
#include "structs.h"

Models NewModels(Model *array, char axe, Color color, int frame_vel, int image_number, int *fixed_position);

void DrawModels(Vector3 position, Models *model);


#endif // FUNCOES_H_INCLUDED
