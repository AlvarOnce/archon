#include "juego.h"
#include "tablero.h"
#include <iostream>
#include <stdlib.h>

Tablero miTablero;

Juego::Juego() {
    estadoActual = MENU;

    miMenu = new Menu();
    miTablero = new Tablero();
    //miArena = new Arena();
    motorGrafico = new Renderizador();
}

Juego::~Juego() {
    delete miMenu;
    delete miTablero;
    //delete miArena;
    delete motorGrafico;
}

void Juego::actualizarLogica() {
    // FASE 1: matemáticas, colisiones y reglas del juego

    switch (estadoActual) {

    case MENU:
       
        miMenu->actualizar();
        break;

    case TABLERO:

        // Aqui por ejemplo irira tablero->actualiza() y DENTRO DE TABLERO: for(todoslosanimales) Animal[i].mover o Animal[i].actualizar
        break;

    case BATALLA:

        // Aqui por ejemplo irira batalla->actualiza()
        break;
    }
}

void Juego::renderizarGraficos() {
    // FASE 2: pintar en pantalla.

    motorGrafico->limpiarPantalla();

    switch (estadoActual) {
    case MENU:
        miMenu->dibujar(motorGrafico);
        break;

    case TABLERO:
        miTablero->dibujarTablero();
        break;

    case BATALLA:
        
        break;
    }
}

void Juego::procesarTeclaPresionada(unsigned char key) // JUGADOR 1 (WASD)
{
    // Esc siempre cierra el juego, aunque en un futuro molaría poner un menú de pausa
    if (key == 27) exit(0); 

    switch (estadoActual) {
    case TABLERO: // movimiento discreto en el tablero
        if (key == 'w' || key == 'W') miTablero->moverCursorJ1(0, 1);
        if (key == 's' || key == 'S') miTablero->moverCursorJ1(0, -1);
        if (key == 'a' || key == 'A') miTablero->moverCursorJ1(-1, 0);
        if (key == 'd' || key == 'D') miTablero->moverCursorJ1(1, 0);
        
        if (key == '.') miTablero->seleccionarCasillaJ1(); // Botón del J1
        break;

    case BATALLA: 
        // movimiento continuo, se activa el bool "interruptor"
        // miArena->recibirInputJugador1(key, true); 
        break;
    }
}

void Juego::procesarTeclaLevantada(unsigned char key)
{
    switch (estadoActual) {
    case TABLERO:
        // como en el tablero el movimiento es discreto, no hay que hacer nada
        // cuando se levanta la tecla, ya se ha hecho todo al pulsarla.
        break;

    case BATALLA:
        // se apaga el bool al levantar la tecla
        // miArena->recibirInputJugador1(key, false);
        break;
    }
}

void Juego::procesarTeclaEspecialPresionada(int key) // JUGADOR 2 (FLECHAS)
{
    switch (estadoActual) {
    case TABLERO:
        if (key == GLUT_KEY_UP)    miTablero->moverCursorJ2(0, 1);
        if (key == GLUT_KEY_DOWN)  miTablero->moverCursorJ2(0, -1);
        if (key == GLUT_KEY_LEFT)  miTablero->moverCursorJ2(-1, 0);
        if (key == GLUT_KEY_RIGHT) miTablero->moverCursorJ2(1, 0);

        if (key == '.') miTablero->seleccionarCasillaJ2(); // Botón del J2
        break;

    case BATALLA:
        // miArena->recibirInputJugador2(key, true);
        break;
    }
}

void Juego::procesarTeclaEspecialLevantada(int key)
{
    switch (estadoActual) {
    case TABLERO:
        // igual que antes, aquí no hay que poner nada
        break;

    case BATALLA:
        // miArena->recibirInputJugador2(key, false);
        break;
    }
}