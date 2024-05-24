#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "raylib.h"
#include "structs.h"

Camera3D NewCamera();

void CameraMoviment(Camera3D *cam, float x_value, float z_value);

void CameraFollowPlayer(Camera3D *cam, Player player);

#endif // CAMERA_H_INCLUDED
