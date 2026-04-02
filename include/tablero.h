#pragma once
#include "animal.h"  

const int BandoLuz = 1;
const int BandoOscuridad = 2;
const int CasillaLuz = 1;
const int CasillaOscura = 2;

class Tablero {
public:
    Tablero();//Le indicamos, o como que avisamos al programa de que vamos a comenzar a ocupar memoria
    ~Tablero();//Digamos que es como nuestro destructor, si la ejecutamos liberamos toda la memoria ocupada por nuestro tablero

    int PosicionFilaCursorActualJ1;
    int PosicionColumnaCursorActualJ1;
    int PosicionFilaCursorActualJ2;
    int PosicionColumnaCursorActualJ2;

    void MoverCursorJ1(int FilaAumentada, int ColumnaAumentada);
    void MoverCursorJ2(int FilaAumentada, int ColumnaAumentada);
    void SeleccionarCasillaJ1();
    void SeleccionarCasillaJ2();

    void InicializarTablero();
    void DibujarTablero();
    bool ObtenerCasillaEnLaPinchamos(int XPantalla, int YPantalla, int& Fila, int& Columna);

    void ColocarPieza(int Fila, int Columna, Animal* Pieza);
    void EliminarPieza(int Fila, int Columna);
    Animal* IdentificarPieza(int Fila, int Columna);//sacamos que pieza hay en la casilla (x,y)
    void MoverPieza(int FilaInicial, int ColumnaInicial, int FilaFinal, int ColumnaFinal);

    bool ComprobarCasillaVacia(int Fila, int Columna);
    void AvanzarTurno();
    int ObtenerTurnoActual();

    bool EsCasillaLuz(int Fila, int Columna);
    bool EsCasillaOscuridad(int Fila, int Columna);
    bool EsPuntoDePoder(int Fila, int Columna);
    int PuntosDePoderControlados(int Bando);

    bool VerificarVictoria(int Bando);
    bool TengoVentaja(int Fila, int Columna, int Bando);

private:
    Animal* Casillas[9][9];
    int ColorCasilla[9][9];
    
    int TurnoActual;

    /*
        Haremos que ColorCasilla sea como una bandera
        Casilla luz = 1
        Casilla Oscuridad = 2
    */

    int FilaSeleccionadaJ1, ColumnaSeleccionadaJ1;
    int FilaSeleccionadaJ2, ColumnaSeleccionadaJ2;
    bool HayPiezaSeleccionadaJ1;
    bool HayPiezaSeleccionadaJ2;

    static const int TamanoCasilla = 22;

    static const int Filas = 9;
    static const int Columnas = 9;

    int ContadorTurno = 0;

    static const int XInicio = 141;
    static const int YInicio = 36;

    /*
        Colocación de neustro tablero en nuestra panatalla
        tomando en cuenta que nuestro tablero es 480x270
        y viendo que nuestras casillas son de 22x22 píxeles
        X_incio=(480-[22x9])=(480-198)/2=141
        Y_incio=(270-[22x9])=(270-198)/2=36
        pd:dividimos entre dos para que cuando se dibuje el tablero este centrado en la ventana emergente.
    */
}; 