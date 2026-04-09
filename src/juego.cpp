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

    for (int i = 0; i < 10; i++) // ejemplo de creacion de 32 animales (cabras, dibujadas como palomas)
    {
        misAnimales[i] = new Cabra();
        misAnimales[i]->posx_ = 50 + 30 * i;
        misAnimales[i]->posy_ = 100 + 5*i;
    }
}

Juego::~Juego() {
    delete miMenu;
    delete miTablero;
    //delete miArena;
    delete motorGrafico;
}

void Juego::actualizarLogica(float dt) {
    // FASE 1: matemáticas, colisiones y reglas del juego

    switch (estadoActual) {

    case MENU:
       
        miMenu->actualizar(25);

        break;

    case TABLERO:

        // Aqui por ejemplo irira tablero->actualiza() y DENTRO DE TABLERO: for(todoslosanimales) Animal[i].mover o Animal[i].actualizar
        for (int i = 0; i < 10; i++) // ESTO DENTRO DE ACTUALIZAR TABLERO
        misAnimales[i]->actualizar(25);
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

        for (int i = 0; i < 10; i++) // LO MISMO QUE ARRIBA DENTRO DE DIBUJAR TABLERO
        misAnimales[i]->dibujar(motorGrafico);
        break;

    case BATALLA:
        
        break;
    }
}

void Juego::procesarTeclaPresionada(unsigned char key) // JUGADOR 1 (WASD)
{
    if (key == 27) exit(0); // Esc siempre cierra el juego, aunque en un futuro molaría poner un menú de pausa

    switch (estadoActual) {

    case MENU:
        if (key == 13) { // Intro para elegir una opción
            switch (miMenu->getOpcionActual()) {

            case Selector::JUGAR: // de momento al elegir JUGAR pasa directamente al TABLERO, falta una pantalla para elegir bando etc.
                estadoActual = TABLERO;

            case Selector::OPCIONES: // en opciones puede estar el volumen o quizá algo del juego
                //estadoActual = OPCIONES;

            case Selector::CONTROLES: // en principio muestra nuestros controles, quizá se puedan elegir los tuyos propios
                //estadoActual = CONTROLES;

            case Selector::CREDITOS:
                //estadoActual = CREDITOS;
                break;
            }
        }

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
    case MENU:
        if (key == GLUT_KEY_UP) miMenu->moverSelector(-1); // arriba resta 1 (se acerca a 0 que es JUGAR)
        if (key == GLUT_KEY_DOWN) miMenu->moverSelector(1); // abajo suma 1 (bajándo hacia el 3 que es CREDITOS)
        break;

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