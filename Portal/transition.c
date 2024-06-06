#include "transition.h"
#include "defines.h"
#include "structs.h"
#include "raylib.h"
#include <stdio.h>

Transition NewTransition(int type, Color color)
{
    Transition tran = {0};

    tran.activated = 0;
    tran.changed = 0;
    tran.color = color;
    tran.speed = 7;
    tran.type = type;
    tran.rectangle = (Rectangle) {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    return tran;
}

//Funcao de logica
void TransitionUpdate(Transition *tran/*, int *exit_opened, Portal *portals, char (*mapa)[LINHAS][COLUNAS], int *renderizado, int *num_mapa, int *qtd_alavancas, int *qtd_inimigos_max*/)
{
    //Se ainda nao trocamos de fase
    if (!tran->changed)
    {
        //Vamos deixar escuro
        if (tran->color.a < 255 - tran->speed)
        {
            //Aumentando a alpha
            tran->color.a += tran->speed;
            //transicao->cor.a = 256;
            printf("\n%d", tran->color.a);
        }
        else
        {
            //Garantindo que vai estar tudo preto
            tran->color.a = 255;

            //Aqui a magica acontece
            switch(tran->type)
            {
                //1 é o tipo de mudar de fase
                case 1:
                {
                    //Aqui a gente chama a função que atualiza a fase
                    //Ai é com vc ALEF
                    tran->change_level = 1;
                    /**saida_aberta = 0;
                    *qtd_alavancas = 0;
                    *qtd_inimigos_max = 0;
                    portais->entidade.x = -LARGURA * 2;
                    portais->entidade.y = -ALTURA * 2;
                    portais->colocado = 0;
                    (portais + 1)->entidade.x = -LARGURA * 2;
                    (portais + 1)->entidade.y = -ALTURA * 2;
                    (portais + 1)->colocado = 0;

                    //Indo pro próximo mapa
                    *num_mapa += 1;
                    carrega_mapa(*num_mapa, mapa);
                    *renderizado = 0;*/
                    break;
                }
                //2 é o tipo do game over
                case 2:
                {
                    //Aqui a gente chama a função que reseta a fase? sla
                    //Ai é com vc ABNER
                    printf("\nGAME OVER");
                    break;
                }
            }
            //Zerando e falando que a gente já trocou de fase
            tran->type = 0;
            tran->changed = 1;
        }
    }
    //Trocamos de fase
    else
    {
        //Vamos clarear
        if (tran->color.a > 0 + tran->speed)
        {
            tran->color.a -= tran->speed;
        }
        //Voltamos ao normal
        else
        {
            tran->color.a = 0;
            printf("\n%d", tran->color.a);
            tran->changed = 0;
            tran->activated = 0;
        }
    }
}

//Função que soh desenha
void DrawTransition(Transition tran)
{
    DrawRectangleRec(tran.rectangle, tran.color);
}