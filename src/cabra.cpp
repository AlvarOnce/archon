#include "cabra.h"

void Cabra::dibujar(Renderizador* motor) 
{
	motor->dibujarSprite("../assets/Sprites/cabra/cabraSpritesheet.png", 256, 32, posx_, posy_, capaz_, 1, 8, frameActualX, frameActualY);
}

void Cabra::actualizar(float dt)
{
	// actualizar posicion
	if (posx_ < (480 - 198) / 2 + 11) posx_++;		//posx_ < 152, no se porque lo han puesto así


	//actualizar animacion

	if (posx_ < (480 - 198) / 2 + 11)
	{
		timer = timer + dt;
		if (timer > msStep)
		{
			if (frameActualX < 4) frameActualX++;
			else frameActualX = 0;
			timer = timer - msStep;
		}
	}
	else
		frameActualX = 0;
}