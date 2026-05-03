#include <iostream>
#include <stdlib.h>
#include "arena.h"
#include "juego.h"

#define numeroAnimales 9 // Por ahora crea 9 entidades

Juego::Juego() {

    estadoActual = MENU;
    proximoEstado = MENU;

    miMenu = new Menu();
    miArena = new Arena();
    motorGrafico = new Renderizador();
    creditos = new Creditos();

    for (int j = 0; j < 2; j++) // Creación de 18 instancias de animal, guardadas en la colección de animales
        for (int i = 0; i < numeroAnimales; i++)
        {
            int tipoAnimal = ((j * (i + 1)) % 3) + j;
            if (tipoAnimal == 0)
                misAnimales[i + j * numeroAnimales] = new Gallina(-44 * j - 15 * (numeroAnimales - i) + 11, 36 + (22 * i) + 11, -3 - 0.01 * i - 0.08 * j, 20, 174);
            else if (tipoAnimal == 1)
                misAnimales[i + j * numeroAnimales] = new Cerdo(-44 * j - 15 * (numeroAnimales - i) + 11, 36 + (22 * i) + 11, -3 - 0.01 * i - 0.08 * j, 20, 152);
            else if (tipoAnimal == 2)
                misAnimales[i + j * numeroAnimales] = new Cabra(-44 * j - 15 * (numeroAnimales - i) + 11, 36 + (22 * i) + 11, -3 - 0.01 * i - 0.08 * j, 20, 152);
            else if (tipoAnimal == 3)
                misAnimales[i + j * numeroAnimales] = new Oveja(-44 * j - 15 * (numeroAnimales - i) + 11, 36 + (22 * i) + 11, -3 - 0.01 * i - 0.08 * j, 20, 152);
        }
    miTablero = new Tablero(misAnimales);

}

Juego::~Juego() {
    delete miMenu;
    delete miTablero;
    delete miArena;
    delete motorGrafico;
	delete creditos;
    for (int i = 0; i < 2 * numeroAnimales; i++)
		delete misAnimales[i];
}

void Juego::actualizarLogica(float dt) {
    // FASE 1: matemáticas, colisiones y reglas del juego

    switch (estadoActual) {

    case MENU:
       
        miMenu->actualizar(dt);

        break;

    case TABLERO:

		miTablero->actualizar(dt);
        break;
    
    case BATALLA:

        miArena->actualizar(dt);
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

        break;

    case BATALLA:
        miArena->dibujar(); // @Alvaro to @David: falta el motor gráfico de la arena 
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

		case TABLERO: // movimiento discreto en el tablero, no hace falta procesar la tecla al levantarla, el movimiento se hace una vez al pulsar y ya está
         if (key == 'w' || key == 'W') miTablero->recibirMovimiento(0, 0, 1); // miTablero->recibirMovimiento(jugador, dx, dy);
         if (key == 's' || key == 'S') miTablero->recibirMovimiento(0, 0, -1);
         if (key == 'a' || key == 'A') miTablero->recibirMovimiento(0, -1, 0);
         if (key == 'd' || key == 'D') miTablero->recibirMovimiento(0, 1, 0);
         if (key == '.') miTablero->seleccionarPieza();
        break;

		case BATALLA: // movimiento continuo en la batalla, se procesa al pulsar la tecla y al levantarla, hay movimiento mientras se mantenga pulsada la tecla
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

        if (key == 'w' || key == 'W') miTablero->recibirMovimiento(0, 0, 1); // miTablero->recibirMovimiento(jugador, dx, dy);
        if (key == 's' || key == 'S') miTablero->recibirMovimiento(0, 0, -1);
        if (key == 'a' || key == 'A') miTablero->recibirMovimiento(0, -1, 0);
        if (key == 'd' || key == 'D') miTablero->recibirMovimiento(0, 1, 0);
        if (key == '.') miTablero->seleccionarPieza();
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
