#include "Tablero.h"

Tablero::Tablero()
{
    InicializarTablero();
}

Tablero::~Tablero()
{

}

void Tablero::InicializarTablero()//Importante, iniclizaiamos el Tablero vacio, es decir, creamos la matriz pero no le decimos todavia si hay figuras o no en las casillas
{
    for (int i = 0; i < Filas; i++)
    {
        for (int j = 0; j < Columnas; j++)
        {
            Casillas[i][j] = nullptr;

            if ((i + j) % 2 == 0)
            {
                ColorCasilla[i][j] = CasillaLuz;//como ya estan creadas las celdas de la matriz, ahora le decimos a cada celda que es, si es luz o oscuradad
            }
            else
            {
                ColorCasilla[i][j] = CasillaOscura;
            }
        }
    }
}

void Tablero::DibujarTablero()
{
    for (int i = 0; i < Filas; i++)
    {
        for (int j = 0; j < Columnas; j++)
        {
            int X = XInicio + j * TamanoCasilla;
            int Y = YInicio + i * TamanoCasilla;

            if (EsPuntoDePoder(i, j))
            {
                //Dibujar con la libreria freglut supongo, un simbolo qeu indique que es una casilla de poder
            }

            if (Casillas[i][j] != nullptr)
            {
                Casillas[i][j]->Dibujar(X, Y);//la funcion dibujar debe estar dentro de animal.h, porque aqui le decimos que nos dibuje en la casilla el animal
            }
        }
    }
}

bool Tablero::ObtenerCasillaEnLaPinchamos(int XPantalla, int YPantalla, int& Fila, int& Columna)
{
    // Comprobamos si el clic se ha ehcho dentro ddel tablero de juego
    if (XPantalla < XInicio || XPantalla >= XInicio + Columnas * TamanoCasilla)
    {
        return false;
    }
    if (YPantalla < YInicio || YPantalla >= YInicio + Filas * TamanoCasilla)
    {
        return false;
    }

    Columna = (XPantalla - XInicio) / TamanoCasilla;//con esto sacas qeu columna de la matriz has clickeado
    Fila = (YPantalla - YInicio) / TamanoCasilla;//lo mismo qeu la linea anterior pero esta vez con las filas

    return true;
}

void Tablero::ColocarPieza(int Fila, int Columna, Animal* Pieza)
{
    Casillas[Fila][Columna] = Pieza;
}

void Tablero::EliminarPieza(int Fila, int Columna)
{
    Casillas[Fila][Columna] = nullptr;
}

Animal* Tablero::IdentificarPieza(int Fila, int Columna) //decir que pieza hay en cada casilla
{
    return Casillas[Fila][Columna];
}

void Tablero::MoverPieza(int FilaInicial, int ColumnaInicial, int FilaFinal, int ColumnaFinal)
{
    Casillas[FilaFinal][ColumnaFinal] = Casillas[FilaInicial][ColumnaInicial];
    Casillas[FilaInicial][ColumnaInicial] = nullptr;
}

bool Tablero::ComprobarCasillaVacia(int Fila, int Columna) //servira para saber si una casilla está vacía o no
{
    return Casillas[Fila][Columna] == nullptr;
}

void Tablero::AvanzarTurno()
{
    ContadorTurno++;
    if (ContadorTurno == 8)//rotaba a los ocho turnos los colores de las casillas no?
    {
        ContadorTurno = 0;
        for (int i = 0; i < Filas; i++)
        {
            for (int j = 0; j < Columnas; j++)
            {
                if (ColorCasilla[i][j] == CasillaLuz)
                {
                    ColorCasilla[i][j] = CasillaOscura;
                }

                else
                {
                    ColorCasilla[i][j] = CasillaLuz;
                }
            }
        }
    }
}

bool Tablero::EsCasillaLuz(int Fila, int Columna)
{
    return ColorCasilla[Fila][Columna] == CasillaLuz;
}

bool Tablero::EsCasillaOscuridad(int Fila, int Columna)
{
    return ColorCasilla[Fila][Columna] == CasillaOscura;
}

//estas dos dunciones serviran para saber en la funcion, TieneVentaja, comprobar que la figura y casilla son del mismo bando por asi decirlo

bool Tablero::EsPuntoDePoder(int Fila, int Columna)
{
    if (Fila == 4 && Columna == 4) return true;
    if (Fila == 0 && Columna == 4) return true;
    if (Fila == 8 && Columna == 4) return true;
    if (Fila == 4 && Columna == 0) return true;
    if (Fila == 4 && Columna == 8) return true;

    return false;
}

int Tablero::PuntosDePoderControlados(int Bando)
{
    int PuntosDePoderTomados = 0;
    if (!ComprobarCasillaVacia(4, 4) && Casillas[4][4]->SaberBando() == Bando) PuntosDePoderTomados++;//la funcion obtener bando prefiero que este dentro de Animal.h y .cpp
    if (!ComprobarCasillaVacia(0, 4) && Casillas[0][4]->SaberBando() == Bando) PuntosDePoderTomados++;
    if (!ComprobarCasillaVacia(8, 4) && Casillas[8][4]->SaberBando() == Bando) PuntosDePoderTomados++;
    if (!ComprobarCasillaVacia(4, 0) && Casillas[4][0]->SaberBando() == Bando) PuntosDePoderTomados++;
    if (!ComprobarCasillaVacia(4, 8) && Casillas[4][8]->SaberBando() == Bando) PuntosDePoderTomados++;

    return PuntosDePoderTomados;
}

bool Tablero::VerificarVictoria(int Bando)
{
    if (PuntosDePoderControlados(Bando) == 5) return true;

    int Rival = (Bando == BandoLuz) ? BandoOscuridad : BandoLuz;
    for (int i = 0; i < Filas; i++)
    {
        for (int j = 0; j < Columnas; j++)
        {
            if (Casillas[i][j] != nullptr && Casillas[i][j]->SaberBando() == Rival)
            {
                return false;
            }    
        }
    }
    return true;
}

bool Tablero::TengoVentaja(int Fila, int Columna, int Bando)
{
    if (Bando == BandoLuz && ColorCasilla[Fila][Columna] == CasillaLuz)
    {
        return true;
    }
    if (Bando == BandoOscuridad && ColorCasilla[Fila][Columna] == CasillaOscura)
    {
        return false;
    }
}