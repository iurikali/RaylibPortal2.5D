#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "mathe.h"
#include "camera.h"
#include "structs.h"
#include "player.h"
#include "map.h"
#include "defines.h"
#include "portal.h"
#include "enemy.h"
#include "lever.h"
#include "models.h"
#include "transition.h"
#include "menu.h"

int main()
{
    char map[ROWS][COLS] = {0};

    int number_map = 1;

    LoadMap(number_map, &map);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60);

    //Iniciando a camera 
    Camera3D cam = NewCamera();

    //Iniciando o player
    Model player_model_array[3] = {0};
    Player player = NewPlayer();
    player_model_array[0] = LoadModel("resources/models/player/mage_idle_1.vox");
    player_model_array[1] = LoadModel("resources/models/player/mage_idle_2.vox");
    player_model_array[2] = LoadModel("resources/models/player/mage_idle_3.vox");
    int fixed_player = 0;
    player.entity.models = NewModels(&player_model_array[0], 'Y', WHITE, 2, 3, &fixed_player);

    //Vars da mira
    Model aim_model = LoadModel("resources/models/others/aim.vox");
    int fixed_aim = 0;
    Models aim_models = NewModels(&aim_model, 'Y', WHITE, 0, 1, &fixed_aim);
    aim_models.scale = (Vector3) {.25f, .25f, .25f};

    //Vars dos portais
    Portal portals[2] = {0};
    portals[0] = NewPortal(SKYBLUE);
    portals[1] = NewPortal(RED_PORTAL);
    int turn = 0;
    int lanched = 0;
    int used = 0;
    float theta = 0;
    int fixed_portal = 0;
    Model portal_model_array[2] = {0};
    portal_model_array[0] = LoadModel("resources/models/others/portal_1.vox");
    portal_model_array[1] = LoadModel("resources/models/others/portal_2.vox");
    portals[0].entity.models = NewModels(&portal_model_array[0], 'Y', portals[0].color, 2, 2, &fixed_portal);
    portals[1].entity.models = NewModels(&portal_model_array[0], 'Y', portals[1].color, 2, 2, &fixed_portal);
    portals[0].entity.models.scale = (Vector3) {.25f, .25f, .25f};
    portals[1].entity.models.scale = (Vector3) {.25f, .25f, .25f};

    //Vars do pause e menu
    int pause = 0;
    int rendered = 0;
    int reset = 0;
    int dead = 0;
    int menu = 1;
    int game_over = 0;
    int first_time = 1;
    int there_is_file = 0;
    int there_is_map = ThereIsFile("maps/map1.txt");
    int img = 0;
    int load = 0;
    int load_map_menu = 0;
    int saved = 0;

    Rectangle botton_play = { SCREEN_WIDTH / 2 - 150, 250, 298, 50 };//principal
    Rectangle botton_load = { SCREEN_WIDTH/ 2 - 150, 320, 298, 50 };//principal
    Rectangle botton_exit_inicial = { SCREEN_WIDTH/ 2 - 150, 390, 298, 50 };//principal
    Rectangle pause_continue = { SCREEN_WIDTH/ 2 - 150, 180, 298, 50};//pause
    Rectangle load_pause = { SCREEN_WIDTH/ 2 - 150, 250, 298, 50 };
    Rectangle save_game = { SCREEN_WIDTH/ 2 - 150, 320, 298, 50 };
    Rectangle return_menu_inic = { SCREEN_WIDTH/ 2 - 150, 460, 298, 50 };//mesmos dados do botao_sair
    Rectangle botton_exit_pause = {SCREEN_WIDTH/ 2 - 150, 390, 298, 50 };//pause

    Font fp = LoadFont("resources/fonts/VCR_OSD_MONO_1.001.ttf");

    //Carregando as imagens de fundo
    Texture2D backgrounds[3] = {0};
    backgrounds[0] = LoadTexture("resources/images/imgmenu01.png");
    backgrounds[1] = LoadTexture("resources/images/imgmenu02.png");
    backgrounds[2] = LoadTexture("resources/images/imgmenu03.png");

    //Vars dos inimigos
    Enemy enemys[MAX_ENEMYS] = {0};
    int qtd_enemys_max = 0;
    Model enemys_model_array[3] = {0};
    enemys_model_array[0] = LoadModel("resources/models/enemy/enemy_spider_1.vox");
    enemys_model_array[1] = LoadModel("resources/models/enemy/enemy_spider_2.vox");
    enemys_model_array[2] = LoadModel("resources/models/enemy/enemy_spider_3.vox");
    int fixed_enemy = 0;

    //Vars das alavancas
    int qtd_levers_max = 0;
    int qtd_levers = 0;
    Lever levers[MAX_LEVERS] = {0};
    Model levers_model_array[2] = {0};
    levers_model_array[0] = LoadModel("resources/models/others/lever_red.vox");
    levers_model_array[1] = LoadModel("resources/models/others/lever_green.vox");
    int fixed_lever = 0;
    //DisableCursor();

    //Vars da saida
    Model exit_model_array[2] = {0};
    exit_model_array[0] = LoadModel("resources/models/others/exit_closed.vox");
    exit_model_array[1] = LoadModel("resources/models/others/exit_opened.vox");
    int fixed_exit = 0;
    Models exit_models = NewModels(&exit_model_array[0], 'Y', WHITE, 0, 2, &fixed_exit);
    exit_models.scale = (Vector3) {.25f, .25f, .25f};
    int exit_opened = 0;

    //Vars das paredes
    Model wall_model = LoadModel("resources/models/others/wall.vox");
    int fixed_wall = 0;
    Models wall_models = NewModels(&wall_model, 'Y', WHITE, 0, 1, &fixed_wall);
    int max_values[2] = {0, 0}; // 0 = x e 1 = z
    int min_values[2] = {100, 100};
    wall_models.scale = (Vector3) {.25f, .25f, .25f};

    //Vars dos espinhos
    Model spike_model = LoadModel("resources/models/others/spikes.vox");
    int fixed_spike = 0;
    Models spike_models = NewModels(&spike_model, 'Y', WHITE, 0, 1, &fixed_spike);

    //Vars da transicao
    Transition tran = NewTransition(0, BLACK);

    FirstReadMap(map, &rendered, enemys, &qtd_enemys_max, &player, levers, &qtd_levers_max, &enemys_model_array[0], &fixed_enemy,
                 &levers_model_array[0], &fixed_lever, &max_values[0], &min_values[0]);

    qtd_levers = qtd_levers_max;

    SetExitKey(KEY_F12);

    while (!WindowShouldClose())
    {   
        //Parando o jogo se estivermos no menu ou pausado ou morto
        if (!menu && !pause && !dead)
        {
            //Reiniciando o jogo
            if (reset)
            {
                ResetHit(&player, portals, enemys, qtd_enemys_max);
                reset = 0;
            }
            
            if (!tran.activated)
            {
                if (IsKeyPressed(KEY_ESCAPE) && !menu && !dead)
                {
                    there_is_file = ThereIsFile("dados_salvos.bin");
                    saved = 0;
                    pause = !pause;
                }

                //Atualizando o player
                PlayerUpdate(&player);

                //Atualizando os valores da camera  
                //CameraMoviment(&cam, player.velh, player.velv);
                
                //UpdateCamera(&cam, CAMERA_FREE);

                //DisableCursor();

                CheckingCollisionWall(&player, map);

                PortalUpdate(&portals[0], &player, &turn, &lanched, map, &used, &theta, &cam);

                //Alavancas
                LeverUpdate(levers, &player, &map, &qtd_levers, qtd_levers_max);
            }
            else
            {
                TransitionUpdate(&tran);
                //Resetando as variaveis para trocar de fase
                if (tran.change_level)
                {
                    exit_opened = 0;
                    qtd_levers = 0;
                    qtd_levers_max = 0;
                    qtd_enemys_max = 0;
                    portals[0].entity.position = (Vector3) {0.0f, 0.0f, 0.0f};
                    portals[0].placed = 0;
                    portals[1].entity.position = (Vector3) {0.0f, 0.0f, 0.0f};
                    portals[1].placed = 0;
                    max_values[0] = 0;
                    max_values[1] = 0;
                    min_values[0] = 100;
                    min_values[1] = 100;

                    //Indo pro proximo mapa
                    number_map++;
                    LoadMap(number_map, &map);
                    rendered = 0;
                    FirstReadMap(map, &rendered, enemys, &qtd_enemys_max, &player, levers, &qtd_levers_max, &enemys_model_array[0], &fixed_enemy,
                                &levers_model_array[0], &fixed_lever, &max_values[0], &min_values[0]);
                    tran.change_level = 0;
                }
            }
            CameraFollowPlayer(&cam, player);
        }

        BeginDrawing();

            //ClearBackground((Color){72, 59, 58, 255});
            ClearBackground(BLACK);

            if (!menu && !dead)
            {
                //Iniciando a area 3D
                BeginMode3D(cam);


                    //Renderizando o mapa
                    RenderMap(map, &wall_models, &spike_models, &exit_models);

                    //Renderizando as alavancas
                    exit_opened = ExitUpdate(levers, qtd_levers_max);
                    exit_models.frame_index = exit_opened;
                    if (exit_opened)
                        leaving(&player, &tran, map);
                    
                    //Renderizando e fazendo a logica dos inimigos
                    RenderEnemys(enemys, map, &player, &rendered, qtd_enemys_max, pause, &dead, &reset);

                    //Desenhando os portais
                    RenderPortal(&portals[0]);

                    //Desenhando o player
                    RenderPlayer(&player);

                    //Desenhando a mira
                    RenderAim(&aim_models, theta, player);

                    /*DrawLine3D((Vector3){player.entity.position.x, player.entity.position.y + 1.0f, player.entity.position.z - ALMOST_HALF}, 
                    (Vector3){player.entity.position.x + (CUBE_SIZE * .5 * SignFloat(player.entity.velh) + player.entity.velh), player.entity.position.y + 1.0f, player.entity.position.z - ALMOST_HALF}, GREEN);

                    DrawLine3D((Vector3){player.entity.position.x, player.entity.position.y + 1.0f, player.entity.position.z + ALMOST_HALF}, 
                    (Vector3){player.entity.position.x + (CUBE_SIZE * .5 * SignFloat(player.entity.velh) + player.entity.velh), player.entity.position.y + 1.0f, player.entity.position.z + ALMOST_HALF}, GREEN);

                    DrawLine3D((Vector3){player.entity.position.x - ALMOST_HALF, player.entity.position.y + 1.0f, player.entity.position.z}, 
                    (Vector3){player.entity.position.x - ALMOST_HALF, player.entity.position.y + 1.0f, player.entity.position.z + (CUBE_SIZE * .5 * SignFloat(player.entity.velv) + player.entity.velv)}, GREEN);

                    DrawLine3D((Vector3){player.entity.position.x + ALMOST_HALF, player.entity.position.y + 1.0f, player.entity.position.z}, 
                    (Vector3){player.entity.position.x + ALMOST_HALF, player.entity.position.y + 1.0f, player.entity.position.z + (CUBE_SIZE * .5 * SignFloat(player.entity.velv) + player.entity.velv)}, GREEN);*/

                    

                    //Desenhando a grid para se orientar
                    //DrawGrid(100, 1.0f);
                    
                    DrawFloor(&max_values[0], &min_values[0]);

                EndMode3D();
            }
            //Estamos no menu
            if (menu)
            {
                    //Resetando tudo
                    exit_opened = 0;
                    qtd_levers = 0;
                    qtd_levers_max = 0;
                    qtd_enemys_max = 0;
                    portals[0].entity.position = (Vector3) {0.0f, 0.0f, 0.0f};
                    portals[0].placed = 0;
                    portals[1].entity.position = (Vector3) {0.0f, 0.0f, 0.0f};
                    portals[1].placed = 0;
                    max_values[0] = 0;
                    max_values[1] = 0;
                    min_values[0] = 100;
                    min_values[1] = 100;
                    rendered = 0;
                    player.life = 3;
                    
                    InicialMenu(botton_play, botton_load, botton_exit_inicial, &menu, fp, backgrounds, &first_time, &img, &number_map, &map, &load,
                                 &player, levers, enemys, &exit_opened, &turn, portals, &there_is_file, &there_is_map, &load_map_menu);

                    //Saindo do menu
                    if (load_map_menu)
                    {
                        FirstReadMap(map, &rendered, enemys, &qtd_enemys_max, &player, levers, &qtd_levers_max, &enemys_model_array[0], &fixed_enemy,
                                    &levers_model_array[0], &fixed_lever, &max_values[0], &min_values[0]);
                        menu = 0;
                        rendered = 1;
                        load_map_menu = 0;
                    }
            }
            else if (pause)
            {
                reset = 0;
                MenuPause(pause_continue, load_pause, save_game, botton_exit_inicial, return_menu_inic, &pause, fp, &menu, &load,
                           &player, enemys, levers, &number_map, &exit_opened, &map, &rendered, &qtd_levers_max, &qtd_enemys_max, &turn, portals, &saved, &there_is_file);
                //printf("D");

                if (load)
                {
                    LoadMap(number_map, &map);
                    rendered = 0;
                    qtd_levers_max = 0;
                    qtd_enemys_max = 0;
                    FirstReadMap(map, &rendered, enemys, &qtd_enemys_max, &player, levers, &qtd_levers_max, &enemys_model_array[0], &fixed_enemy,
                                &levers_model_array[0], &fixed_lever, &max_values[0], &min_values[0]);
                    
                    //qtd_levers = 0;

                    LoadGame(&map, &player, levers, enemys, &exit_opened, &number_map, &turn, portals);
                    pause = 0;
                    load = 0;
                }
            }
            DrawFPS(0, 0);

            //Desenhando a transicao
            if (tran.activated)
                DrawTransition(tran);

        EndDrawing();
    }

    UnloadModel(player_model_array[0]);
    UnloadModel(player_model_array[1]);
    UnloadModel(player_model_array[2]);
    UnloadModel(enemys_model_array[0]);
    UnloadModel(enemys_model_array[1]);
    UnloadModel(enemys_model_array[2]);
    UnloadModel(wall_model);
    UnloadModel(levers_model_array[0]);
    UnloadModel(levers_model_array[1]);
    UnloadModel(portal_model_array[0]);
    UnloadModel(portal_model_array[1]);
    UnloadModel(exit_model_array[0]);
    UnloadModel(exit_model_array[1]);
    UnloadModel(spike_model);
    UnloadModel(aim_model);
    
    UnloadTexture(backgrounds[0]);
    UnloadTexture(backgrounds[1]);
    UnloadTexture(backgrounds[2]);

    UnloadFont(fp);
    CloseWindow();

    return 0;
}