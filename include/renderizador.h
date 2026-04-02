#pragma once

// este es el ÚNICO archivo .h de todo el proyecto que debe incluir librerías gráficas. (leer a continuación)
// animal.h necesita ETSIDI.h para crear un puntero a SpriteSequence, pero se mantiene cierto para freeglut.h

#include "freeglut.h"
#include "ETSIDI.h"

class Renderizador {
public:

    void limpiarPantalla();

    void dibujarSprite(const char* rutaImagen, float ancho, float alto, float posx, float posy, float capa, 
                       int cols = 1, int rows = 1, int stateX = 0, int stateY = 0);

};