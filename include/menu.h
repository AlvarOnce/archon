#pragma once

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
    void dibuja(Renderizador* motor, double ancho, double alto);
};