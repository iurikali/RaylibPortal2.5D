#include "raylib.h"
#include "defines.h"
#include "structs.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Função que verifica se existe o arquivo binario
int ThereIsFile(char dir[])
{
    int opened = 0;
    FILE *file = NULL;

    file = fopen(dir, "r");

    if (file != NULL)
    {
        opened = 1;

        fclose(file);
    }

    return opened;
}


void InicialMenu(Rectangle b, Rectangle c, int *menu, Font f1, Texture2D background[3], int *first_time, int *img,
                  char (*map)[ROWS][COLS], int *there_is_map, int *close_game)
{
    // gerando as variaveis para as finalidades do menu
    Vector2 /*vect = {c.x - 40, c.y + 110}, */vb = {b.x + 90, b.y + 15}, vc = {c.x + 69, c.y + 15};

    if (*first_time)
    {
        // gerando uma semente aleat�ria para mudan�a de imagem do background do menu
        srand(time(NULL));

        *img = MIN_IMG + (rand() % (MAX_IMG - MIN_IMG + 1));

        *first_time = 0;
    }

    //Desenhando as opções
    DrawTexture(background[*img - 1], 0, 0, WHITE);

    if (*there_is_map)
    {
        DrawRectangleRec(b, GRAY);
        DrawRectangleLinesEx(b, 2, BLACK);
        DrawTextEx(f1, "Iniciar", vb, 17, 2, BLACK);
    }
    else
    {
        DrawRectangleRec(b, GRAY_ALPHA);
        DrawRectangleLinesEx(b, 2, BLACK_ALPHA);
        DrawTextEx(f1, "Iniciar", vb, 17, 2, BLACK_ALPHA);
    }


    DrawRectangleRec(c, RED);
    DrawRectangleLinesEx(c, 2, BLACK);
    DrawTextEx(f1, "Sair do Jogo", vc, 17, 2, BLACK);

    /*DrawRectangleRec(c, RED);
    DrawRectangleLinesEx(c, 2, BLACK);
    DrawTextEx(f1, "Sair do Jogo", vc, 17, 2, BLACK);*/

    //DrawTextEx(f1, "A game by Alef, Abyner & Iuri", vect, 17, 2, WHITE);

    //Novo jogo
    if (CheckCollisionPointRec(GetMousePosition(), b))
    {
        if (*there_is_map)
        {
            DrawRectangleLinesEx(b, 4, WHITE);
            DrawTextEx(f1, "Iniciar", vb, 17, 2, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Logica para iniciar o jogo
                *menu = 0;
            }
        }
    }
    //Carregar jogo
    else if (CheckCollisionPointRec(GetMousePosition(), c))
    {
        DrawRectangleLinesEx(c, 4, WHITE);
        DrawTextEx(f1, "Sair do jogo", vc, 17, 2, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            *close_game = 1;
        }
    }
}

void MenuPause(Rectangle b, Rectangle c, int *pause, Font fp, int *close_game)
{
    Vector2 vect = {357, 80}, vb = {b.x + 87, b.y + 15}, vc = {c.x + 70, c.y + 15};

    //Desenhando o fundo
    DrawRectangle(-1, -1, SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1, (Color){0, 0, 0, 150});

    // Desenhando
    DrawTextEx(fp, "GAME PAUSED", vect, 60, 5, LIGHTGRAY);

    //Continuar
    DrawRectangleRec(b, PURPLE);
    DrawRectangleLinesEx(b, 4, BLACK);
    DrawTextEx(fp, "Continuar", vb, 17, 2, BLACK);

    //Sair
    DrawRectangleRec(c, RED);
    DrawRectangleLinesEx(c, 4, BLACK);
    DrawTextEx(fp, "Sair do Jogo", vc, 17, 2, BLACK);

    //Verificando se apertou os botões

    //Continuar
    if (CheckCollisionPointRec(GetMousePosition(), b))
    {
        DrawRectangleLinesEx(b, 4, WHITE);
        DrawTextEx(fp, "Continuar", vb, 17, 2, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            *pause = 0;
        }
    }
    //Sair do jogo
    else if (CheckCollisionPointRec(GetMousePosition(), c))
    {
        DrawRectangleLinesEx(c, 4, WHITE);
        DrawTextEx(fp, "Sair do Jogo", vc, 17, 2, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            *close_game = 1;
        }
    }
}

void EndGame(Rectangle b, int *menu, Font f1, int *won, int *dead, Font f2, Texture2D background_over, Texture2D background_win, Music *music, Music *music_win)
{
    // gerando as variaveis para as finalidades do menu
    Vector2 vb = {b.x + 69, b.y + 15};
    Vector2 vet = {320, 100}, vet2 = {238, 100};

    //Desenhando o fundo preto
    DrawRectangle(-1, -1, SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1, BLACK);

    PlayMusicStream(*music_win);
    StopMusicStream(*music);

    //Aqui tu coloca o texto de vitória
    if (*won)
    {
        DrawTexture(background_win, 0, 0, WHITE);
        DrawTextEx(f2, "VOCE GANHOU!!!", vet2, 90, 2, LIGHTGRAY);
        //DrawTextEx(f1, "Voce pode experimentar criar seu proprio mapa na pasta Editaveis", vect2, 17, 2, WHITE);
    }
    else
    {
        DrawTexture(background_over, 0, 0, WHITE);
        DrawTextEx(f2, "GAME OVER", vet, 90, 5, LIGHTGRAY);
        //DrawTextEx(f1, "Que pena...", vect, 17, 2, WHITE);
    }


    //Desenhando as opções

    DrawRectangleRec(b, VIOLET);
    DrawRectangleLinesEx(b, 2, BLACK);
    DrawTextEx(f1, "Menu Inicial", vb, 17, 2, BLACK);

    //Novo jogo
    //Aqui t
    //Menu inicial
    if (CheckCollisionPointRec(GetMousePosition(), b))
    {
        DrawRectangleLinesEx(b, 4, WHITE);
        DrawTextEx(f1, "Menu Inicial", vb, 17, 2, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            StopMusicStream(*music_win);
            PlayMusicStream(*music);
            *won = 0;
            *dead = 0;
            *menu = 1;
        }
    }
}