#pragma once
#include "renderizador.h"

struct Letra {
    float altura;
    float horiz;
};

class Menu {
private:
    float angulo{};
    Letra titulo[6];
    double ancho = 480;
    double alto = 270;

public:

    void actualizar();
    void dibujar(Renderizador* motor);
};