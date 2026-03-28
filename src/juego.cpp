#include "juego.h"
#include <iostream>
#include <stdlib.h>

void Juego::actualizarLogica() {
    // FASE 1: Matemáticas, colisiones y reglas del juego
    switch (estadoActual) {
    case MENU:
        
        break;
    case TABLERO:
        
        break;
    case BATALLA:
        
        break;
    }
}

void Juego::renderizarGraficos() {
    // FASE 2: Pintar en pantalla.

    motorGrafico->limpiarPantalla();

    switch (estadoActual) {
    case MENU:
        motorGrafico->dibujarMenu();
        break;

    case TABLERO:
        motorGrafico->dibujarFondoTablero();
        break;

    case BATALLA:
        motorGrafico->dibujarFondoArena();
        break;
    }
}

void Juego::procesarTeclaPresionada(unsigned char key) 
{
    if (key == 27) exit(0); // Esc

    switch (estadoActual) {
    case TABLERO:
        //if (key == 'w' || key == 'W') miTablero->moverCursor(0, 1);
        //if (key == 's' || key == 'S') miTablero->moverCursor(0, -1);
        //if (key == 13) miTablero->seleccionarCasilla(); // Enter
        //break;

    case BATALLA:
        // Pasamos las teclas WASD a la lógica de la arena
        // miArena->recibirInputJugador1(key);
        break;
    }
}

void Juego::procesarTeclaLevantada(unsigned char key) {
    switch (estadoActual) {
    case BATALLA:
        // si suelta la W, A, S o D, le decimos a la arena que apague el motor de ese lado
        // miArena->recibirInputLevantadoJugador1(key);
        break;
    default:
        break;
    }
}

void Juego::procesarTeclaEspecialPresionada(int key) {
    switch (estadoActual) {
    case TABLERO:
        // En el tablero, el Jugador 2 (Flechas) también mueve el cursor general
        // miTablero->moverCursorEspecial(key); 
        break;

    case BATALLA:
        // Pasamos las flechas a la lógica de la arena
        // miArena->recibirInputJugador2(key);
        break;
    }
}

void Juego::procesarTeclaEspecialLevantada(int key) {
    switch (estadoActual) {
    case TABLERO:
        // En el tablero, el Jugador 2 (Flechas) también mueve el cursor general
        // miTablero->moverCursorEspecial(key); 
        break;

    case BATALLA:
        // Pasamos las flechas a la lógica de la arena
        // miArena->recibirInputJugador2(key);
        break;
    }
}