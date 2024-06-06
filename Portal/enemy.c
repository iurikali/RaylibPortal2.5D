#include "enemy.h"
#include "models.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


// Funcao que verifica se a gente pode mover
int ShouldMove(Entity entity, char map[ROWS][COLS], int holes)
{
    int go = 1;

    // Verficando se tem parede
    int horizontal = (int)(entity.position.x + entity.velh);
    int vertical = (int)(entity.position.z + entity.velv);

    // Verficando se pode mover no eixo X
    if (map[(int) entity.position.z][horizontal] == 'W' || map[vertical][horizontal] == 'W')
    {
        go = 0;
    }

    // Verificando se pode mover no eixo Y
    else if (map[vertical][(int)entity.position.x] == 'W')
    {
        go = 0;
    }

    // Verificacao do burado
    if (holes)
    {
        if (map[(int)entity.position.z][horizontal] == 'H' || map[vertical][horizontal] == 'H' || map[vertical][(int)entity.position.x] == 'H')
        {
            go = 0;
        }
    }

    return go;
}

void MoveIni(Enemy *enemy, char map[ROWS][COLS], Player *player, int *rendered, int pause, int *dead, int *reset)
{
    if (!pause)
    {
        int random;

        // Se a posicao tiver um inimigo e ele não estiver caminhando
        if (enemy->placed && enemy->walking == 0)
        {
            random = rand() % 4;
            switch (random)
            {
            case 0:
                enemy->entity.velh = -enemy->entity.speed;
                enemy->entity.velv = 0.0f;
                enemy->entity.models.angle = 270;
                break;
            case 1:
                enemy->entity.velh = enemy->entity.speed;
                enemy->entity.velv = 0.0f;
                enemy->entity.models.angle = 90;
                break;
            case 2:
                enemy->entity.velh = 0.0f;
                enemy->entity.velv = -enemy->entity.speed;
                enemy->entity.models.angle = 180;
                break;
            case 3:
                enemy->entity.velh = 0.0f;
                enemy->entity.velv = enemy->entity.speed;
                enemy->entity.models.angle = 0;
                break;

            default:
                enemy->entity.velh = 0.0f;
                enemy->entity.velv = 0.0f;
                enemy->entity.models.angle = 0;
                break;
            }
            enemy->walking = 50;
        }
        if (ShouldMove(enemy->entity, map, 1))
        {
            if (enemy->walking % 20 == 0)
            {
                enemy->entity.position.x = enemy->entity.velh + enemy->entity.position.x;

                enemy->entity.position.z = enemy->entity.velv + enemy->entity.position.z;

                // Atualizando a mascara
                /*enemy->entity.mascara.x = inimigo->entidade.x;
                inimigo->entidade.mascara.y = inimigo->entidade.y;*/
                enemy->entity.hitbox = (BoundingBox){(Vector3){enemy->entity.position.x - enemy->entity.size * ENEMY_HITBOX_NUMBER,
                                                              enemy->entity.position.y - enemy->entity.size * ENEMY_HITBOX_NUMBER,
                                                              enemy->entity.position.z - enemy->entity.size * ENEMY_HITBOX_NUMBER}, 
                                                    (Vector3){enemy->entity.position.x + enemy->entity.size * ENEMY_HITBOX_NUMBER,
                                                              enemy->entity.position.y + enemy->entity.size * ENEMY_HITBOX_NUMBER,
                                                              enemy->entity.position.z + enemy->entity.size * ENEMY_HITBOX_NUMBER}};
            }

            enemy->walking -= 1;
        }
        else
        {
            enemy->walking = 0;
        }

        // Verficando a colisão com o player
        if (CheckCollisionBoxes(enemy->entity.hitbox, player->entity.hitbox) && *rendered && !*dead && !*reset)
        {
            player->life -= 1;
            *reset = 1;
            if (player->life < 0)
                *dead = 1;
            printf("\nColidi");
        }
    }

    // Para o inimigo que fica preso no canto
    if (enemy->entity.position.x != 0)
    {
        //sprite_desenha_pro(&enemy->entidade.sprite, inimigo->entidade.x + 10, inimigo->entidade.y + 10, WHITE, pause);
        /*DrawCube(enemy->entity.position, enemy->entity.size, enemy->entity.size, enemy->entity.size, RED);
        DrawCubeWires(enemy->entity.position, enemy->entity.size, enemy->entity.size, enemy->entity.size, BLUE);
        printf("\nJ");*/
        DrawModels(enemy->entity.position, &(enemy->entity.models));
    }
}

void RenderEnemys(Enemy enemys[MAX_ENEMYS], char map[ROWS][COLS], Player *player, int *rendered, int qtd_enemys_max, int pause, int *dead, int *reset)
{
    int i = 0;
    for (i = 0; i < qtd_enemys_max; i++)
    {        
        MoveIni(&enemys[i], map, player, rendered, pause, dead, reset);
    }
}