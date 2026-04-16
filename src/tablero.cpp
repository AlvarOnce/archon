#include "tablero.h"

Tablero::Tablero()
{
    fase_actual = NAVEGANDO;
    inicializarTablero();
}

Tablero::~Tablero()
{

}

void Tablero::inicializarTablero() // inicializamos el Tablero vacio
{
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            casillas[i][j] = nullptr;

            if ((i + j) % 2 == 0)
            {
                color_casilla[i][j] = CASILLA_LUZ;
            }
            else
            {
                color_casilla[i][j] = CASILLA_OSCURA;
            }
        }
    }

    turno_actual = BANDO_LUZ; // inicia el turno el bando de luz

    // NOTA: Las posiciones iniciales del cursor ya no se declaran aquí.
    // Nacen directamente en Juego.cpp cuando se hace 'new Jugador(...)'.
    // Ahí le indicaremos las coordenadas del "Mago/Granjero".
}

void Tablero::recibirInputDireccion(int idJugador, int deltaFila, int deltaCol)
{
    Jugador* j = jugadores[idJugador];
    if (turno_actual != j->getBando()) return; // No es su turno

    if (fase_actual == NAVEGANDO) {
        // 1. Fase normal: Movemos el cursor buscando pieza
        j->moverCursorVacio(deltaFila, deltaCol);
    }
    else if (fase_actual == MOVIENDO_PIEZA) {
        // 2. Fase de agarre: El cursor azul/rojo se queda fijo, controlas a la pieza
        j->moverPiezaVirtual(deltaFila, deltaCol);
    }
}

void Tablero::botonAccion(int idJugador)
{
    Jugador* j = jugadores[idJugador];
    if (turno_actual != j->getBando()) return;

    if (fase_actual == NAVEGANDO)
    {
        // INTENTAR AGARRAR
        int f = j->getFilaCursor();
        int c = j->getColCursor();

        if (!comprobarCasillaVacia(f, c)) {
            Animal* piezaEnCasilla = casillas[f][c];

            // ¿Es mía la pieza? (Usamos obtenerBando que añadimos en Animal.h)
            if (piezaEnCasilla->obtenerBando() == j->getBando()) {
                j->agarrarPieza(piezaEnCasilla);

                // BORRAMOS TEMPORALMENTE la pieza de la matriz (así "vuela" y no se pinta doble)
                casillas[f][c] = nullptr;

                // CAMBIAMOS DE FASE
                fase_actual = MOVIENDO_PIEZA;
            }
        }
    }
    else if (fase_actual == MOVIENDO_PIEZA)
    {
        // INTENTAR SOLTAR EN LA CASILLA DESTINO
        int origenF = j->getFilaCursor(); // Dónde empezó (el cursor fijo)
        int origenC = j->getColCursor();
        int destF = j->getFilaPiezaVirtual(); // Dónde está la pieza voladora
        int destC = j->getColPiezaVirtual();

        Animal* piezaQueLlevo = j->getPieza();

        // 1. ¿He soltado la pieza en la misma casilla de la que la cogí? (Cancelar)
        if (destF == origenF && destC == origenC) {
            casillas[origenF][origenC] = piezaQueLlevo; // La devolvemos a la matriz
            j->soltarPieza();
            fase_actual = NAVEGANDO;
            return; // No pasamos turno, fue un error del jugador
        }

        // 2. ¿La casilla de destino está vacía?
        if (comprobarCasillaVacia(destF, destC)) {
            casillas[destF][destC] = piezaQueLlevo; // Aterriza
            j->soltarPieza();
            fase_actual = NAVEGANDO;

            // ¡MOVIMIENTO COMPLETADO! PASAMOS TURNO.
            turno_actual = (turno_actual == BANDO_LUZ) ? BANDO_OSCURIDAD : BANDO_LUZ;
            avanzarTurno();

            // Teletransportamos el cursor del jugador a donde aterrizó la pieza
            j->moverCursorVacio(destF - origenF, destC - origenC);
        }
        else {
            Animal* enemigo = casillas[destF][destC];
            if (enemigo->obtenerBando() != j->getBando()) {

                // ¡¡COMBATE!! 
                // Aquí en el futuro le diremos al Juego.cpp que cambie a estado BATALLA
                // dejaremos a los animales listos para pelear.

            }
        }
    }
}

void Tablero::dibujar(Renderizador* motor) {

    // 1. Imagen de fondo del tablero
    motor->dibujarSprite("../assets/Sprites/tablero/tableroFondo.png", 512, 512, 480 / 2, 270 / 2, -1);
    motor->dibujarSprite("../assets/Sprites/tablero/tablero.png", 256, 256, 480 / 2, 270 / 2, -2);

    // 2. Recorrer la matriz para dibujar casillas de poder y animales en reposo
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            // Calculamos el centro exacto de la casilla en píxeles (+11 para centrar en recuadro de 22)
            float xPixel = X_INICIO + j * TAMANO_CASILLA + 11.0f;
            float yPixel = Y_INICIO + i * TAMANO_CASILLA + 11.0f;

            if (esPuntoDePoder(i, j))
            {
                // motor->dibujarSprite("../assets/Sprites/puntopoder.png", [...] )
            }

            if (casillas[i][j] != nullptr)
            {
                // Invocamos el polimorfismo para que el animal se pinte centrado en su casilla
                casillas[i][j]->dibujarEnCoordenadas(motor, xPixel, yPixel);
            }
        }
    }

    // 3. Pintar los Cursores de los jugadores (El azul y el rojo)
    jugadores[0]->dibujarCursorVacio(motor);
    jugadores[1]->dibujarCursorVacio(motor);

    // 4. Si alguien tiene una pieza agarrada, pintarla la última (por encima de todo para que parezca que vuela)
    if (fase_actual == MOVIENDO_PIEZA) {
        if (turno_actual == BANDO_LUZ) jugadores[0]->dibujarPiezaFlotando(motor);
        else                           jugadores[1]->dibujarPiezaFlotando(motor);
    }
}

// -------------------------------------------------------------
// LÓGICA DE REGLAS Y MEMORIA (Se mantiene intacta la de David)
// -------------------------------------------------------------

void Tablero::colocarPieza(int fila, int columna, Animal* pieza)
{
    casillas[fila][columna] = pieza;
}

void Tablero::eliminarPieza(int fila, int columna)
{
    casillas[fila][columna] = nullptr;
}

Animal* Tablero::identificarPieza(int fila, int Columna)
{
    return casillas[fila][Columna];
}

void Tablero::moverPieza(int fila_inicial, int columna_inicial, int fila_final, int columna_final)
{
    casillas[fila_final][columna_final] = casillas[fila_inicial][columna_inicial];
    casillas[fila_inicial][columna_inicial] = nullptr;
}

bool Tablero::comprobarCasillaVacia(int fila, int Columna)
{
    return casillas[fila][Columna] == nullptr;
}

int Tablero::obtenerTurnoActual()
{
    return turno_actual;
}

void Tablero::avanzarTurno()
{
    contador_turno++;
    if (contador_turno == 8)
    {
        contador_turno = 0;
        for (int i = 0; i < FILAS; i++)
        {
            for (int j = 0; j < COLUMNAS; j++)
            {
                if (color_casilla[i][j] == CASILLA_LUZ)
                {
                    color_casilla[i][j] = CASILLA_OSCURA;
                }
                else
                {
                    color_casilla[i][j] = CASILLA_LUZ;
                }
            }
        }
    }
}

bool Tablero::esCasillaLuz(int fila, int columna)
{
    return color_casilla[fila][columna] == CASILLA_LUZ;
}

bool Tablero::esCasillaOscuridad(int fila, int columna)
{
    return color_casilla[fila][columna] == CASILLA_OSCURA;
}

bool Tablero::esPuntoDePoder(int fila, int columna)
{
    if (fila == 4 && columna == 4) return true;
    if (fila == 0 && columna == 4) return true;
    if (fila == 8 && columna == 4) return true;
    if (fila == 4 && columna == 0) return true;
    if (fila == 4 && columna == 8) return true;

    return false;
}

int Tablero::puntosDePoderControlados(int bando)
{
    int puntos_de_poder_tomados = 0;

    // Descomentado y arreglado usando la función obtenerBando() de Animal.h
    if (!comprobarCasillaVacia(4, 4) && casillas[4][4]->obtenerBando() == bando) puntos_de_poder_tomados++;
    if (!comprobarCasillaVacia(0, 4) && casillas[0][4]->obtenerBando() == bando) puntos_de_poder_tomados++;
    if (!comprobarCasillaVacia(8, 4) && casillas[8][4]->obtenerBando() == bando) puntos_de_poder_tomados++;
    if (!comprobarCasillaVacia(4, 0) && casillas[4][0]->obtenerBando() == bando) puntos_de_poder_tomados++;
    if (!comprobarCasillaVacia(4, 8) && casillas[4][8]->obtenerBando() == bando) puntos_de_poder_tomados++;

    return puntos_de_poder_tomados;
}

bool Tablero::verificarVictoria(int bando) {
    if (puntosDePoderControlados(bando) == 5) return true;

    int rival = (bando == BANDO_LUZ) ? BANDO_OSCURIDAD : BANDO_LUZ;
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            if (casillas[i][j] != nullptr && casillas[i][j]->obtenerBando() == rival)
            {
                return false;
            }
        }
    }
    return true;
}

bool Tablero::tengoVentaja(int fila, int columna, int bando) {
    if (bando == BANDO_LUZ && color_casilla[fila][columna] == CASILLA_LUZ)
    {
        return true;
    }
    if (bando == BANDO_OSCURIDAD && color_casilla[fila][columna] == CASILLA_OSCURA)
    {
        return false;
    }
    return false; // Añadido return de seguridad
}