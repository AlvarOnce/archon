#pragma once
#include "renderizador.h"

struct Letra {
    float horiz;
    float altura;
    float capa;
};

struct Tractor {
    float posx = 550;
    float posy = 65;
    int frameActualX = 0, frameActualY = 0;
    float timer{}, msStep = 300;
};

struct Paloma {
    float posx = -10;
    float posy = 222;
    int frameActualX = 0, frameActualY = 1;
    float timer{}, msStep = 100;
};

struct Nube {
    float posx;
    float posy;
    float capa;
};

struct selector {
    float posx;
    float posy;

    enum opcion{
    JUGAR,
    OPCIONES,
    CONTROLES,
    CREDITOS
    };
};

class Menu {

public:

    Letra titulo[6] = {{0,0,-2.0},{0,0,-2.1},{0,0,-2.2},{0,0,-2.3},{0,0,-2.4},{0,0,-2.5}};
    Tractor tractor;
    Paloma paloma;
    Nube nube[2] = {{0,210,-1}, {240,210,-1.1} };


    float dt;
    float anguloLetras{};
    double ancho = 480;
    double alto = 270;

    void actualizar(float dt);
    void dibujar(Renderizador* motor);
};

