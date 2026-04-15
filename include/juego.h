#pragma once

#include "tablero.h"
#include "menu.h"
#include "tablero.h"
//#include "arena.h"
#include "renderizador.h" 
#include "transicion.h" 

enum  Comando { ARRIBA, ABAJO, IZQUIERDA, DERECHA, SELECCIONAR, CANCELAR, NINGUNO };

enum Jugador { J1, J2 };

class Juego {

    Transicion transicion;
    Menu* menu;
    Tablero* tablero;
    //Arena* arena;
    Renderizador* motor;

    double anchoVentana = 480;
    double altoVentana = 270;

	Comando traducirTeclaJ1(unsigned char key);
	Comando traducirTeclaJ2(int key);

public:
    Juego();
    ~Juego();

    double getAnchoVentana() {return anchoVentana;} // Para decirle al main cuánto mide la ventana que debe crear
    double getAltoVentana() {return altoVentana;}

    enum Estado { MENU, TABLERO, ARENA };
    Estado estadoActual;
    Estado proximoEstado;

    // game loop dividido en dos fases desacopladas
    void actualizarLogica(float dt); // se llama desde OnTimer
    void renderizarGraficos(); // se llama desde OnDraw

    // coordinador de inputs de teclado
    void procesarTeclaPresionada(unsigned char key);
    void procesarTeclaLevantada(unsigned char key);
    void procesarTeclaEspecialPresionada(int key);
    void procesarTeclaEspecialLevantada(int key);
};