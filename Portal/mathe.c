#include <stdlib.h>
#include <math.h>
#include "mathe.h"

// Clamp float value
float ClampFloat(float value, float minimo, float maximo)
{
    float result = (value < minimo)? minimo : value;

    if (result > maximo) result = maximo;

    return result;
}

// Calculate linear interpolation between two floats
float LerpFloat(float start, float fim, float amount)
{
    float result = start + amount*(fim - start);

    return result;
}

//Essa funcao retorna -1 ou 0 ou 1
int Sign(int valor)
{
    int v_final = 0;

    if (valor != 0)
        v_final = valor/abs(valor);

    return v_final;
}

//Essa funcao retorna -1 ou 0 ou 1
int SignFloat(float valor)
{
    int v_final = 0;

    if (valor != 0)
        v_final = valor/fabs(valor);

    return v_final;
}

// Funcao que calcula o angulo entre 2 pontos da computacao
float PointDirection(float x1, float y1, float x2, float y2)
{
    // Pegando a distancia entre os pontos
    float x = x2 - x1;
    float y = y2 - y1;

    float angle = atan2f(y, x);

    return angle;
}

// Funcao que calcula o angulo entre 2 pontos usando Y da matematica
float PointDirectionMath(float x1, float y1, float x2, float y2)
{
    // Pegando a distancia entre os pontos
    float x = x2 - x1;
    float y = y2 - y1;

    float angle = atan2f(y * -1, x);

    return angle;
}

//Funcao que calcula a distancia entre dois pontos
float PointDistance(float x1, float y1, float x2, float y2)
{
    float x = x2 - x1;
    float y = y2 - y1;

    float distance = sqrt(x * x + y * y);

    return distance;
}

//Funcao que verifica a colisao usando a matriz
//X e Y eh a posicao em pixels
/*
int CollisionInMatrix(char matrix[ROWS][COLS], int x, int y, int obj)
{
    int collided = 0;

    if (matrix[y / BLOCKSIZE][x / BLOCKSIZE] / 10 == obj)
        collided = 1;

    return collided;
}*/

//Funcao que gera um inteiro aleatorio entre dois valores
int RandomNumberInt(int lowest, int highest)
{
    int number = rand();
    int final_number = lowest + (number % (highest - lowest + 1));

    return final_number;
}

//Gerando um float aleatorio entre dois valores floats NAO INCLUSIVOS
float RandomNumberFloat(float lowest, float highest)
{
    float num = lowest + (highest - lowest) * ((float)rand()/(float)(RAND_MAX));

    return num;
}

//Funcao que transforma do y computacao para o y matematica (float)
float CompToMathFloat(float y_math_origin, float y_old)
{
    float y_math = y_math_origin - y_old;

    return y_math;
}

//Funcao que transforma do y computacao para o y matematica (int)
int CompToMathInt(int y_math_origin, int y_old)
{
    int y_math = y_math_origin - y_old;

    return y_math;
}

//Funcao que converte o nosso angulo tan^-1 comp para angulos normais
float DeegresComptoMath(float comp_angle)
{
    float math_angle = 0;

    if (comp_angle < 0)
        math_angle = comp_angle * -1;
    else
        math_angle = 360 - comp_angle;
    
    return math_angle;
}

//Funcao que converte radianos para graus
float RadianToDegrees(float radian)
{
    float degrees = radian * 180/MY_PI;

    return degrees;
}

//Funcao que converte graus para radianos
float DegreesToRadian(float degrees)
{
    float radian = degrees * (MY_PI/180);

    return radian;
}