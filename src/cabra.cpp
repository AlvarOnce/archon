#include "cabra.h"

void Cabra::dibujar(Renderizador* motor) 
{
	motor->dibujarSprite("../assets/Sprites/Pruebas/palomaVolando.png", 128, 64, posx_, posy_, -3, 2, 4, frameActualX, frameActualY);
}