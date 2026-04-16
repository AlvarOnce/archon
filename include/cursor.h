#pragma once
#include "renderizador.h"

class Cursor 
{
    float posx;
    float posy;
    int idJugador; 

public:
    Cursor() {} 
    Cursor(float x_inicial, float y_inicial, int id); 

    void mover(int x, int y);
    void dibujar(Renderizador* motor);
};