#pragma once
#include "animal.h"  

const int BANDO_LUZ = 1;
const int BANDO_OSCURIDAD = 2;
const int CASILLA_LUZ = 1;
const int CASILLA_OSCURA = 2;

class Tablero {
public:
    Tablero();//Le indicamos, o como que avisamos al programa de que vamos a comenzar a ocupar memoria
    ~Tablero();//Digamos que es como nuestro destructor, si la ejecutamos liberamos toda la memoria ocupada por nuestro tablero

    int posicion_fila_cursor_actual_j1;
    int posicion_columna_cursor_actual_j1;
    int posicion_fila_cursor_actual_j2;
    int posicion_columna_cursor_actual_j2;

    void moverCursorJ1(int FilaAumentada, int ColumnaAumentada);
    void moverCursorJ2(int FilaAumentada, int ColumnaAumentada);
    void seleccionarCasillaJ1();
    void seleccionarCasillaJ2();

    void inicializarTablero();
    void dibujarTablero();
    bool obtenerCasillaEnLaPinchamos(int XPantalla, int YPantalla, int& Fila, int& Columna);

    void colocarPieza(int Fila, int Columna, Animal* Pieza);
    void eliminarPieza(int Fila, int Columna);
    Animal* identificarPieza(int Fila, int Columna);//sacamos que pieza hay en la casilla (x,y)
    void moverPieza(int FilaInicial, int ColumnaInicial, int FilaFinal, int ColumnaFinal);

    bool comprobarCasillaVacia(int Fila, int Columna);
    void avanzarTurno();
    int obtenerTurnoActual();

    bool esCasillaLuz(int Fila, int Columna);
    bool esCasillaOscuridad(int Fila, int Columna);
    bool esPuntoDePoder(int Fila, int Columna);
    int puntosDePoderControlados(int Bando);

    bool verificarVictoria(int Bando);
    bool tengoVentaja(int Fila, int Columna, int Bando);

private:
    Animal* casillas[9][9];
    int color_casilla[9][9];
    
    int turno_actual;

    /*
        Haremos que ColorCasilla sea como una bandera
        Casilla luz = 1
        Casilla Oscuridad = 2
    */

    int fila_seleccionada_j1, columna_seleccionada_j1;
    int fila_seleccionada_j2, columna_seleccionada_j2;
    bool hay_pieza_seleccionada_j1;
    bool hay_pieza_seleccionada_j2;

    static const int TAMANO_CASILLA = 22;

    static const int FILAS = 9;
    static const int COLUMNAS = 9;

    int contador_turno = 0;

    static const int X_INICIO = 141;
    static const int Y_INICIO = 36;

    /*
        Colocación de neustro tablero en nuestra panatalla
        tomando en cuenta que nuestro tablero es 480x270
        y viendo que nuestras casillas son de 22x22 píxeles
        X_incio=(480-[22x9])=(480-198)/2=141
        Y_incio=(270-[22x9])=(270-198)/2=36
        pd:dividimos entre dos para que cuando se dibuje el tablero este centrado en la ventana emergente.
    */
}; 