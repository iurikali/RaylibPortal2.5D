#ifndef MATHE_H_INCLUDED
#define MATHE_H_INCLUDED

#define MY_PI 3.14159265358979323846

// Clamp float value
float ClampFloat(float value, float minimo, float maximo);

// Calculate linear interpolation between two floats
float LerpFloat(float start, float fim, float amount);

//Essa funcaoo retorna -1 ou 0 ou 1
int Sign(int valor);

//Essa funcaoo retorna -1 ou 0 ou 1, tendo float como argumento
int SignFloat(float valor);

//Funcao que calcula
float PointDirection(float x1, float y1, float x2, float y2);

// Funcao que calcula o angulo entre 2 pontos usando Y da matematica
float PointDirectionMath(float x1, float y1, float x2, float y2);

//Funcao que calcula a distancia entre 2 pontos
float PointDistance(float x1, float y1, float x2, float y2);

//Funcao que verifica se a colisao usando a matriz de inteiros
//int CollisionInMatrix(char matrix[ROWS][COLS], int x, int y, int obj);

//Funcao que gera um inteiro aleatorio entre dois valores
int RandomNumberInt(int lowest, int highest);

//Gerando um float aleatorio entre dois valores NAO INCLUSIVOS
float RandomNumberFloat(float lowest, float highest);

//Funcao que transforma do y computacao para o y matematica
float CompToMathFloat(float y_math_origin, float y_old);

//Funcao que transforma do y computacao para o y matematica (int)
int CompToMathInt(int y_math_origin, int y_old);

//Funcao que converte o nosso angulo tan^-1 comp para angulos normais
float DeegresComptoMath(float comp_angle);

//Funcao que converte radianos para graus
float RadianToDegrees(float radian);

//Funcao que converte graus para radianos
float DegreesToRadian(float degrees);

#endif // MATHE_H_INCLUDED
