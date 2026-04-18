#include <iostream>
#include <stdlib.h>
#include "arena.h"
#include "juego.h"
#include "tablero.h"

#define numeroAnimales 9 // Por ahora crea 9 entidades (todas cabras)

Tablero miTablero;

Juego::Juego() {

    estadoActual = MENU;
    proximoEstado;

    miMenu = new Menu();
    miTablero = new Tablero();
    miArena = new Arena();
    motorGrafico = new Renderizador();

    for (int i = 0; i < numeroAnimales; i++) // ejemplo de creacion de 32 animales (cabras, dibujadas como palomas)
    {
        misAnimales[i] = new Cabra(-15*(numeroAnimales-i) + 11,  36+(22*i) + 11, -3 - 0.01*i, 20);
    }
}

Juego::~Juego() {
    delete miMenu;
    delete miTablero;
    delete miArena;
    delete motorGrafico;
}

void Juego::actualizarLogica(float dt) {
    // FASE 1: matemáticas, colisiones y reglas del juego

    switch (estadoActual) {

    case MENU:
       
        miMenu->actualizar(25);

        break;

    case TABLERO:

        for (int i = 0; i < numeroAnimales; i++) 
        misAnimales[i]->actualizar(25);
        break;

        //if(el cursor esta sobre un animal, funcion propia de tablero y cursor detectar la casilla)
        // miTablero->tarjeta.animalSeleccionado = ___

    case BATALLA:

        miArena->actualizar(dt);
        break;

  
    }


    if (transicion.activo) transicion.actualizar(25);

    if (transicion.getEstado() == Transicion::CERRADO)
    {
        estadoActual = proximoEstado;
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
        miTablero->dibujar(motorGrafico);

        for (int i = 0; i < numeroAnimales; i++) // LO MISMO QUE ARRIBA DENTRO DE DIBUJAR TABLERO
        misAnimales[i]->dibujar(motorGrafico); // 9 cabras

        miTablero->cursor.dibujar(motorGrafico);

        //if(el cursor esta sobre un animal, funcion propia de tablero y cursor detectar la casilla)
        // en actualizar se determina que tarjeta se va a dibujar interiormente
        if(miTablero->cursor.posx > 150 && miTablero->cursor.posx <170) // ELIMINAR ESTA CONDICION
        miTablero->tarjeta.dibujar(motorGrafico);

        break;

    case BATALLA:
        miArena->dibujar();
        break;
    }

    if(transicion.activo) { transicion.dibujar(motorGrafico); }
}

void Juego::procesarTeclaPresionada(unsigned char key) // Hacer que tecla solo se procese si transicion.activo = false
{
    if (key == 27) exit(0); // Esc siempre cierra el juego, aunque en un futuro molaría poner un menú de pausa

    switch (estadoActual) {

        case MENU:
        if (key == 13) { // Intro para elegir una opción
            switch (miMenu->getOpcionActual()) {

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
        if (key == 'w' || key == 'W') miTablero->moverCursorJ1(0, 1);
        if (key == 's' || key == 'S') miTablero->moverCursorJ1(0, -1);
        if (key == 'a' || key == 'A') miTablero->moverCursorJ1(-1, 0);
        if (key == 'd' || key == 'D') miTablero->moverCursorJ1(1, 0);
        
        if (key == '.') miTablero->seleccionarCasillaJ1(); // Botón del J1
        break;

     case BATALLA: 
         if (key == 'w' || key == 'W') miArena->recibirMovimiento(0, ARRIBA, true);
         if (key == 's' || key == 'S') miArena->recibirMovimiento(0, ABAJO, true);
         if (key == 'a' || key == 'A') miArena->recibirMovimiento(0, IZQUIERDA, true);
         if (key == 'd' || key == 'D') miArena->recibirMovimiento(0, DERECHA, true);
         if (key == '.') miArena->recibirAtaque(0); //poner los controles qeu querais
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
        if (key == 'w' || key == 'W') miArena->recibirMovimiento(0, ARRIBA, false);
        if (key == 's' || key == 'S') miArena->recibirMovimiento(0, ABAJO, false);
        if (key == 'a' || key == 'A') miArena->recibirMovimiento(0, IZQUIERDA, false);
        if (key == 'd' || key == 'D') miArena->recibirMovimiento(0, DERECHA, false);
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
        if (key == GLUT_KEY_UP) { miTablero->moverCursorJ2(0, 1); miTablero->cursor.mover(0, 1); } // esto es PROVISIONAL y hay que modificarlo ( es para observar movimiento en pantalla por ahora)
        if (key == GLUT_KEY_DOWN) { miTablero->moverCursorJ2(0, -1); miTablero->cursor.mover(0, -1); } // hasta solucionar moverCursorJ1 y J2.
        if (key == GLUT_KEY_LEFT) { miTablero->moverCursorJ2(-1, 0); miTablero->cursor.mover(-1, 0); }
        if (key == GLUT_KEY_RIGHT) { miTablero->moverCursorJ2(1, 0); miTablero->cursor.mover(1, 0); }

        if (key == '.') miTablero->seleccionarCasillaJ2(); // Botón del J2
        break;

    case BATALLA:
        if (key == GLUT_KEY_UP)    miArena->recibirMovimiento(1, ARRIBA, true);
        if (key == GLUT_KEY_DOWN)  miArena->recibirMovimiento(1, ABAJO, true);
        if (key == GLUT_KEY_LEFT)  miArena->recibirMovimiento(1, IZQUIERDA, true);
        if (key == GLUT_KEY_RIGHT) miArena->recibirMovimiento(1, DERECHA, true);
        if (key == '.') miArena->recibirAtaque(1);
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
        if (key == GLUT_KEY_UP)    miArena->recibirMovimiento(1, ARRIBA, false);
        if (key == GLUT_KEY_DOWN)  miArena->recibirMovimiento(1, ABAJO, false);
        if (key == GLUT_KEY_LEFT)  miArena->recibirMovimiento(1, IZQUIERDA, false);
        if (key == GLUT_KEY_RIGHT) miArena->recibirMovimiento(1, DERECHA, false);
        break;
    }
}