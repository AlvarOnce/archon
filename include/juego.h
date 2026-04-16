#pragma once

#include "tablero.h"
#include "menu.h"
#include "renderizador.h" 
#include "animal.h"
#include "cabra.h"
#include "transicion.h" 
#include "jugador.h" // ¡NUEVO!

class Juego
{
    Transicion transicion;
    Menu* miMenu;
    Tablero* miTablero;
    //Arena* miArena;
    Renderizador* motorGrafico;

    Animal* misAnimales[18];
    Jugador* jugadores[2]; // ¡NUEVO: El juego es el dueño de los jugadores!

    double anchoVentana = 480;
    double altoVentana = 270;

public:

    double getAnchoVentana() { return anchoVentana; }
    double getAltoVentana() { return altoVentana; }

    enum Estado { MENU, TABLERO, BATALLA };
    Estado estadoActual;
    Estado proximoEstado;

    Juego();
    ~Juego();

    // game loop dividido en dos fases desacopladas
    void actualizarLogica(float dt);
    void renderizarGraficos();

    // coordinador de inputs de teclado
    void procesarTeclaPresionada(unsigned char key);
    void procesarTeclaLevantada(unsigned char key);
    void procesarTeclaEspecialPresionada(int key);
    void procesarTeclaEspecialLevantada(int key);
};