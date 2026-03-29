#pragma once
#include "Renderizador.h"

struct Letra {
    float altura;
    float horiz;
};

class Menu {
private:
    float angulo{};
    Letra titulo[6];

public:
    void actualiza();
    void dibuja(Renderizador* motor);
};