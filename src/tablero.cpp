#include "tablero.h"

Tablero::Tablero()
{
    inicializarTablero();
}

Tablero::~Tablero()
{

}

void Tablero::inicializarTablero() // iniclizaiamos el Tablero vacio, es decir, creamos la matriz pero no le decimos todavia si hay figuras o no en las casillas
{
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            casillas[i][j] = nullptr;

            if ((i + j) % 2 == 0)
            {
                color_casilla[i][j] = CASILLA_LUZ; // como ya estan creadas las celdas de la matriz, ahora le decimos a cada celda que es, si es luz o oscuradad
            }
            else
            {
                color_casilla[i][j] = CASILLA_OSCURA;
            }
        }
    }

    turno_actual = BANDO_LUZ; // incia el turno el bando de luz

    posicion_fila_cursor_actual_j1 = 0; posicion_columna_cursor_actual_j1 = 0;
    posicion_fila_cursor_actual_j2 = 8; posicion_columna_cursor_actual_j2 = 8;
    hay_pieza_seleccionada_j1 = false; // están en false porque, si hemos iniciado el juego, pero como en el archon, no inicias el juego con una pieza ya seleccionada, dejas qeu el juegador escoga qeu figura quiere escoger
    hay_pieza_seleccionada_j2 = false;

}

void Tablero::dibujarTablero(Renderizador* motor){

    // imagen de fondo del tablero
    motor->dibujarSprite("../assets/Sprites/tablero y escenario/tableroOficial.png", 480, 270, 480/2, 270/2, 0);

    // recorrer la matriz para dibujar casillas de poder y animales
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            int x = X_INICIO + j * TAMANO_CASILLA;
            int y = Y_INICIO + i * TAMANO_CASILLA;

            if (esPuntoDePoder(i, j))
            {
                // motor->dibujarSprite("../assets/Sprites/puntopoder.png", [...] )
            }

            if (casillas[i][j] != nullptr)
            {
                // casillas[i][j]->dibujar(motor); 
                // la funcion dibujar debe estar dentro de animal.h, porque aqui le decimos que nos dibuje en la casilla el animal
            }
        }
    }

    // dibujar los cursores
    //float cursor1X = X_INICIO + (posicion_columna_cursor_actual_j1 * TAMANO_CASILLA) + 11.0f;
    //float cursor1Y = Y_INICIO + (posicion_fila_cursor_actual_j1 * TAMANO_CASILLA) + 11.0f;
    //motor->dibujarSprite("../assets/Sprites/cursorJ1.png", 22, 22, cursor1X, cursor1Y, -1.0f);

    //float cursor2X = X_INICIO + (posicion_columna_cursor_actual_j2 * TAMANO_CASILLA) + 11.0f;
    //float cursor2Y = Y_INICIO + (posicion_fila_cursor_actual_j2 * TAMANO_CASILLA) + 11.0f;
    //motor->dibujarSprite("../assets/Sprites/cursorJ2.png", 22, 22, cursor2X, cursor2Y, -1.0f);

}

bool Tablero::obtenerCasillaEnLaPinchamos(int x_pantalla, int y_pantalla, int& fila, int& columna)
{
    // Comprobamos si el clic se ha ehcho dentro ddel tablero de juego
    if (x_pantalla < X_INICIO || x_pantalla >= X_INICIO + COLUMNAS * TAMANO_CASILLA)
    {
        return false;
    }
    if (y_pantalla < Y_INICIO || y_pantalla >= Y_INICIO + FILAS * TAMANO_CASILLA)
    {
        return false;
    }

    columna = (x_pantalla - X_INICIO) / TAMANO_CASILLA; // con esto sacas qeu columna de la matriz has clickeado
    fila = (y_pantalla - Y_INICIO) / TAMANO_CASILLA; // lo mismo qeu la linea anterior pero esta vez con las filas

    return true;
}

void Tablero::colocarPieza(int fila, int columna, Animal* pieza)
{
    casillas[fila][columna] = pieza;
}

void Tablero::eliminarPieza(int fila, int columna)
{
    casillas[fila][columna] = nullptr;
}

Animal* Tablero::identificarPieza(int fila, int Columna) //decir que pieza hay en cada casilla
{
    return casillas[fila][Columna];
}

void Tablero::moverPieza(int fila_inicial, int columna_inicial, int fila_final, int columna_final)
{
    casillas[fila_final][columna_final] = casillas[fila_inicial][columna_inicial];
    casillas[fila_inicial][columna_inicial] = nullptr;
}

bool Tablero::comprobarCasillaVacia(int fila, int Columna) //servira para saber si una casilla está vacía o no
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
    if (contador_turno == 8)//rotaba a los ocho turnos los colores de las casillas no?
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

//estas dos dunciones serviran para saber en la funcion, TieneVentaja, comprobar que la figura y casilla son del mismo bando por asi decirlo

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
    
    //if (!comprobarCasillaVacia(4, 4) && casillas[4][4]->SaberBando() == bando) puntos_de_poder_tomados++;//la funcion obtener bando prefiero que este dentro de Animal.h y .cpp
    //if (!comprobarCasillaVacia(0, 4) && casillas[0][4]->SaberBando() == bando) puntos_de_poder_tomados++;
    //if (!comprobarCasillaVacia(8, 4) && casillas[8][4]->SaberBando() == bando) puntos_de_poder_tomados++;
    //if (!comprobarCasillaVacia(4, 0) && casillas[4][0]->SaberBando() == bando) puntos_de_poder_tomados++;
    //if (!comprobarCasillaVacia(4, 8) && casillas[4][8]->SaberBando() == bando) puntos_de_poder_tomados++;

    return puntos_de_poder_tomados;
}

bool Tablero::verificarVictoria(int bando){
    if (puntosDePoderControlados(bando) == 5) return true;

    int rival = (bando == BANDO_LUZ) ? BANDO_OSCURIDAD : BANDO_LUZ;
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            //if (Casillas[i][j] != nullptr && Casillas[i][j]->SaberBando() == Rival)
            {
                //return false;
            }
        }
    }
    return true;
}

bool Tablero::tengoVentaja(int fila, int columna, int bando){
    if (bando == BANDO_LUZ && color_casilla[fila][columna] == CASILLA_LUZ)
    {
        return true;
    }
    if (bando == BANDO_OSCURIDAD && color_casilla[fila][columna] == CASILLA_OSCURA)
    {
        return false;
    }
} 

void Tablero::moverCursorJ1(int fila_aumentada, int columna_aumentada)
{
    // sumamos el delta a la posicion actual y comprobamos que no salga del tablero
    int nueva_fila_cursor_seleccionada = posicion_fila_cursor_actual_j1 + fila_aumentada;
    int nueva_columna_cursor_seleccionada = posicion_columna_cursor_actual_j1 + columna_aumentada;

    if (nueva_fila_cursor_seleccionada >= 0 && nueva_fila_cursor_seleccionada < FILAS && nueva_columna_cursor_seleccionada >= 0 && nueva_columna_cursor_seleccionada < COLUMNAS)
    {
        posicion_fila_cursor_actual_j1 = nueva_fila_cursor_seleccionada;
        posicion_columna_cursor_actual_j1 = nueva_columna_cursor_seleccionada;
    }
}

void Tablero::moverCursorJ2(int fila_aumentada, int columna_aumentada)
{
    // sumamos el delta a la posicion actual y comprobamos que no salga del tablero
    int nueva_fila_cursor_seleccionada = posicion_fila_cursor_actual_j2 + fila_aumentada;
    int nueva_columna_cursor_seleccionada = posicion_columna_cursor_actual_j2 + columna_aumentada;

    if (nueva_fila_cursor_seleccionada >= 0 && nueva_fila_cursor_seleccionada < FILAS && nueva_columna_cursor_seleccionada >= 0 && nueva_columna_cursor_seleccionada < COLUMNAS)
    {
        posicion_fila_cursor_actual_j2 = nueva_fila_cursor_seleccionada;
        posicion_columna_cursor_actual_j2 = nueva_columna_cursor_seleccionada;
    }
}

void Tablero::seleccionarCasillaJ1()
{
    if (turno_actual != BANDO_LUZ) return; //para evitar que el juegador del bando de luz pueda emplear un turno que no le corresponde

    if (!hay_pieza_seleccionada_j1)
    {
        // si no hay pieza seleccionada, intentamos seleccionar la del cursor
        if (!comprobarCasillaVacia(posicion_fila_cursor_actual_j1, posicion_columna_cursor_actual_j1))
        {
            fila_seleccionada_j1 = posicion_fila_cursor_actual_j1;
            columna_seleccionada_j1 = posicion_columna_cursor_actual_j1;
            hay_pieza_seleccionada_j1 = true;
        }
    }
    else
    {
        // ya hay una pieza seleccionada, la movemos a donde esta el cursor
        moverPieza(fila_seleccionada_j1, columna_seleccionada_j1, posicion_fila_cursor_actual_j1, posicion_columna_cursor_actual_j1);
        hay_pieza_seleccionada_j1 = false;
        turno_actual = BANDO_OSCURIDAD;
    }
}

void Tablero::seleccionarCasillaJ2()
{
    if (turno_actual != BANDO_OSCURIDAD) return; //lo mismo que en SeleccionarCasillaJ1
    if (!hay_pieza_seleccionada_j2)
    {
        // si no hay pieza seleccionada, intentamos seleccionar la del cursor
        if (!comprobarCasillaVacia(posicion_fila_cursor_actual_j2, posicion_columna_cursor_actual_j2))
        {
            fila_seleccionada_j2 = posicion_fila_cursor_actual_j2;
            columna_seleccionada_j2 = posicion_columna_cursor_actual_j2;
            hay_pieza_seleccionada_j2 = true;
        }
    }
    else
    {
        // ya hay una pieza seleccionada, la movemos a donde esta el cursor
        moverPieza(fila_seleccionada_j2, columna_seleccionada_j2, posicion_fila_cursor_actual_j2, posicion_columna_cursor_actual_j2);
        hay_pieza_seleccionada_j2 = false;

        turno_actual = BANDO_LUZ; //le pasamos el turno al bandoLuz despues
        avanzarTurno();
    }
}