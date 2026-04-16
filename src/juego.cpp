#include <iostream>
#include <stdlib.h>

#include "juego.h"
#include "tablero.h"

#define numeroAnimales 9 // Por ahora crea 9 entidades

Juego::Juego() {

    estadoActual = MENU;
    // proximoEstado se inicializará cuando se pulse Jugar

    miMenu = new Menu();
    miTablero = new Tablero();
    //miArena = new Arena();
    motorGrafico = new Renderizador();

    // 1. INICIALIZAMOS LOS JUGADORES EN LAS CASILLAS DE LOS MAGOS
    // Mago Luz (Fila 0, Columna 4)
    float xLuz = 141.0f + (4 * 22.0f) + 11.0f;
    float yLuz = 36.0f + (0 * 22.0f) + 11.0f;
    jugadores[0] = new Jugador(0, BANDO_LUZ, 0, 4, xLuz, yLuz);

    // Mago Oscuridad (Fila 8, Columna 4)
    float xOsc = 141.0f + (4 * 22.0f) + 11.0f;
    float yOsc = 36.0f + (8 * 22.0f) + 11.0f;
    jugadores[1] = new Jugador(1, BANDO_OSCURIDAD, 8, 4, xOsc, yOsc);

    miTablero->setJugadores(jugadores[0], jugadores[1]); // Inyección de dependencias

    // 2. CREAMOS ANIMALES DE PRUEBA Y LOS METEMOS EN EL TABLERO PARA TESTEAR LA MECÁNICA
    // Cabra de la Luz
    misAnimales[0] = new Cabra(0, 0, -3.0f, 20, BANDO_LUZ);
    miTablero->colocarPieza(1, 4, misAnimales[0]); // La ponemos justo delante del Mago Luz

    // Cabra de la Oscuridad
    misAnimales[1] = new Cabra(0, 0, -3.0f, 20, BANDO_OSCURIDAD);
    miTablero->colocarPieza(7, 4, misAnimales[1]); // La ponemos justo delante del Mago Oscuro
}

Juego::~Juego() {
    delete miMenu;
    delete miTablero;
    //delete miArena;
    delete motorGrafico;
    delete jugadores[0];
    delete jugadores[1];

    // Aquí habría que hacer un for para deletear misAnimales[] para que no haya memory leaks
}

void Juego::actualizarLogica(float dt) {
    // FASE 1: matemáticas, colisiones y reglas del juego

    switch (estadoActual) {

    case MENU:
        miMenu->actualizar(25);
        break;

    case TABLERO:
        // El tablero gestiona la matriz, pero las animaciones internas de la Cabra (mover las patas)
        // se actualizan aquí temporalmente
        for (int i = 0; i < 2; i++) {
            if (misAnimales[i] != nullptr) misAnimales[i]->actualizar(25);
        }
        break;

    case BATALLA:
        // Aqui por ejemplo irira batalla->actualiza()
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
        // LA MAGIA DE LA POO: Esta sola línea dibuja la matriz, las cabras y los cursores
        miTablero->dibujar(motorGrafico);

        // Tarjeta ID provisional
        if (miTablero->tarjeta.animalSeleccionado != nullptr)
            miTablero->tarjeta.dibujar(motorGrafico);

        break;

    case BATALLA:
        break;
    }

    if (transicion.activo) { transicion.dibujar(motorGrafico); }
}

// -------------------------------------------------------------
// CONTROLES
// -------------------------------------------------------------

void Juego::procesarTeclaPresionada(unsigned char key)
{
    if (key == 27) exit(0);

    // Bloqueamos el input si la pantalla está fundida en negro
    if (transicion.activo) return;

    switch (estadoActual) {

    case MENU:
        if (key == 13) { // Intro
            switch (miMenu->getOpcionActual()) {
            case Selector::JUGAR:
                transicion.empieza();
                proximoEstado = TABLERO;
                break;
            }
        }
        break;

    case TABLERO:
        // Jugador 1 (WASD)
        if (key == 'w' || key == 'W') miTablero->recibirInputDireccion(0, 1, 0); // Fila +1
        if (key == 's' || key == 'S') miTablero->recibirInputDireccion(0, -1, 0); // Fila -1
        if (key == 'a' || key == 'A') miTablero->recibirInputDireccion(0, 0, -1); // Col -1
        if (key == 'd' || key == 'D') miTablero->recibirInputDireccion(0, 0, 1);  // Col +1

        // El Espacio (' ') para agarrar/soltar del J1
        if (key == ' ') miTablero->botonAccion(0);

        // El Punto ('.') para agarrar/soltar del J2 (ASCII normal, va aquí)
        if (key == '.') miTablero->botonAccion(1);
        break;

    case BATALLA:
        break;
    }
}

void Juego::procesarTeclaLevantada(unsigned char key)
{
    switch (estadoActual) {
    case TABLERO:
        break;
    case BATALLA:
        break;
    }
}

void Juego::procesarTeclaEspecialPresionada(int key)
{
    if (transicion.activo) return; // Bloqueo de input

    switch (estadoActual) {
    case MENU:
        if (key == GLUT_KEY_UP) miMenu->moverSelector(-1);
        if (key == GLUT_KEY_DOWN) miMenu->moverSelector(1);
        break;

    case TABLERO:
        // Jugador 2 (Flechas)
        if (key == GLUT_KEY_UP)    miTablero->recibirInputDireccion(1, 1, 0);
        if (key == GLUT_KEY_DOWN)  miTablero->recibirInputDireccion(1, -1, 0);
        if (key == GLUT_KEY_LEFT)  miTablero->recibirInputDireccion(1, 0, -1);
        if (key == GLUT_KEY_RIGHT) miTablero->recibirInputDireccion(1, 0, 1);

        // ¡NOTA! La tecla de acción del J2 (el '.') la hemos movido a la función de arriba 
        // porque es una tecla ASCII normal, no una tecla especial de GLUT.
        break;

    case BATALLA:
        break;
    }
}

void Juego::procesarTeclaEspecialLevantada(int key)
{
    switch (estadoActual) {
    case TABLERO:
        break;
    case BATALLA:
        break;
    }
}