#include "cursor.h"
#include "renderizador.h"

void Cursor::mover(int x, int y)
{
	posx += 22*x;
	posy += 22*y;
	columna += x;
	fila += y;

}

void Cursor::dibujar(Renderizador* motor)
{
	motor->dibujarSprite("../assets/Sprites/tablero/cursor.png", 32, 32, posx, posy, -5);
}