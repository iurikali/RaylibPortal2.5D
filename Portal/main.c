#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "mathe.h"
#include "camera.h"
#include "structs.h"
#include "player.h"
#include "map.h"
#include "defines.h"




int main()
{
    char map[ROWS][COLS] = {0};

    LoadMap(1, &map);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60);

    //Iniciando a camera 
    Camera3D cam = NewCamera();

    //Iniciando o player
    Player player = NewPlayer();

    //Definindo a posicao do bolinha
    Vector3 ball_positon = {0.0f, 0.0f, -2.0f};



    float theta = 0;
    float radius = 2.0f;

    //DisableCursor();

    while (!WindowShouldClose())
    {   

        //Atualizando o player
        PlayerUpdate(&player);

        //Atualizando os valores da camera  
        //CameraMoviment(&cam, player.velh, player.velv);
        CameraFollowPlayer(&cam, player);

        CheckingCollisionWall(&player, map);

        //Fazendo a bolinha circular o cubo
        if (IsKeyDown(KEY_I))
            theta += .01;
        if (IsKeyDown(KEY_U))
            theta -= .01;

        //Calculando o theta
        Vector2 screen_cube_position = GetWorldToScreen(player.position, cam);
        theta = PointDirection(screen_cube_position.x, screen_cube_position.y,
        GetMouseX(), GetMouseY());

        ball_positon.x = cosf(theta) * radius;
        ball_positon.z = sinf(theta) * radius;

        BeginDrawing();

            ClearBackground(RAYWHITE);

            //Iniciando a area 3D
            BeginMode3D(cam);

                //Renderizando o mapa
                RenderMap(map);

                //Desenhando o player
                RenderPlayer(player);

                DrawLine3D((Vector3){player.position.x, player.position.y + 1.0f, player.position.z - ALMOST_HALF}, 
                (Vector3){player.position.x + (CUBE_SIZE * .5 * SignFloat(player.velh) + player.velh), player.position.y + 1.0f, player.position.z - ALMOST_HALF}, GREEN);

                DrawLine3D((Vector3){player.position.x, player.position.y + 1.0f, player.position.z + ALMOST_HALF}, 
                (Vector3){player.position.x + (CUBE_SIZE * .5 * SignFloat(player.velh) + player.velh), player.position.y + 1.0f, player.position.z + ALMOST_HALF}, GREEN);



                DrawLine3D((Vector3){player.position.x, player.position.y + 1.0f, player.position.z}, 
                (Vector3){player.position.x, player.position.y + 1.0f, player.position.z + (CUBE_SIZE * .5 * SignFloat(player.velv) + player.velv)}, GREEN);

                //Desenhando a bolinha
                DrawSphere(ball_positon, 0.1f, BLUE);

                //Desenhando a grid para se orientar
                DrawGrid(100, 1.0f);

            EndMode3D();

            DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}