#include "lever.h"
#include "defines.h"
#include "structs.h"
#include "models.h"
#include <stdio.h>

void LeverUpdate(Lever levers[MAX_LEVERS], Player *player, char (*map)[ROWS][COLS], int *qtd_levers, int qtd_levers_max, Sound *sfx_active)
{
    int i = 0;
    // Apertando para ativar a alavanca
    if (IsKeyPressed(KEY_E) && ((*map)[(int)player->entity.position.z][(int)player->entity.position.x] == 'A' ||
                                (*map)[(int)player->entity.position.z][(int)(player->entity.position.x + CUBE_SIZE)] == 'A' ||
                                (*map)[(int)(player->entity.position.z + CUBE_SIZE)][(int)(player->entity.position.x + CUBE_SIZE)] == 'A' ||
                                (*map)[(int)(player->entity.position.z + CUBE_SIZE)][(int)player->entity.position.x] == 'A'))
    {
        for (i = 0; i < qtd_levers_max; i++)
        {

            if ((CheckCollisionBoxes(player->entity.hitbox, levers[i].entity.hitbox)) && levers[i].used == 0)
            {
                levers[i].used = 1;
                levers[i].entity.models.frame_index = levers[i].used;
                //levers[i].sprite.frame_atual = 1;
                (*qtd_levers)--;
                //(*mapa)[player->entidade.y / TAMANHO][player->entidade.x / TAMANHO] = 'U';
                PlaySound(*sfx_active);
            }

            //printf("%d", alavancas[i].x);
        }
    }
}

int ExitUpdate(Lever levers[MAX_LEVERS], int qtd_levers_max, Sound *sfx_exit)
{
    int i = 0, closed = 1;
    for (i = 0; i < qtd_levers_max; i++)
    {
        if (levers[i].placed == 1)
        {
            closed = levers[i].used && closed;
        }
        //sprite_desenha_pro(&alavancas[i].sprite, alavancas[i].x + 10, alavancas[i].y + 10, WHITE, pause);
        //Desenhando a alavanca
        /*if (!levers[i].used)
        {
            DrawCube(levers[i].entity.position, levers[i].entity.size, levers[i].entity.size, levers[i].entity.size, YELLOW);
        }
        else
        {
            DrawCube(levers[i].entity.position, levers[i].entity.size, levers[i].entity.size, levers[i].entity.size, GREEN);
        }*/
        DrawModels(levers[i].entity.position, &(levers[i].entity.models));
        //DrawCubeWires(levers[i].entity.position, levers[i].entity.size, levers[i].entity.size, levers[i].entity.size, BLUE);
    }
    if(!closed)
    {
        PlaySound(*sfx_exit);
    }
    return closed;
}


void leaving(Player *player, Transition *tran, char map[ROWS][COLS])
{
    //Verificando se o player tah colidindo com a saida
    if ((map[(int)player->entity.position.z][(int)player->entity.position.x] == 'S')&& !tran->activated)
    {
        //Chamando a transicao
        tran->type = 1;
        tran->activated = 1;
    }
}