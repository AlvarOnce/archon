#include "oveja.h"

void Oveja::dibujar(Renderizador* motor)
{
	motor->dibujarSprite("../assets/Sprites/oveja/ovejaSpritesheet.png", 256, 64, posx_, posy_, capaz_, 2, 8, frameActualX_, frameActualY_);
}

void Oveja::actualizar(float dt)
{
	// actualizar posicion
	if (posx_ < (480 - 198) / 2 + 11) posx_++;

	//actualizar animacion
	nFrames = 5;
	if (posx_ < (480 - 198) / 2 + 11)
		animar(dt);

	else
		setState(0, 0);
}