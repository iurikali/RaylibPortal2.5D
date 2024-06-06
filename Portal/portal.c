#include "portal.h"
#include "raylib.h"
#include "defines.h"
#include "structs.h"
#include "mathe.h"
#include <math.h>
#include <stdio.h>
#include "models.h"

Portal NewPortal(Color color)
{
    Portal portal = {0};
    portal.color = color;
    portal.placed = 0;
    portal.entity.position.x = 0.0f;
    portal.entity.position.z = 0.0f;
    portal.entity.position.y = 0.0f;
    portal.entity.speed = 0.3f;
    portal.entity.velh = 0.0f;
    portal.entity.velv = 0.0f;

    portal.entity.size = .2f;

    portal.entity.hitbox = (BoundingBox){(Vector3){portal.entity.position.x - portal.entity.size * .5f,
                                                   portal.entity.position.y - portal.entity.size * .5f,
                                                   portal.entity.position.z - portal.entity.size * .5f},
                                         (Vector3){portal.entity.position.x + portal.entity.size * .5f,
                                                   portal.entity.position.y + portal.entity.size * .5f,
                                                   portal.entity.position.z + portal.entity.size * .5f}};

    return portal;
}


void PortalUpdate(Portal *portals, Player *player, int *turn, int *lanched, char map[ROWS][COLS], int *used, float *theta, Camera3D *cam)
{
    //Calculando o theta
    Vector2 screen_cube_position = GetWorldToScreen(player->entity.position, *cam);
    *theta = PointDirection(screen_cube_position.x, screen_cube_position.y,
    GetMouseX(), GetMouseY());

    //Apertando para disparar o portal
    if (IsMouseButtonPressed(0) && !(*lanched) && map[(int)player->entity.position.z][(int)player->entity.position.x] != 'W')
    {
        //Mudando o portal
        *turn = !(*turn);

        (portals + *turn)->entity.size = .2f;

        //Passando a posicao do player
        ((portals + *turn)->entity).position.x = player->entity.position.x;
        ((portals + *turn)->entity).position.z = player->entity.position.z;

        //Passando a dx
        ((portals + *turn)->entity).velh = ((portals + *turn)->entity).speed * cosf(*theta);
        ((portals + *turn)->entity).velv = ((portals + *turn)->entity).speed * sinf(*theta);

        //Descolando ele
        (portals + *turn)->placed = 0;

        *lanched = 1;
    }

    //Se foi disparado e ainda nao bateu
    if (*lanched)
    {
        if (((portals + *turn)->entity).velh != 0.0f || ((portals + *turn)->entity).velv != 0.0f)
        {

            //Verificando a colisao do portal com a parede
            if (map[(int)((portals + *turn)->entity.position.z + (portals + *turn)->entity.velv)][(int)((portals + *turn)->entity.position.x + (portals + *turn)->entity.velh)] == 'W' 
                && !(portals + *turn)->placed)
            {
                //Parando o portal e colocando ele na posicao certa
                (portals + *turn)->entity.position.x = (int) ((portals + *turn)->entity.position.x) + .5f;
                (portals + *turn)->entity.position.z = (int) ((portals + *turn)->entity.position.z) + .5f;


                (portals + *turn)->entity.velh = 0.0f;
                (portals + *turn)->entity.velv = 0.0f;
                (portals + *turn)->placed = 1;

                (portals + *turn)->entity.size = 1.0f;
            }
        }
    }

    ((portals + *turn)->entity).position.x += ((portals + *turn)->entity).velh;
    ((portals + *turn)->entity).position.z += ((portals + *turn)->entity).velv;

    //Colidimos
    if ((portals + *turn)->placed)
    {
        //Atualizando a mascara
        (portals + *turn)->entity.hitbox = (BoundingBox){(Vector3){(portals + *turn)->entity.position.x - (portals + *turn)->entity.size * .4f,
                                                                   (portals + *turn)->entity.position.y - (portals + *turn)->entity.size * .4f,
                                                                   (portals + *turn)->entity.position.z - (portals + *turn)->entity.size * .4f}, 
                                                         (Vector3){(portals + *turn)->entity.position.x + (portals + *turn)->entity.size * .4f,
                                                                   (portals + *turn)->entity.position.y + (portals + *turn)->entity.size * .4f,
                                                                   (portals + *turn)->entity.position.z + (portals + *turn)->entity.size * .4f}};


        //Aumentando a escala
        /*if ((portais + *vez)->entidade.sprite.escala < 1)
        {
            (portais + *vez)->entidade.sprite.escala+= .1;
        }
        else
        {
            (portais + *vez)->entidade.sprite.escala = 1;
            //Ja bateu, entao podemos disparar de novo
            *disparou = 0;
        }*/
        *lanched = 0;
    }


    //Verficando se ambos foram colocados
    if (portals->placed == 1 && (portals + 1)->placed == 1)
    {
        //Verificando se paramos em cima de um buraco
        if (map[(int) portals->entity.position.z][(int) portals->entity.position.x] != 'H' &&
            map[(int) (portals + 1)->entity.position.z][(int) (portals + 1)->entity.position.x] != 'H')
        {
            //Verificando a colisao do primeiro portal com o player
            if (CheckCollisionBoxes(portals->entity.hitbox, player->entity.hitbox))
            {
                //Usando so uma vez o portal
                if (!(*used))
                {
                    //Mandando o player parar
                    player->stop = 1;

                    player->entity.position.x = (portals + 1)->entity.position.x;
                    player->entity.position.z = (portals + 1)->entity.position.z;
                    *used = 1;
                }
                else
                {
                    player->stop = 0;
                }
            }
            //Verificando a colisao com o segundo portal
            else if (CheckCollisionBoxes((portals + 1)->entity.hitbox, player->entity.hitbox))
            {
                //Usando so uma vez o portal
                if (!(*used))
                {
                    //Mandando o player parar
                    player->stop = 1;

                    player->entity.position.x = (portals)->entity.position.x;
                    player->entity.position.z = (portals)->entity.position.z;
                    *used = 1;
                }
                else
                {
                    player->stop = 0;
                }
            }
            //Se o player nao ta mais colidindo com os portais
            else
            {
                *used = 0;
            }
        }
    }
}

void RenderPortal(Portal *portals)
{
    /*DrawCubeV(portals->entity.position, (Vector3){portals->entity.size, portals->entity.size, portals->entity.size}, portals->color);

    DrawCubeV((portals + 1)->entity.position, (Vector3){(portals + 1)->entity.size, (portals + 1)->entity.size, (portals + 1)->entity.size}, (portals + 1)->color);*/

    for (int i = 0; i < 2; i++)
    {
        if ((portals + i)->placed)
        {
            //Rotacionando
            (portals + i)->entity.models.angle += 1;
            //Desenhando os modelos
            DrawModels((portals + i)->entity.position, &((portals + i)->entity.models));
        }
        else
        {
            //(portals + i)->entity.models.angle = 0;
            DrawCube((portals + i)->entity.position, SIZE_CUBE_PORTAL, SIZE_CUBE_PORTAL, SIZE_CUBE_PORTAL, (portals + i)->color);
        }

    }
}