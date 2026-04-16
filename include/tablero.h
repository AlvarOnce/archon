#pragma once
#include "jugador.h"
#include "animal.h"  
#include "tarjetaID.h" 

const int BANDO_LUZ = 1;
const int BANDO_OSCURIDAD = 2;
const int CASILLA_LUZ = 1;
const int CASILLA_OSCURA = 2;

// Las dos fases del turno para la nueva mecánica
enum FaseTurno {
    NAVEGANDO,       // El cursor se mueve libre buscando una pieza
    MOVIENDO_PIEZA   // El cursor se queda atrás y controlas a la pieza voladora
};

class Tablero {

    Animal* casillas[9][9];
    int color_casilla[9][9];

    int turno_actual;
    int contador_turno = 0;

    /*
        Haremos que ColorCasilla sea como una bandera
        Casilla luz = 1
        Casilla Oscuridad = 2
    */

    static const int TAMANO_CASILLA = 22;

    static const int FILAS = 9;
    static const int COLUMNAS = 9;

    static const int X_INICIO = 141;
    static const int Y_INICIO = 36;

    // LA NUEVA ARQUITECTURA: El tablero tiene 2 jugadores y sabe en qué fase está
    Jugador* jugadores[2];
    FaseTurno fase_actual;

public:

    Tablero(); // Le indicamos, o como que avisamos al programa de que vamos a comenzar a ocupar memoria
    ~Tablero(); // Digamos que es como nuestro destructor, si la ejecutamos liberamos toda la memoria ocupada por nuestro tablero

    // INYECCIÓN Y CONTROLES MAESTROS
    void setJugadores(Jugador* p1, Jugador* p2) { jugadores[0] = p1; jugadores[1] = p2; }
    void recibirInputDireccion(int idJugador, int deltaFila, int deltaCol);
    void botonAccion(int idJugador);

    // LÓGICA DEL TABLERO ORIGINAL (Intacta)
    void inicializarTablero();

    void colocarPieza(int Fila, int Columna, Animal* Pieza);
    void eliminarPieza(int Fila, int Columna);
    Animal* identificarPieza(int Fila, int Columna); // sacamos que pieza hay en la casilla (x,y)
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

    void dibujar(Renderizador* motor);

    Tarjeta tarjeta;

    /*
        Colocación de nuestro tablero en nuestra pantalla
        tomando en cuenta que nuestro tablero es 480x270
        y viendo que nuestras casillas son de 22x22 píxeles
        X_incio=(480-[22x9])=(480-198)/2=141
        Y_incio=(270-[22x9])=(270-198)/2=36
        pd: dividimos entre dos para que cuando se dibuje el tablero este centrado en la ventana emergente.
    */
};