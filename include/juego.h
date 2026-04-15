#pragma once

#include "tablero.h"
#include "menu.h"
#include "tablero.h"
//#include "arena.h"
#include "renderizador.h" 
#include "transicion.h" 

class Juego {

    Transicion transicion;
    Menu* menu;
    Tablero* tablero;
    //Arena* arena;
    Renderizador* motor;

    double anchoVentana_ = 480;
    double altoVentana_ = 270;

public:
    Juego();
    ~Juego();

    double anchoVentana() const {return anchoVentana_;} // Para decirle al main cuánto mide la ventana que debe crear
    double altoVentana() const {return altoVentana_;}

    enum Estado { MENU, TABLERO, ARENA };
    Estado estadoActual {MENU};
    Estado proximoEstado {MENU};

    // game loop dividido en dos fases desacopladas
    void actualizarLogica(float dt); // se llama desde OnTimer
    void renderizarGraficos(); // se llama desde OnDraw

    // coordinador de inputs de teclado
    void procesarTeclaPresionada(unsigned char key);
    void procesarTeclaLevantada(unsigned char key);
    void procesarTeclaEspecialPresionada(int key);
    void procesarTeclaEspecialLevantada(int key);

};