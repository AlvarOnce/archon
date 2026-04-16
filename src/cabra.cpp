#include "cabra.h"

void Cabra::actualizar(float dt)
{
	// actualizar posicion
	if (posx_ < (480 - 198) / 2 + 11) posx_++;

	//posx_ += velx_ * dt;
	// posy_ += vely_ * dt;

	//actualizar animacion

	if (posx_ < (480 - 198) / 2 + 11) //if (velx_ != 0 || vely_ != 0)
	{
		timer = timer + dt;
		if (timer > msStep)
		{
			if (frameActualX < 4) frameActualX++;
			else frameActualX = 0;
			timer = timer - msStep;
		}
	}
	else frameActualX = 0;
}

void Cabra::dibujar(Renderizador* motor)
{
	motor->dibujarSprite("../assets/Sprites/cabra/cabraSpritesheet.png", 
		256, 32, posx_, posy_, capa_, 1, 8, frameActualX, frameActualY);
}

void Cabra::dibujarEnCoordenadas(Renderizador* motor, float xPixel, float yPixel)
{
	motor->dibujarSprite("../assets/Sprites/cabra/cabraSpritesheet.png",
		256, 32, xPixel, yPixel, capa_, 1, 8, frameActualX, frameActualY);
}