#include "structs.h"
#include "player.h"
#include "defines.h"
#include "mathe.h"
#include <stdio.h>

Player NewPlayer()
{
    Player player = {0};
    player.position = (Vector3) {3.0f, 0.0f, 7.0f};
    player.hitbox = (Vector3) {1.0f, 1.0f, 1.0f};
    player.speed = .1f;
    player.velh = 0;
    player.velv = 0;


    return player;
}




void PlayerUpdate(Player *player)
{
    //Fazendo a verificacao das teclas para o player andar
    int right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
    int left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    int up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
    int down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);


    player->velh = (right - left) * player->speed;
    player->velv = (down - up) * player->speed;

}




void RenderPlayer(Player player)
{   
    //Desenhando inicialmente um cubo para representar o player
    DrawCube(player.position, player.hitbox.x, player.hitbox.y, player.hitbox.z, RED);

    //Desenhando as bordas do cubo
    DrawCubeWires(player.position, player.hitbox.x, player.hitbox.y, player.hitbox.z, BLUE);
}

void CheckingCollisionWall(Player *player, char map[ROWS][COLS])
{
    printf("\n%f", player->position.x + (CUBE_SIZE * .5 * SignFloat(player->velh) + player->velh));
    
    //Horizontal
    if (map[(int) player->position.z][(int) (player->position.x + (CUBE_SIZE * .5 * SignFloat(player->velh) + player->velh))] == 'W')
    {
        //Ajustando a posicao
        if (player->velh > 0)
            player->position.x = (int) (player->position.x + (CUBE_SIZE * .5 * SignFloat(player->velh) + player->velh)) - 1 + .5f;
        else if (player->velh < 0)
            player->position.x = (int) (player->position.x + (CUBE_SIZE * .5 * SignFloat(player->velh) + player->velh)) + 1 + .5f;

        player->velh = 0;
    }
    else
    {
        player->position.x += player->velh;
    }

    //Vertical
    if (map[(int) (player->position.z + (CUBE_SIZE * .5 * SignFloat(player->velv) + player->velv))][(int) (player->position.x)] == 'W')
    {
        //Ajustando a posicao
        if (player->velv > 0)
            player->position.z = (int) (player->position.z + (CUBE_SIZE * .5 * SignFloat(player->velv) + player->velv)) - 1 + .5f;
        else if (player->velv < 0)
            player->position.z = (int) (player->position.z + (CUBE_SIZE * .5 * SignFloat(player->velv) + player->velv)) + 1 + .5f;

        player->velv = 0;
    }
    else
    {
        player->position.z += player->velv;
    }
}