#include "cursor.h"
#include "renderizador.h"

Cursor::Cursor(float x_inicial, float y_inicial, int id)
{
    posx = x_inicial;
    posy = y_inicial;
    idJugador = id;
}

void Cursor::mover(int x, int y)
{
    posx += 22 * x;
    posy += 22 * y;
}

void Cursor::dibujar(Renderizador* motor)
{
    if (idJugador == 0) {
        motor->dibujarSprite("../assets/Sprites/cursor.png", 22, 22, posx, posy, -5.0f); // Julián, cambia el color para cada cursor, gracias.
    }
    else {
        motor->dibujarSprite("../assets/Sprites/cursor.png", 22, 22, posx, posy, -5.0f);
    }
}