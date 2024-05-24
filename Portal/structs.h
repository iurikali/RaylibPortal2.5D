#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "raylib.h"

typedef struct player_struct
{
    Vector3 position;
    Vector3 hitbox;
    float speed, velh, velv;
}Player;



#endif // STRUCTS_H_INCLUDED