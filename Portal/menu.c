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


void InicialMenu(Rectangle a, Rectangle b, Rectangle c, int *menu, Font f1, Texture2D background[3], int *first_time, int *img, int *number_map,
                  char (*map)[ROWS][COLS], int *load, Player *player, Lever levers[MAX_LEVERS], Enemy enemys[MAX_ENEMYS], int *exit_opened, int *turn,
                  Portal portals[2], int *there_is_file, int *there_is_map, int *load_map_menu)
{
    // gerando as variaveis para as finalidades do menu
    Vector2 /*vect = {c.x - 40, c.y + 110}, */va = {a.x + 87, a.y + 15}, vb = {b.x + 60, b.y + 15}, vc = {c.x + 69, c.y + 15};

    if (*first_time)
    {
        // gerando uma semente aleat�ria para mudan�a de imagem do background do menu
        srand(time(NULL));

        *img = MIN_IMG + (rand() % (MAX_IMG - MIN_IMG + 1));

        *there_is_file = ThereIsFile("dados_salvos.bin");

        *first_time = 0;
    }

    //Desenhando as opções
    DrawTexture(background[*img - 1], 0, 0, WHITE);

    if (*there_is_map)
    {
        DrawRectangleRec(a, GRAY);
        DrawRectangleLinesEx(a, 2, BLACK);
        DrawTextEx(f1, "Novo Jogo", va, 17, 2, BLACK);
    }
    else
    {
        DrawRectangleRec(a, GRAY_ALPHA);
        DrawRectangleLinesEx(a, 2, BLACK_ALPHA);
        DrawTextEx(f1, "Novo Jogo", va, 17, 2, BLACK_ALPHA);
    }


    if (*there_is_file)
    {
        DrawRectangleRec(b, GRAY);
        DrawRectangleLinesEx(b, 2, BLACK);
        DrawTextEx(f1, "Carregar Jogo", vb, 17, 2, BLACK);
    }
    else
    {
        DrawRectangleRec(b, GRAY_ALPHA);
        DrawRectangleLinesEx(b, 2, BLACK_ALPHA);
        DrawTextEx(f1, "Carregar Jogo", vb, 17, 2, BLACK_ALPHA);
    }

    DrawRectangleRec(c, RED);
    DrawRectangleLinesEx(c, 2, BLACK);
    DrawTextEx(f1, "Sair do Jogo", vc, 17, 2, BLACK);

    //DrawTextEx(f1, "A game by Alef, Abyner & Iuri", vect, 17, 2, WHITE);

    //Novo jogo
    if (CheckCollisionPointRec(GetMousePosition(), a))
    {
        if (*there_is_map)
        {
            DrawRectangleLinesEx(a, 4, WHITE);
            DrawTextEx(f1, "Novo Jogo", va, 17, 2, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                // Logica para iniciar o jogo
                *number_map = 1;
                *load = 0;
                *menu = 0;
                LoadMap(*number_map, map);
                *first_time = 1;
                *load_map_menu = 1;
            }
        }
    }
    //Carregar jogo
    else if (CheckCollisionPointRec(GetMousePosition(), b))
    {
        if (*there_is_file)
        {
            DrawRectangleLinesEx(b, 4, WHITE);
            DrawTextEx(f1, "Carregar Jogo", vb, 17, 2, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                //carregarJogo(mapa, player, alavancas, inimigos, saida_aberta, num_mapa, vez, portais);
                LoadMap(*number_map, map);
                *load = 1;
                *menu = 0;
                *first_time = 1;
            }
        }
    }
    //Sair do jogo
    else if (CheckCollisionPointRec(GetMousePosition(), c))
    {
        DrawRectangleLinesEx(c, 4, WHITE);
        DrawTextEx(f1, "Sair do Jogo", vc, 17, 2, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            CloseWindow();
        }
    }
}

int LoadGame(char (*map)[ROWS][COLS], Player *player, Lever levers[MAX_LEVERS], Enemy enemys[MAX_ENEMYS], int *exit_opened, int *level, int *turn,
                 Portal portals[2])
{
    FILE *file;
    int read, qtd_levers = 0, qtd_enemys = 0, x_levers;
    int i = 0, j = 0;

    file = fopen("dados_salvos.bin", "r");

    if (file == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 0;
    }
    else
    {
        // Carregar fase e chamar a funcao correspondente
        fread(level, sizeof(int), 1, file);
        //printf("\nfase: %d", *fase);

        // carrega_mapa(fase, mapa);

        // Vidas
        fread(&player->life, sizeof(int), 1, file);
        //printf("\nvidas: %d", player->vida);

        // Carregar player e coloca-lo no mapa
        fread(&player->entity.position, sizeof(Vector3), 1, file);
        //fread(&player->entidade.y, sizeof(int), 1, arquivo);
        //printf("\npx: %d", player->entidade.x);
        //printf("\npy: %d", player->entidade.y);
        //printf("\nD");

        // Estado da saida
        fread(exit_opened, sizeof(int), 1, file);
        //printf("\nD");
        //printf("\nsaida: %d", *saida_aberta);

        // Inimigos
        fread(&qtd_enemys, sizeof(int), 1, file);
        for (i = 0; i < qtd_enemys; i++)
        {
            //fread(&enemys[i], sizeof(Enemy), 1, file);
            fread(&enemys[i].entity.position.x, sizeof(float), 1, file);
            fread(&enemys[i].entity.position.y, sizeof(float), 1, file);
            fread(&enemys[i].entity.position.z, sizeof(float), 1, file);
            //fread(&inimigos[i].entidade.y, sizeof(int), 1, arquivo);
            //printf("\ninix: %d", inimigos[i].entidade.x);
            //printf("\niniy: %d", inimigos[i].entidade.y);
        }

        // Carregar alavancas e coloca-las no mapa
        fread(&qtd_levers, sizeof(int), 1, file);
        for (i = 0; i < qtd_levers; i++)
        {
            fread(&levers[i].used, sizeof(int), 1, file);
            //printf("\nalaa: %d", alavancas[i].ativa);
        }

        //Carregando os portais
        fread(turn, sizeof(int), 1, file);
        for (i = 0; i < 2; i++)
        {
            fread(&portals[i].entity.position, sizeof(Vector3), 1, file);
            //fread(&portals[i].entidade.y, sizeof(int), 1, arquivo);
            fread(&portals[i].placed, sizeof(int), 1, file);
        }


        // Se ocorreu algum erro em alguma das leituras
        if (ferror(file))
        {
            printf("Ocorreu um erro durante a leitura do arquivo salvo");
            fclose(file);
            return 0;
        }
        printf("\nCarregou");
        fflush(file);
    }
    fclose(file);
    return 1;
}

int SaveGame(Player player, Enemy enemys[MAX_ENEMYS], Lever levers[MAX_LEVERS], int level, int exit_opened, int turn, Portal portals[2])
{
    int qtd_enemys = 0, qtd_levers = 0, i = 0;
    FILE *file;

    // Estrutura do arquivo binario

    // int fase
    // int vidas
    // Vector3 player position
    // estado da saida
    // int quantidade dos inimigos
    // loop quantidade inimigos {
    //      Vector3 inimigo position
    // }

    // int quantidade alavancas
    // loop quantidade alavancas {
    //      int estado da alavanca
    // }
    //int vez do portal
    //Vector3 portal 0 position
    //int portal 0 colocado
    //Vector3 portal 1 position
    //int portal 1 colocado


    file = fopen("dados_salvos.bin", "w");

    if (file == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 0;
    }
    else
    {
        // Fase
        fwrite(&level, sizeof(int), 1, file);

        // Vidas
        fwrite(&player.life, sizeof(int), 1, file);

        // Player
        fwrite(&player.entity.position, sizeof(Vector3), 1, file);
        //fwrite(&player.entidade.y, sizeof(int), 1, arquivo);

        // Saida
        fwrite(&exit_opened, sizeof(int), 1, file);

        // Inimigos

        // Contabiliza quantos inimigos tem
        for (i = 0; i < MAX_ENEMYS; i++)
        {
            if (enemys[i].placed == 1)
            {
                qtd_enemys++;
            }
        }

        fwrite(&qtd_enemys, sizeof(int), 1, file);

        for (i = 0; i < MAX_ENEMYS; i++)
        {
            if (enemys[i].placed == 1)
            {
                //fwrite(&enemys[i], sizeof(Enemy), 1, file);
                fwrite(&enemys[i].entity.position.x, sizeof(float), 1, file);
                fwrite(&enemys[i].entity.position.y, sizeof(float), 1, file);
                fwrite(&enemys[i].entity.position.z, sizeof(float), 1, file);
                //fwrite(&eme[i].entidade.y, sizeof(int), 1, arquivo);
            }
        }

        // Ativacao das alavancas

        // Contabiliza quantas alavancas tem
        for (i = 0; i < MAX_LEVERS; i++)
        {
            if (levers[i].placed == 1)
            {
                qtd_levers++;
            }
        }

        fwrite(&qtd_levers, sizeof(int), 1, file);

        for (i = 0; i < MAX_LEVERS; i++)
        {
            if (levers[i].placed == 1)
            {
                fwrite(&levers[i].used, sizeof(int), 1, file);
            }
        }
        //Parte dos portais
        fwrite(&turn, sizeof(int), 1, file);
        for (i = 0; i < 2; i++)
        {
            fwrite(&portals[i].entity.position, sizeof(Vector3), 1, file);
            //fwrite(&portais[i].entidade.y, sizeof(int), 1, arquivo);
            fwrite(&portals[i].placed, sizeof(int), 1, file);
        }

        printf("\nSalvou");
    }
    fflush(file);
    fclose(file);
    return 1;
}

void MenuPause(Rectangle a, Rectangle b, Rectangle c, Rectangle d, Rectangle e, int *pause, Font fp, int *menu, int *load,
                Player *player, Enemy enemys[MAX_ENEMYS], Lever levers[MAX_LEVERS], int *level, int *exit_opened, char (*map)[ROWS][COLS], int *rendered,
                int *qtd_levers, int *qtd_enemys, int *turn, Portal portals[2], int *saved, int *there_is_file)
{
    Vector2 vect = {357, 80}, va = {a.x + 87, a.y + 15}, vb = {b.x + 60, b.y + 15}, vc = {c.x + 75, c.y + 15}, vd = {d.x + 58, d.y + 15}, ve = {e.x + 70, e.y + 15};

    //Desenhando o fundo
    DrawRectangle(-1, -1, SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1, (Color){0, 0, 0, 150});

    // Desenhando
    DrawTextEx(fp, "GAME PAUSED", vect, 60, 5, LIGHTGRAY);


    DrawRectangleRec(a, PURPLE);
    DrawRectangleLinesEx(a, 4, BLACK);
    DrawTextEx(fp, "Continuar", va, 17, 2, BLACK);

    if (*there_is_file)
    {
        DrawRectangleRec(b, PURPLE);
        DrawRectangleLinesEx(b, 4, BLACK);
        DrawTextEx(fp, "Carregar Jogo", vb, 17, 2, BLACK);
    }
    else
    {
        DrawRectangleRec(b, PURPLE_ALPHA);
        DrawRectangleLinesEx(b, 4, BLACK_ALPHA);
        DrawTextEx(fp, "Carregar Jogo", vb, 17, 2, BLACK_ALPHA);
    }


    //Desenhando o salvar apenas se ainda não salvamos o jogo
    if (!*saved)
    {
        DrawRectangleRec(c, PURPLE);
        DrawRectangleLinesEx(c, 4, BLACK);
        DrawTextEx(fp, "Salvar Jogo", vc, 17, 2, BLACK);
    }
    else
    {
        DrawRectangleRec(c, PURPLE_ALPHA);
        DrawRectangleLinesEx(c, 4, BLACK_ALPHA);
        DrawTextEx(fp, "Salvar Jogo", vc, 17, 2, BLACK_ALPHA);
    }

    DrawRectangleRec(d, BLUE);
    DrawRectangleLinesEx(d, 4, BLACK);
    DrawTextEx(fp, "Menu Principal", vd, 17, 2, BLACK);

    DrawRectangleRec(e, RED);
    DrawRectangleLinesEx(e, 4, BLACK);
    DrawTextEx(fp, "Sair do Jogo", ve, 17, 2, BLACK);

    //Verificando se apertou os botões

    //Continuar
    if (CheckCollisionPointRec(GetMousePosition(), a))
    {
        DrawRectangleLinesEx(a, 4, WHITE);
        DrawTextEx(fp, "Continuar", va, 17, 2, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            *pause = 0;
        }
    }
    //Carregar jogo
    else if (CheckCollisionPointRec(GetMousePosition(), b))
    {
        if (*there_is_file)
        {
            DrawRectangleLinesEx(b, 4, WHITE);
            DrawTextEx(fp, "Carregar Jogo", vb, 17, 2, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                /*LoadMap(*level, map);
                LoadGame(map, player, levers, enemys, exit_opened, level, turn, portals);
                *load = 1;
                *rendered = 0;
                *qtd_levers = 0;
                *qtd_enemys = 0;
                *pause = 0;*/
               *load = 1;
            }
        }
    }
    //Salvar jogo
    else if (CheckCollisionPointRec(GetMousePosition(), c))
    {
        if (!*saved)
        {
            DrawRectangleLinesEx(c, 4, WHITE);
            DrawTextEx(fp, "Salvar Jogo", vc, 17, 2, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                SaveGame(*player, enemys, levers, *level, *exit_opened, *turn, portals);
                *there_is_file = 1;
                *saved = 1;
            }
        }
    }
    //Menu principal
    else if (CheckCollisionPointRec(GetMousePosition(), d))
    {
        DrawRectangleLinesEx(d, 4, WHITE);
        DrawTextEx(fp, "Menu Principal", vd, 17, 2, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            *menu = 1;
            *pause = 0;
        }
    }
    //Sair do jogo
    else if (CheckCollisionPointRec(GetMousePosition(), e))
    {
        DrawRectangleLinesEx(e, 4, WHITE);
        DrawTextEx(fp, "Sair do Jogo", ve, 17, 2, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            CloseWindow();
        }
    }
}
