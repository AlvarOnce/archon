#pragma once
#include "renderizador.h"

struct Letra {
    float altura;
    float horiz;
};

struct Tractor {
    float posx = 550;
    float posy = 60;
};

struct Paloma {

    float posx = 0;
    float posy = 220;
    int frameActualX = 0, frameActualY = 1;
    float timer{}, msStep = 100;
};

class Menu {

public:

    Letra titulo[6];
    Tractor tractor;
    Paloma paloma;

    float dt;
    float anguloLetras{};
    double ancho = 480;
    double alto = 270;

    void actualizar(float dt);
    void dibujar(Renderizador* motor);
};

