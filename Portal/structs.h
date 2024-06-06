#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "raylib.h"

typedef struct models_struct
{
    Model *model;
    float angle;
    Vector3 axes;
    Vector3 scale;
    Color color;

    int frame_vel, frame_index, timer, image_number;
}Models;

typedef struct entity_struct
{
    Vector3 position;
    float size;
    float speed, velh, velv;
    BoundingBox hitbox;
    Models models;
}Entity;

typedef struct player_struct
{
    Entity entity;
    int stop;
    int life;
    Vector3 inicial_position;
}Player;

typedef struct portal_struct
{
    Entity entity;
    Color color;
    int placed;
}Portal;

typedef struct enemy_struct
{
    Entity entity;
    int walking, placed;
    Vector3 inicial_position;
}Enemy;

typedef struct lever_struct
{
    Entity entity;
    int placed, used;
}Lever;

typedef struct transition_struct
{
    Rectangle rectangle;
    Color color;
    int speed, type, activated, changed, change_level;
}Transition;



#endif // STRUCTS_H_INCLUDED