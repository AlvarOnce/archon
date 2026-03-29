#pragma once

// este es el ÚNICO archivo .h de todo el proyecto que debe incluir librerías gráficas.
#include "freeglut.h"
#include "ETSIDI.h"

class Renderizador {
public:

    void limpiarPantalla();

    void dibujarSprite(const char* rutaImagen, float posx, float posy, float posz, float ancho, float alto);

};