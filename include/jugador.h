#pragma once
#include "cursor.h"
#include "animal.h"

class Jugador {
private:
    int idJugador;
    int bando;

    // El Cursor de Navegación
    int filaCursor;
    int colCursor;
    Cursor miCursor; // Objeto visual encapsulado

    // La Pieza Agarrada (Para la Fase 2 del turno)
    Animal* piezaSeleccionada;
    int filaPiezaVirtual; // Dónde está la pieza "volando" antes de soltarla
    int colPiezaVirtual;

public:
    Jugador(int id, int bandoAsignado, int filaInicio, int colInicio, float xPixel, float yPixel);

    // Para la fase NAVEGANDO
    void moverCursorVacio(int deltaFila, int deltaCol);
    void dibujarCursorVacio(Renderizador* motor);

    // Para la fase MOVIENDO_PIEZA
    void moverPiezaVirtual(int deltaFila, int deltaCol);
    void dibujarPiezaFlotando(Renderizador* motor);

    // Getters y Setters
    int getBando() { return bando; }
    int getFilaCursor() { return filaCursor; }
    int getColCursor() { return colCursor; }

    int getFilaPiezaVirtual() { return filaPiezaVirtual; }
    int getColPiezaVirtual() { return colPiezaVirtual; }

    Animal* getPieza() { return piezaSeleccionada; }
    bool tienePiezaAgarrada() { return piezaSeleccionada != nullptr; } // Función helper muy útil

    void agarrarPieza(Animal* p) {
        piezaSeleccionada = p;
        filaPiezaVirtual = filaCursor; // La pieza empieza donde está el cursor
        colPiezaVirtual = colCursor;
    }

    void soltarPieza() {
        piezaSeleccionada = nullptr; // Al soltarla, volvemos a la seguridad
    }
};