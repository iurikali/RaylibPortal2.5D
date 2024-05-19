#include <stdio.h>
#include <math.h>
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define MY_PI 3.14159265358979323846

// Funcao que calcula o angulo entre 2 pontos da computacao
float PointDirection(float x1, float y1, float x2, float y2)
{
    // Pegando a distancia entre os pontos
    float x = x2 - x1;
    float y = y2 - y1;

    float angle = atan2f(y, x);

    return angle;
}

//Funcao que converte radianos para graus
float RadianToDegrees(float radian)
{
    float degrees = radian * 180/MY_PI;

    return degrees;
}


int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60);

    //Iniciando a camera 
    Camera3D cam = {0};
    cam.target = (Vector3) {0.0f, 0.0f, 0.0f}; //Fazendo a camera olhar para esse ponto
    cam.position = (Vector3) {0.0f, 13.0f, 0.1f}; //Posicao inicial da camera
    cam.up = (Vector3) {0.0f, 1.0f, 0.0f}; //Rotacao da camera
    cam.fovy = 45.0f; //Campo de visao
    cam.projection = CAMERA_PERSPECTIVE; //Tipo de projecao

    /*
        Sobre o 3D:
        - x eh o x normal
        - z eh o y do 2D, z negativo vai pra cima e positivo pra baixo
        - y eh a altura, y positivo para cima e negativo para baixo
        - Visao top-down (0.0f, y, 0.1f)

        Detalhes sobre as configs da camera:
        CameraUpdate():
        - Aparentemente tudo que faz eh atualizar os valores da camera (position, target etc), mas 
        tambem adiciona movimentacao no WASD, setinhas e mouse,
        nao achei uma maneira de retirar isso, entao a solucao eh nao usar essa funcao e atualizar os 
        valores na mao.
        - Utilizar essa funcao como debug para achar os valores ideais

        Target:
        - Faz a camera olhar para o ponto
        - Mudar os 3 pontos ao mesmo tempo nao gera nenhuma altercao
        - Mudar o target e position juntos para se movimentar sem perder o foco

        Position:
        - O .target eh o nosso eixo
        - Para andar pelo eixo, tem que mudar o x y z ao mesmo tempo de maneira proporcional (ex: 2, 2, 2)
        - Imaginar que o .target eh um espeto de churrasco e o .position eh a carne
        - Provavelmente para fazer uma camera 3 pessoa no x e z tera que transformar em coordenadas polares
        ou talvez em coordenadas esfericas
        - Aparentemente nao podemos deixar a camera examente no 0, y, 0 com o target fixo
        


        UP:
        - sempre entre -1f e 1f
        - up.y sempre em 1f
        - up.y = -1f (deixa de cabeca para baixo)
        - Para rotacionar manualmente a camera eh melhor colocar no FREE e ajustar com o 'Q' 'E'
        ate achar um valor bom e colocar manualmente depois.

        Exemplos de camera:
        - cam.target = (Vector3) {0.0f, 0.0f, 0.0f};
          cam.position = (Vector3) {0.0f, 13.0f, 2.1f};
          (Visao top down com um pouco de perspectiva)
    */

    //Definindo a posicao do cubo
    Vector3 cube_position = {0.0f, 0.0f, 0.0f};

    //Definindo a posicao do bolinha
    Vector3 ball_positon = {0.0f, 0.0f, -2.0f};



    float theta = 0;
    float radius = 2.0f;

    //Variaveis de teste
    float valor_x = 0.0f;
    float valor_y = 0.0f;
    float valor_z = 0.0f;

    float valor = 1.0f;

    //DisableCursor();

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_P))
            valor_x = valor;
        else if (IsKeyPressed(KEY_O))
            valor_x = -valor;
        else
            valor_x = 0.0f;

        if (IsKeyPressed(KEY_L))
            valor_y = valor;
        else if (IsKeyPressed(KEY_K))
            valor_y = -valor;
        else
            valor_y = 0.0f;

        if (IsKeyPressed(KEY_M))
            valor_z = valor;
        else if (IsKeyPressed(KEY_N))
            valor_z = -valor;
        else
            valor_z = 0.0f;

        

        
        //Atualizando os valores da camera
        cam.target.x += valor_x;
        cam.target.z += valor_z;

        cam.position.x += valor_x;
        cam.position.y += valor_y;
        cam.position.z += valor_z;


        //UpdateCamera(&cam, CAMERA_THIRD_PERSON);

        /*cube_position.x += valor_x;
        cube_position.y += valor_y;
        cube_position.z += valor_z;*/

        //Fazendo a bolinha circular o cubo
        if (IsKeyDown(KEY_I))
            theta += .01;
        if (IsKeyDown(KEY_U))
            theta -= .01;

        //Calculando o theta
        Vector2 screen_cube_position = GetWorldToScreen(cube_position, cam);
        theta = PointDirection(screen_cube_position.x, screen_cube_position.y,
        GetMouseX(), GetMouseY());

        ball_positon.x = cosf(theta) * radius;
        ball_positon.z = sinf(theta) * radius;



        Ray mouse_ray = GetMouseRay(GetMousePosition(), cam);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            //Iniciando a area 3D
            BeginMode3D(cam);

                //Desenhando o cubo
                DrawCube(cube_position, 2.0f, 2.0f, 2.0f, RED);
                //Desenhando as bordas do cubo
                DrawCubeWires(cube_position, 2.0f, 2.0f, 2.0f, BLUE);

                //Desenhando a bolinha
                DrawSphere(ball_positon, 0.1f, BLUE);

                //Desenhando a grid para se orientar
                DrawGrid(10, 1.0f);

                DrawRay(mouse_ray, GREEN);

            EndMode3D();


        EndDrawing();

        /*printf("\nPosition: %f : %f : %f", cam.position.x, cam.position.y, cam.position.z);
        printf("\nUp: %f : %f : %f", cam.up.x, cam.up.y, cam.up.z);
        printf("\nTarget: %f : %f : %f", cam.target.x, cam.target.y, cam.target.z);
        printf("\nCube: %f : %f : %f", cube_position.x, cube_position.y, cube_position.z);*/
        printf("\nAngulo: %f", RadianToDegrees(theta));
    }

    CloseWindow();

    return 0;
}