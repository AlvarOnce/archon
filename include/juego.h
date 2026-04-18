#pragma once

#include "tablero.h"
#include "menu.h"
#include "tablero.h"
#include "arena.h"
#include "renderizador.h" 
#include "animal.h"
#include "cabra.h"
#include "transicion.h" 

class Juego 
{
    Transicion transicion;
    Menu* miMenu;
    Tablero* miTablero;
    Arena* miArena;
    Renderizador* motorGrafico;
    Animal* misAnimales[18];

    double anchoVentana = 480;
    double altoVentana = 270;

public:

    double getAnchoVentana() {return anchoVentana;} // Para decirle al main cuánto mide la ventana que debe crear
    double getAltoVentana() {return altoVentana;}

    enum Estado { MENU, TABLERO, BATALLA };
    Estado estadoActual;
    Estado proximoEstado;

    Juego(); 
    ~Juego();

    // game loop dividido en dos fases desacopladas
    void actualizarLogica(float dt); // se llama desde OnTimer
    void renderizarGraficos(); // se llama desde OnDraw

    // coordinador de inputs de teclado
    void procesarTeclaPresionada(unsigned char key);
    void procesarTeclaLevantada(unsigned char key);
    void procesarTeclaEspecialPresionada(int key);
    void procesarTeclaEspecialLevantada(int key);
};