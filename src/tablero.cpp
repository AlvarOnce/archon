#include "tablero.h"

Tablero::Tablero(Animal** misAnimales)
{
    inicializarTablero();

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < FILAS; j++)
        {
            casillas[1-i][j] = misAnimales[j+(i*FILAS)];
        }
    }

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


}

void Tablero::dibujar(Renderizador* motor){

    // imagen de fondo del tablero
    motor->dibujarSprite("../assets/Sprites/tablero/tableroFondo.png", 512, 512, 480/2, 270/2, -1);
    motor->dibujarSprite("../assets/Sprites/tablero/tablero.png", 256, 256, 480 / 2, 270 / 2, -2);


    //// recorrer la matriz para dibujar casillas de poder y animales
    //for (int i = 0; i < FILAS; i++)
    //{
    //    for (int j = 0; j < COLUMNAS; j++)
    //    {
    //        int x = X_INICIO + j * TAMANO_CASILLA;
    //        int y = Y_INICIO + i * TAMANO_CASILLA;

    //        if (esPuntoDePoder(i, j))
    //        {
    //            // motor->dibujarSprite("../assets/Sprites/puntopoder.png", [...] )
    //        }

    //        if (casillas[i][j] != nullptr)
    //        {
    //            // casillas[i][j]->dibujar(motor); 
    //            // la funcion dibujar debe estar dentro de animal.h, porque aqui le decimos que nos dibuje en la casilla el animal
    //        }
    //    }
    //}

    // dibujar los cursores
    //float cursor1X = X_INICIO + (posicion_columna_cursor_actual_j1 * TAMANO_CASILLA) + 11.0f;
    //float cursor1Y = Y_INICIO + (posicion_fila_cursor_actual_j1 * TAMANO_CASILLA) + 11.0f;
    //motor->dibujarSprite("../assets/Sprites/cursorJ1.png", 22, 22, cursor1X, cursor1Y, -1.0f);

    //float cursor2X = X_INICIO + (posicion_columna_cursor_actual_j2 * TAMANO_CASILLA) + 11.0f;
    //float cursor2Y = Y_INICIO + (posicion_fila_cursor_actual_j2 * TAMANO_CASILLA) + 11.0f;
    //motor->dibujarSprite("../assets/Sprites/cursorJ2.png", 22, 22, cursor2X, cursor2Y, -1.0f);

}

void Tablero::moverCursor(int key)
{
    if (casillas[0][0]!= nullptr && casillas[0][0]->getIntroTablero()) return;
    if (hay_pieza_seleccionada_ == FALSE)
    {
        if (turno_actual == BANDO_LUZ)
        {
            if (key == 'w' || key == 'W')   cursor.mover(0, 1);
            if (key == 's' || key == 'S')   cursor.mover(0, -1);
            if (key == 'a' || key == 'A')   cursor.mover(-1, 0);
            if (key == 'd' || key == 'D')   cursor.mover(1, 0);     //la 'd' y la flecha izquierda las dos glut las lee como 100
            //std::cout << "posicion del cursor: " << cursor.columna << ", " << cursor.fila << std::endl;
			//std::cout << casillas[cursor.columna][cursor.fila] << std::endl; // esto es para ver si el cursor se mueve por la matriz, si el puntero es null o no
        }
        else if (turno_actual == BANDO_OSCURIDAD)
        {
            if (key == GLUT_KEY_UP)         cursor.mover(0, 1);
            if (key == GLUT_KEY_DOWN)       cursor.mover(0, -1);
            if (key == GLUT_KEY_LEFT)       cursor.mover(-1, 0);
            if (key == GLUT_KEY_RIGHT)      cursor.mover(1, 0);
        }
    }
    else 
    {
        if (animal_seleccionado_->getEnMovimiento()) return;

		bool movimiento_valido = false;
        if (key == 'w' || key == 'W')   movimiento_valido = animal_seleccionado_->mover(TABLERO, U);
        if (key == 's' || key == 'S')   movimiento_valido = animal_seleccionado_->mover(TABLERO, D);
        if (key == 'a' || key == 'A')   movimiento_valido = animal_seleccionado_->mover(TABLERO, L);
        if (key == 'd' || key == 'D')   movimiento_valido = animal_seleccionado_->mover(TABLERO, R);

        if (movimiento_valido) {
            if (key == 'w' || key == 'W') cursor.mover(0, 1);
            if (key == 's' || key == 'S') cursor.mover(0, -1);
            if (key == 'a' || key == 'A') cursor.mover(-1, 0);
            if (key == 'd' || key == 'D') cursor.mover(1, 0);
        }
    }
    if (key == '.') seleccionarPieza();
    
}

void Tablero::seleccionarPieza() {
    if (casillas[cursor.columna][cursor.fila] == nullptr && animal_seleccionado_ == nullptr) {

    }
    else if (casillas[cursor.columna][cursor.fila] != nullptr && animal_seleccionado_ == nullptr) {
        hay_pieza_seleccionada_ = !hay_pieza_seleccionada_;
        animal_seleccionado_ = casillas[cursor.columna][cursor.fila];
        casillas[cursor.columna][cursor.fila] = nullptr;
    }
    else if (casillas[cursor.columna][cursor.fila] == nullptr && animal_seleccionado_ != nullptr) {
        casillas[cursor.columna][cursor.fila] = animal_seleccionado_;
        hay_pieza_seleccionada_ = !hay_pieza_seleccionada_;
		animal_seleccionado_ = nullptr;
    }
    else if (casillas[cursor.columna][cursor.fila] != nullptr && animal_seleccionado_ != nullptr)
    {

    }
}
