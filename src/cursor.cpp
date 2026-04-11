#include "cursor.h"
#include "renderizador.h"

void Cursor::mover(int x, int y)
{
	posx += 22.0*x;
	posy += 22.0*y;

}

void Cursor::dibujar(Renderizador* motor)
{
	motor->dibujarSprite("../assets/Sprites/tablero/cursor.png", 32, 32, posx, posy, -5);
}