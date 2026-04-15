#include <iostream>
#include <stdlib.h>

#include "juego.h"
#include "tablero.h"

Tablero miTablero;

Juego::Juego() {

    estadoActual = MENU;
    proximoEstado;

    menu = new Menu();
    tablero = new Tablero();
    //arena = new Arena();
    motor = new Renderizador();
}

Juego::~Juego() {
    delete menu;
    delete tablero;
    //delete arena;
    delete motor;
}

void Juego::actualizarLogica(float dt) {
    // FASE 1: matemáticas, colisiones y reglas del juego

    switch (estadoActual) {

    case MENU:
       
        menu->actualizar(25);

        break;

    case TABLERO:

		tablero->actualizar(25);
        break;

    case ARENA:

        //arena->actualizar(25);
        break;        
    }

    // transición entre estados 
    if (transicion.activo) transicion.actualizar(25);
    if (transicion.getEstado() == Transicion::CERRADO)
    {
        estadoActual = proximoEstado;
    }
}

void Juego::renderizarGraficos() {
    // FASE 2: pintar en pantalla

    motor->limpiarPantalla();

    switch (estadoActual) {
    case MENU:
        menu->dibujar(motor);
        break;

    case TABLERO:  
        tablero->dibujar(motor);       
        break;

    case ARENA:
		//arena->dibujar(motor);
        break;
    }

    if(transicion.activo) transicion.dibujar(motor);
}

void Juego::procesarTeclaPresionada(unsigned char key) // Hacer que tecla solo se procese si transicion.activo = false
{
    if (key == 27) exit(0); // Esc siempre cierra el juego, aunque en un futuro molaría poner un menú de pausa

    switch (estadoActual) {

        case MENU:
        if (key == 13) { // Intro para elegir una opción
            switch (menu->getOpcionActual()) {

            case Selector::JUGAR: 
                transicion.empieza();
                proximoEstado = TABLERO;
                break;

            //case Selector::OPCIONES: // en opciones puede estar el volumen o quizá algo del juego
            //    estadoActual = OPCIONES; // no sé si los submenús del ménu son un estado 
            //    break;

            //case Selector::CONTROLES: // en principio muestra nuestros controles, quizá se puedan elegir los tuyos propios
            //    estadoActual = CONTROLES;
            //    break;

            //case Selector::CREDITOS:
            //    estadoActual = CREDITOS;
            //    break;
            }

        }
        break;

        case TABLERO: // movimiento discreto en el tablero
        if (key == 'w' || key == 'W') tablero->moverCursor(0,0, 1);
        if (key == 's' || key == 'S') tablero->moverCursor(0,0, -1);
        if (key == 'a' || key == 'A') tablero->moverCursor(0,-1, 0);
        if (key == 'd' || key == 'D') tablero->moverCursor(0,1, 0);
        
        if (key == '.') tablero->seleccionarCasilla(); // Botón del J1
        break;

     case ARENA: 
        // movimiento continuo, se activa el bool "interruptor"
        // arena->recibirInputJugador1(key, true); 
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

    case ARENA:
        // se apaga el bool al levantar la tecla
        // miArena->recibirInputJugador1(key, false);
        break;
    }
}

void Juego::procesarTeclaEspecialPresionada(int key) // JUGADOR 2 (FLECHAS)
{
    switch (estadoActual) {
    case MENU:
        if (key == GLUT_KEY_UP) menu->moverSelector(-1); // arriba resta 1 (se acerca a 0 que es JUGAR)
        if (key == GLUT_KEY_DOWN) menu->moverSelector(1); // abajo suma 1 (bajándo hacia el 3 que es CREDITOS)
        break;

    case TABLERO:
        if (key == GLUT_KEY_UP)    { tablero->moverCursor(1,0, 1); tablero->cursor.mover(0, 1); } // esto es PROVISIONAL y hay que modificarlo ( es para observar movimiento en pantalla por ahora)
        if (key == GLUT_KEY_DOWN)  { tablero->moverCursor(1,0, -1); tablero->cursor.mover(0, -1); } // hasta solucionar moverCursorJ1 y J2.
        if (key == GLUT_KEY_LEFT)  { tablero->moverCursor(1,-1, 0); tablero->cursor.mover(-1, 0); }
        if (key == GLUT_KEY_RIGHT) { tablero->moverCursor(1,1, 0); tablero->cursor.mover(1, 0); }
        if (key == '.') tablero->seleccionarCasilla(); // Botón del J2
        break;

    case ARENA:
        // arena->recibirInputJugador2(key, true);
        break;
    }
}

void Juego::procesarTeclaEspecialLevantada(int key)
{
    switch (estadoActual) {
    case TABLERO:
        // igual que antes, aquí no hay que poner nada
        break;

    case ARENA:
        // arena->recibirInputJugador2(key, false);
        break;
    }
}