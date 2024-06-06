#include "structs.h"
#include "player.h"
#include "defines.h"
#include "mathe.h"
#include "models.h"
#include <stdio.h>

Player NewPlayer()
{
    Player player = {0};
    player.entity.position = (Vector3){0.0f, 0.0f, 0.0f};
    player.entity.size = 1.0f;
    player.entity.speed = .1f;
    player.entity.velh = 0;
    player.entity.velv = 0;
    player.stop = 0;
    player.life = 3;
    player.inicial_position = player.entity.position;


    player.entity.hitbox = (BoundingBox) {(Vector3){player.entity.position.x - player.entity.size * .5f,
                                                    player.entity.position.y - player.entity.size * .5f,
                                                    player.entity.position.z - player.entity.size * .5f},
                                          (Vector3){player.entity.position.x + player.entity.size * .5f,
                                                    player.entity.position.y + player.entity.size * .5f,
                                                    player.entity.position.z + player.entity.size * .5f}};

    return player;
}




void PlayerUpdate(Player *player)
{
    //Fazendo a verificacao das teclas para o player andar
    int right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
    int left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    int up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
    int down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);


    player->entity.velh = (right - left) * player->entity.speed;
    player->entity.velv = (down - up) * player->entity.speed;

    //Rotacionando o playe conforme o movimento
    if (player->entity.velh != 0 || player->entity.velv != 0)
        player->entity.models.angle = RadianToDegrees(PointDirectionMath(0, 0, player->entity.velh, player->entity.velv)) + 90;
}




void RenderPlayer(Player *player)
{   
    /*//Desenhando inicialmente um cubo para representar o player
    DrawCube(player->entity.position, player->entity.size, player->entity.size, player->entity.size, PURPLE);

    //Desenhando as bordas do cubo
    DrawCubeWires(player->entity.position, player->entity.size, player->entity.size, player->entity.size, GREEN);*/
    DrawModels(player->entity.position, &(player->entity.models));
}

void CheckingCollisionWall(Player *player, char map[ROWS][COLS])
{   
    //Horizontal
    if (map[(int) (player->entity.position.z - ALMOST_HALF)][(int) (player->entity.position.x + (CUBE_SIZE * .5 * SignFloat(player->entity.velh) + player->entity.velh))] == 'W' ||
        map[(int) (player->entity.position.z + ALMOST_HALF)][(int) (player->entity.position.x + (CUBE_SIZE * .5 * SignFloat(player->entity.velh) + player->entity.velh))] == 'W' ||
        map[(int) (player->entity.position.z - ALMOST_HALF)][(int) (player->entity.position.x + (CUBE_SIZE * .5 * SignFloat(player->entity.velh) + player->entity.velh))] == 'H' ||
        map[(int) (player->entity.position.z + ALMOST_HALF)][(int) (player->entity.position.x + (CUBE_SIZE * .5 * SignFloat(player->entity.velh) + player->entity.velh))] == 'H')
    {
        //Ajustando a posicao
        if (player->entity.velh > 0)
            player->entity.position.x = (int) (player->entity.position.x + (CUBE_SIZE * .5 * SignFloat(player->entity.velh) + player->entity.velh)) - 1 + .5f;
        else if (player->entity.velh < 0)
            player->entity.position.x = (int) (player->entity.position.x + (CUBE_SIZE * .5 * SignFloat(player->entity.velh) + player->entity.velh)) + 1 + .5f;

        player->entity.velh = 0;
    }
    else
    {
        player->entity.position.x += player->entity.velh;
    }

    //Vertical
    if (map[(int) (player->entity.position.z + (CUBE_SIZE * .5 * SignFloat(player->entity.velv) + player->entity.velv))][(int) (player->entity.position.x - ALMOST_HALF)] == 'W' ||
        map[(int) (player->entity.position.z + (CUBE_SIZE * .5 * SignFloat(player->entity.velv) + player->entity.velv))][(int) (player->entity.position.x + ALMOST_HALF)] == 'W' ||
        map[(int) (player->entity.position.z + (CUBE_SIZE * .5 * SignFloat(player->entity.velv) + player->entity.velv))][(int) (player->entity.position.x - ALMOST_HALF)] == 'H' ||
        map[(int) (player->entity.position.z + (CUBE_SIZE * .5 * SignFloat(player->entity.velv) + player->entity.velv))][(int) (player->entity.position.x + ALMOST_HALF)] == 'H')
    {
        //Ajustando a posicao
        if (player->entity.velv > 0)
            player->entity.position.z = (int) (player->entity.position.z + (CUBE_SIZE * .5 * SignFloat(player->entity.velv) + player->entity.velv)) - 1 + .5f;
        else if (player->entity.velv < 0)
            player->entity.position.z = (int) (player->entity.position.z + (CUBE_SIZE * .5 * SignFloat(player->entity.velv) + player->entity.velv)) + 1 + .5f;

        player->entity.velv = 0;
    }
    else
    {
        player->entity.position.z += player->entity.velv;
    }

    //Atualizando a hitbox
    player->entity.hitbox = (BoundingBox){(Vector3){player->entity.position.x - player->entity.size * .5f,
                                                    player->entity.position.y - player->entity.size * .5f,
                                                    player->entity.position.z - player->entity.size * .5f},
                                          (Vector3){player->entity.position.x + player->entity.size * .5f,
                                                    player->entity.position.y + player->entity.size * .5f,
                                                    player->entity.position.z + player->entity.size * .5f}};
}