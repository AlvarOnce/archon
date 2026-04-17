#include <iostream>
#include <stdlib.h>

#include "juego.h"

#define numeroAnimales 9 // Por ahora crea 9 entidades

Juego::Juego() {

    estadoActual = MENU;
    proximoEstado = MENU;

    miMenu = new Menu();
    miTablero = new Tablero();
    creditos = new Creditos();
    //miArena = new Arena();
    motorGrafico = new Renderizador();

    for (int j = 0; j < 2; j++) // Creación de 18 instancias de animal, guardadas en la colección de animales
        for (int i = 0; i < numeroAnimales; i++)
        {
            if (i % 4 == 0)
                misAnimales[i + j*numeroAnimales] = new Cabra(-44 * j - 15 * (numeroAnimales - i) + 11, 36 + (22 * i) + 11, -3 - 0.01 * i-0.08*j, 20);
            if (i % 4 == 1)
                misAnimales[i + j*numeroAnimales] = new Cerdo(-44 * j - 15 * (numeroAnimales - i) + 11, 36 + (22 * i) + 11, -3 - 0.01 * i - 0.08 * j, 20);
            if (i % 4 == 2)
                misAnimales[i + j*numeroAnimales] = new Gallina(-44 * j - 15 * (numeroAnimales - i) + 11, 36 + (22 * i) + 11, -3 - 0.01 * i - 0.08 * j, 20);
            if (i % 4 == 3)
                misAnimales[i + j * numeroAnimales] = new Oveja(-44 * j - 15 * (numeroAnimales - i) + 11, 36 + (22 * i) + 11, -3 - 0.01 * i - 0.08 * j, 20);
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
       
        miMenu->actualizar(dt);

        break;

    case TABLERO:

        for (int j = 0; j < 2; j++)
            for (int i = 0; i < numeroAnimales; i++)
            {
                misAnimales[i + j * numeroAnimales]->actualizar(dt);
            }

        break;

        //if(el cursor esta sobre un animal, funcion propia de tablero y cursor detectar la casilla)
        // miTablero->tarjeta.animalSeleccionado = ___

    case BATALLA:

        // Aqui por ejemplo irira batalla->actualiza()
        break;

    case CREDITOS:

        if (!transicion.activo)
        creditos->actualizar(25);
        if (creditos->getFinalizado())
        {
            transicion.empieza();
            proximoEstado = MENU;
        }
        break;
    }

    if (transicion.activo) transicion.actualizar(dt);
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

        for (int j = 0; j < 2; j++)
            for (int i = 0; i < numeroAnimales; i++)
                misAnimales[i + j * numeroAnimales]->dibujar(motorGrafico);
         

        miTablero->cursor.dibujar(motorGrafico);

        //if(el cursor esta sobre un animal, funcion propia de tablero y cursor detectar la casilla)
        // en actualizar se determina que tarjeta se va a dibujar interiormente
        if(miTablero->cursor.posx > 150 && miTablero->cursor.posx <170) // ELIMINAR ESTA CONDICION
        miTablero->tarjeta.dibujar(motorGrafico);

        break;

    case BATALLA:
        
        break;

    case CREDITOS:

        creditos->dibujar(motorGrafico);
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

            case Selector::CREDITOS:
                creditos->reset();
                transicion.empieza();
                proximoEstado = CREDITOS;
                break;
            }

        }
        break;

        case TABLERO: // movimiento discreto en el tabler

        miTablero->moverCursor(key);
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

        miTablero->moverCursor(key);  
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
