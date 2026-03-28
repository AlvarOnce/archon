#pragma once

// Incluimos las clases lógicas y el nuevo gestor gráfico
#include "tablero.h"
#include "arena.h"
#include "renderizador.h" 

class Juego {
public:
    enum Estado { MENU, TABLERO, BATALLA };

    // game loop dividido en dos fases desacopladas
    void actualizarLogica(); // se llamará desde OnTimer
    void renderizarGraficos(); // se llamará desde OnDraw

    // coordinador de inputs de teclado
    void procesarTeclaPresionada(unsigned char key);
    void procesarTeclaLevantada(unsigned char key);
    void procesarTeclaEspecialPresionada(int key);
    void procesarTeclaEspecialLevantada(int key);

private:
    Estado estadoActual;

    // escenarios lógicos
    Tablero* miTablero;
    Arena* miArena;

    // esclavo que se encarga exclusivamente de pintar
    Renderizador* motorGrafico;
};