#include "granjero.h"

void Granjero::dibujar(Renderizador* motor)
{
	motor->dibujarSprite("../assets/Sprites/cabra/cabraSpritesheet.png", 256, 32, posx_, posy_, capaz_, 1, 8, frameActualX_, frameActualY_);
}

void Granjero::actualizar(float dt)
{
	Animal::actualizar(dt);
	// actualizar posicion
	if (posx_ < (480 - 198) / 2 + 11) posx_++;


	//actualizar animacion
	nFrames = 5;
	if (posx_ < (480 - 198) / 2 + 11)
		animar(dt);

	else
		setState(0, 0);
}