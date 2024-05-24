#include "raylib.h"
#include "camera.h"
#include "structs.h"


Camera3D NewCamera()
{
    Camera3D cam = {0};

    cam.target = (Vector3) {0.0f, 0.0f, 0.0f}; //Fazendo a camera olhar para esse ponto
    cam.position = (Vector3) {0.0f, 13.0f, 0.1f}; //Posicao inicial da camera
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
    cam->target.x = player.position.x;
    cam->target.z = player.position.z;

    cam->position.x = player.position.x;
    cam->position.z = player.position.z + 0.1f;
}