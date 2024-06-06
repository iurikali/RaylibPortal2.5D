#include "models.h"
#include "raylib.h"
#include "raymath.h"

Models NewModels(Model *array, char axe, Color color, int frame_vel, int image_number, int *fixed_position)
{
    Models models = {0};

    models.angle = 0.0f;
    models.color = color;
    models.frame_index = 0;
    models.frame_vel = frame_vel;
    models.image_number = image_number;
    models.model = array;
    models.scale = (Vector3) {.5f, .5f, .5f};
    models.timer = 0;

    switch (axe)
    {
        case 'X':
        {
            models.axes = (Vector3) {1.0f, 0.0f, 0.0f};
            break;
        }
        case 'Y':
        {
            models.axes = (Vector3) {0.0f, 1.0f, 0.0f};
            break;
        }
        case 'Z':
        {
            models.axes = (Vector3) {0.0f, 0.0f, 1.0f};
            break;
        }
    
    default:
        models.axes = (Vector3) {0.0f, 1.0f, 0.0f};
        break;
    }


    //Ajustando a posicao
    if (!(*fixed_position))
    {
        for (int i = 0; i <= image_number - 1; i++)
        {
            // Compute model translation matrix to center model on draw position (0, 0 , 0)
            BoundingBox bb = GetModelBoundingBox(array[i]);
            Vector3 center = { 0 };
            center.x = bb.min.x + (((bb.max.x - bb.min.x) / 2));
            center.z = bb.min.z + (((bb.max.z - bb.min.z) / 2));

            Matrix matTranslate = MatrixTranslate(-center.x, 0, -center.z);
            array[i].transform = matTranslate;
        }
        *fixed_position = 1;
    }


    return models;
}


void DrawModels(Vector3 position, Models *model)
{
    // Atualizando a sprite
    // Rodando o timer
    if (model->frame_vel != 0)
    {
        model->timer++;
        // printf("\n%d", imagem->timer);

        if (model->timer >= (60 / model->frame_vel))
        {
            // Mudando a imagem
            model->frame_index = (model->frame_index + 1) % model->image_number;
            model->timer = 0;
        }
    }


    DrawModelEx(model->model[model->frame_index], position, model->axes, model->angle, model->scale, model->color);
}