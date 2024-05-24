#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "raylib.h"


//Funcao que renderiza o mapa
void RenderMap(char map[ROWS][COLS])
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
                    //Desenhando o cubo
                    DrawCube((Vector3){(j * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5, Y_HEIGHT, (i * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5}, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, BROWN);
                    //Desenhando o contorno
                    DrawCubeWires((Vector3){(j * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5, Y_HEIGHT, (i * (CUBE_SIZE + .0f)) + CUBE_SIZE * .5}, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, GREEN);
                    break;
                }
            }
        }
    }
}



//num_mapa eh o numero do mapa que tu quer carregar/salvar
void LoadMap(int number, char (*map)[ROWS][COLS])
{
    //Pegando o nome do mapa que queremos abrir
    char number_string[3] = {0};
    sprintf(number_string, "%d", number);

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
        printf("\nNao foi possivel abrir o arquivo :(");
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
