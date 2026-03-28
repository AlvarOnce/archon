#pragma once

// este es el ÚNICO archivo .h de todo el proyecto que debe incluir librerías gráficas.
#include "freeglut.h"
#include "ETSIDI.h"

class Renderizador {
public:

    void limpiarPantalla();

    // antigua función Dibujar, ahora convertida en un método
    void dibujarSprite(const char* rutaImagen, float posx, float posy, float posz, float ancho, float alto);

    // otros métodos que llamará el coordinador Juego
    void dibujarMenu();
    void dibujarFondoTablero();
    void dibujarFondoArena();
    // void dibujarCursor(int x, int y);
};