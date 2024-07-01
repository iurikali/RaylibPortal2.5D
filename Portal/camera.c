#include "raylib.h"
#include "camera.h"
#include "structs.h"
#include <stdio.h>

Camera3D NewCamera()
{
    Camera3D cam = {0};

    cam.target = (Vector3) {0.0f, 0.0f, 0.0f}; //Fazendo a camera olhar para esse ponto
    cam.position = (Vector3) {0.0f, 13.0f, 0.1f}; //Posicao inicial da camera 13y
    cam.up = (Vector3) {0.0f, 1.0f, 0.0f}; //Rotacao da camera
    cam.fovy = 45.0f; //Campo de visao
    cam.projection = CAMERA_PERSPECTIVE; //Tipo de projecao


    return cam;
}

void CameraMoviment(Camera3D *cam, float x_value, float z_value)
{
    //Atualizando o target
    cam->target.x += x_value;
    cam->target.z += z_value;

    //Atualizando a posicao
    cam->position.x += x_value;
    cam->position.z += z_value;
}

void CameraFollowPlayer(Camera3D *cam, Player player)
{
    /*float incremento = 1.0f;
    static float target_x = 0.0f;
    static float target_z = 0.0f;
    static float target_y = 0.0f;

    if (IsKeyPressed(KEY_P)) target_x += incremento;
    if (IsKeyPressed(KEY_O)) target_x -= incremento;

    if (IsKeyPressed(KEY_L)) target_z += incremento;
    if (IsKeyPressed(KEY_K)) target_z -= incremento;

    if (IsKeyPressed(KEY_M)) target_y += incremento;
    if (IsKeyPressed(KEY_N)) target_y -= incremento;

    static float position_x = 0.0f;
    static float position_z = 10.1f; //10.1
    static float position_y = 13.0f; 

    if (IsKeyPressed(KEY_I)) position_x += incremento;
    if (IsKeyPressed(KEY_U)) position_x -= incremento;

    if (IsKeyPressed(KEY_J)) position_z += incremento;
    if (IsKeyPressed(KEY_H)) position_z -= incremento;

    if (IsKeyPressed(KEY_B)) position_y += incremento;
    if (IsKeyPressed(KEY_V)) position_y -= incremento;

    printf("\nPosition: %f : %f", position_x, position_y, position_z);
    printf("\ntarget: %f : %f", target_x, target_y, target_z);

    cam->target.x = player.entity.position.x + target_x;
    cam->target.y = target_y;
    cam->target.z = player.entity.position.z + target_z;

    cam->position.x = player.entity.position.x + position_x;
    cam->position.y = position_y;
    cam->position.z = player.entity.position.z + position_z; //cam->position.z = player.entity.position.z + 10.1f; */

    cam->target.x = player.entity.position.x + 2.0f;
    //cam->target.y = 13.0f;
    cam->target.z = player.entity.position.z + 2.0f;

    cam->position.x = player.entity.position.x + 2.0f;
    //cam->position.y = position_y;
    cam->position.z = player.entity.position.z + 10.0f; //cam->position.z = player.entity.position.z + 10.1f; */
}