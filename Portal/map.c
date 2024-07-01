#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "raylib.h"
#include "structs.h"
#include "player.h"
#include "portal.h"
#include "models.h"

//Funcao que renderiza o mapa
void RenderMap(char map[ROWS][COLS], Models *wall_models, Models *spike_models, Models *exit_models)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            switch (map[i][j])
            {
                //Renderizando a parede
                case 'W':
                {
                    /*//Desenhando o cubo
                    DrawCube((Vector3){(j * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5, Y_HEIGHT, (i * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5}, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, BROWN);
                    //Desenhando o contorno
                    DrawCubeWires((Vector3){(j * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5, Y_HEIGHT, (i * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5}, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, GREEN);*/

                    DrawModels((Vector3){(j * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5, Y_HEIGHT, (i * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5}, wall_models);
                    break;
                }
                case 'H':
                {
                    DrawModels((Vector3){(j * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5, Y_HEIGHT, (i * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5}, spike_models);
                    break;
                }
                case 'S':
                {
                    DrawModels((Vector3){(j * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5, Y_HEIGHT, (i * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5}, exit_models);
                    break;;
                }
            }
        }
    }
}

void FirstReadMap(char map[ROWS][COLS], int *rendered, Enemy array_enemys[MAX_ENEMYS], int *qtd_enemys_max, Player *player, Lever levers[MAX_LEVERS], int *qtd_levers_max,
                  Model *enemy_model, int *fixed_enemy, Model *lever_model, int *fixed_lever, int *max_values, int *min_values)
{
    int qtd_enemys = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            switch (map[i][j])
            {
                //Renderizando a parede
                case 'M':
                {
                    // Na primeira renderizacao, cria monstros e coloca-os no array correspondente
                    Enemy enemy = {0};
                    
                    enemy.entity.position.x = j * CUBE_SIZE + CUBE_SIZE * .5f;
                    enemy.entity.position.y = Y_HEIGHT;
                    enemy.entity.position.z = i * CUBE_SIZE + CUBE_SIZE * .5f;
                    /*enemy.entity.mascara.x = -5000;
                    enemy.entity.mascara.y = -5000;
                    enemy.entity.mascara.width = 20;
                    enemy.entity.mascara.height = 20;
                    enemy.entity.sprite.textura = inimigos_texture;
                    enemy.entity.sprite.crop = (Rectangle) {0, 0, 20, 20};
                    enemy.entity.sprite.escala = 1;
                    enemy.entity.sprite.frame_vel = 2;*/
                    enemy.walking = 0;
                    enemy.placed = 1;
                    enemy.entity.speed = 1.0f;
                    enemy.entity.size = 1.0f;
                    enemy.entity.velh = 0.0f;
                    enemy.entity.velv = 0.0f;
                    enemy.inicial_position = enemy.entity.position;
                    
                    enemy.entity.hitbox = (BoundingBox){(Vector3){enemy.entity.position.x - enemy.entity.size * ENEMY_HITBOX_NUMBER,
                                                                  enemy.entity.position.y - enemy.entity.size * ENEMY_HITBOX_NUMBER,
                                                                  enemy.entity.position.z - enemy.entity.size * ENEMY_HITBOX_NUMBER}, 
                                                        (Vector3){enemy.entity.position.x + enemy.entity.size * ENEMY_HITBOX_NUMBER,
                                                                  enemy.entity.position.y + enemy.entity.size * ENEMY_HITBOX_NUMBER,
                                                                  enemy.entity.position.z + enemy.entity.size * ENEMY_HITBOX_NUMBER}};

                    //Passando o modelo
                    enemy.entity.models = NewModels(enemy_model, 'Y', WHITE, 2, 3, fixed_enemy);


                    array_enemys[qtd_enemys] = enemy;

                    qtd_enemys++;
                    *qtd_enemys_max = qtd_enemys;
                        //DrawRectangle(j * TAMANHO, i * TAMANHO, TAMANHO, TAMANHO, RED);
                    //Voltando para posicao original
                    /*if (*reinicia)
                    {
                        array_inimigos[qtd_inimigos].entidade.x = j * TAMANHO;
                        array_inimigos[qtd_inimigos].entidade.y = i * TAMANHO;
                        array_inimigos[qtd_inimigos].entidade.mascara.x = -5000;
                        array_inimigos[qtd_inimigos].entidade.mascara.y = -5000;
                        qtd_inimigos++;
                    }*/
                    break;
                }
                case 'J':
                {
                    player->entity.position.x = j * CUBE_SIZE + CUBE_SIZE * .5f;
                    player->entity.position.z = i * CUBE_SIZE + CUBE_SIZE * .5f;
                    player->entity.position.y = 0.0f;

                    player->inicial_position = player->entity.position;
                    break;
                }
                case 'A':
                {
                    levers[*qtd_levers_max].entity.size = CUBE_SIZE;
                    levers[*qtd_levers_max].entity.position.x = j * CUBE_SIZE + CUBE_SIZE * .5f;
                    levers[*qtd_levers_max].entity.position.z = i * CUBE_SIZE + CUBE_SIZE * .5f;
                    levers[*qtd_levers_max].entity.position.y = 0;

                    levers[*qtd_levers_max].entity.hitbox = (BoundingBox){(Vector3){levers[*qtd_levers_max].entity.position.x - CUBE_SIZE * .5f,
                                                                                    levers[*qtd_levers_max].entity.position.y - CUBE_SIZE * .5f,
                                                                                    levers[*qtd_levers_max].entity.position.z - CUBE_SIZE * .5f}, 
                                                                          (Vector3){levers[*qtd_levers_max].entity.position.x + CUBE_SIZE * .5f,
                                                                                    levers[*qtd_levers_max].entity.position.y + CUBE_SIZE * .5f,
                                                                                    levers[*qtd_levers_max].entity.position.z + CUBE_SIZE * .5f}};

                    levers[*qtd_levers_max].used = 0;
                    levers[*qtd_levers_max].placed = 1;
                    levers[*qtd_levers_max].entity.models = NewModels(lever_model, 'Y', WHITE, 0, 2, fixed_lever);
                    levers[*qtd_levers_max].entity.models.angle = 90;

                    *qtd_levers_max += 1;
                    break;
                }
                case 'W':
                {
                    //Pegando os maximos e minimos
                    //X
                    if (j > max_values[0])
                    {
                        max_values[0] = j;
                    }

                    if (j < min_values[0])
                    {
                        min_values[0] = j;
                    }

                    //Z
                    if (i > max_values[1])
                    {
                        max_values[1] = i;
                    }

                    if (i < min_values[1])
                    {
                        min_values[1] = i;
                    }
                    break;
                }
            }
        }
    }

    *rendered = 1;
}

void ResetHit(Player *player, Portal portals[2], Enemy enemys[MAX_ENEMYS], int qtd_inimigos)
{
    //Resetando a posicao do player
    player->entity.position = player->inicial_position;

    //Resetando os portais
    Models temp_1 = portals[0].entity.models;
    Models temp_2 = portals[1].entity.models;
    portals[0] = NewPortal(portals[0].color);
    portals[1] = NewPortal(portals[1].color);

    portals[0].entity.models = temp_1;
    portals[1].entity.models = temp_2;

    //Resetando os inimigos
    for (int i = 0; i < qtd_inimigos; i++)
    {
        enemys[i].entity.position = enemys[i].inicial_position;
    }
}

//num_mapa eh o numero do mapa que tu quer carregar/salvar
void LoadMap(int *number, char (*map)[ROWS][COLS])
{
    //Pegando o nome do mapa que queremos abrir
    char number_string[3] = {0};
    sprintf(number_string, "%d", *number);

    char map_dir[16] = "maps/map";
    char type[5] = ".txt";


    //Juntando tudo
    strcat(map_dir, number_string);
    strcat(map_dir, type);

    FILE *file = NULL;

    //Abrindo o arquivo
    file = fopen(map_dir, "r");

    if (file == NULL)
    {
        if (*number != 1)
        {
            *number = 101;
        }
        //printf("\nNao foi possivel abrir o arquivo :(");
    }
    else
    {
        //Abriu o arquivo
        //Vamos salvar
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS + 1; j++)
            {
                //Passando o char do mapa para uma temporavel
                char temp = fgetc(file);

                //Peneirando o \n e o \0
                if (temp != '\n')
                    (*map)[i][j] = temp;
            }
        }
        printf("\nCarregou");
        fflush(file);
    }
}


void DrawFloor(int *max_values, int *min_values)
{
    Vector2 size = {max_values[0] - min_values[0], max_values[1] - min_values[1]};

    Vector3 position = {min_values[0] + .5f + size.x * .5, 0.0f, min_values[1] + .5f + size.y * .5};

    DrawPlane(position, size, FLOOR_COLOR);
}