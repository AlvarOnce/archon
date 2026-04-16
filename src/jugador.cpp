#include "jugador.h"

// CONSTRUCTOR: Usamos la 'Lista de Inicialización' (los dos puntos ':') 
// para construir el objeto 'miCursor' antes de entrar a las llaves. 
// Es la forma más optimizada de C++ para el patrón RAII.
Jugador::Jugador(int id, int bandoAsignado, int filaInicio, int colInicio, float xPixel, float yPixel)
    : miCursor(xPixel, yPixel, id) // Nace el cursor inyectándole sus datos
{
    idJugador = id;
    bando = bandoAsignado;
    filaCursor = filaInicio;
    colCursor = colInicio;

    // CRÍTICO: El jugador nace con las manos vacías. 
    // Evita crashes al arrancar el juego.
    piezaSeleccionada = nullptr;
    filaPiezaVirtual = -1;
    colPiezaVirtual = -1;
}

void Jugador::moverCursorVacio(int deltaFila, int deltaCol) {
    int nuevaFila = filaCursor + deltaFila;
    int nuevaCol = colCursor + deltaCol;

    if (nuevaFila >= 0 && nuevaFila < 9 && nuevaCol >= 0 && nuevaCol < 9) {
        filaCursor = nuevaFila;
        colCursor = nuevaCol;
        // Le pasamos deltaCol (X) y deltaFila (Y) al cursor para que mueva sus píxeles
        miCursor.mover(deltaCol, deltaFila);
    }
}

// ¡LA NUEVA FASE! Movemos las coordenadas virtuales de la pieza
void Jugador::moverPiezaVirtual(int deltaFila, int deltaCol) {
    int nuevaFila = filaPiezaVirtual + deltaFila;
    int nuevaCol = colPiezaVirtual + deltaCol;

    // El jugador no deja que su pieza se salga del tablero 9x9
    if (nuevaFila >= 0 && nuevaFila < 9 && nuevaCol >= 0 && nuevaCol < 9) {
        filaPiezaVirtual = nuevaFila;
        colPiezaVirtual = nuevaCol;
    }
}

void Jugador::dibujarCursorVacio(Renderizador* motor) {
    miCursor.dibujar(motor);
}

void Jugador::dibujarPiezaFlotando(Renderizador* motor) {
    // Doble seguridad: Solo dibujamos si realmente tenemos algo agarrado
    if (piezaSeleccionada != nullptr) {
        // Calculamos dónde pintarla en base a sus coordenadas "virtuales"
        // (141 y 36 son los X_INICIO e Y_INICIO de vuestro Tablero)
        float xPixel = 141.0f + (colPiezaVirtual * 22.0f) + 11.0f;
        float yPixel = 36.0f + (filaPiezaVirtual * 22.0f) + 11.0f;

        // Invocamos la función virtual de polimorfismo
        piezaSeleccionada->dibujarEnCoordenadas(motor, xPixel, yPixel);
    }
}