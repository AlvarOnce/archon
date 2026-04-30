#include "cabra.h"

void Cabra::dibujar(Renderizador* motor) 
{
	motor->dibujarSprite("../assets/Sprites/cabra/cabraSpritesheet.png", 256, 64, posx_, posy_, capaz_, 2, 8, frameActualX_, frameActualY_);
}

void Cabra::actualizar(float dt)
{
	Animal::actualizar(dt);
	// actualizar posicion
	if (posx_ < (480 - 198) / 2 + 11) posx_++;		//posx_ < 152, no se porque lo han puesto así


	//actualizar animacion
	nFrames = 5;
	if (posx_ < (480 - 198) / 2 + 11)
	animar(dt);

	else
		setState(0,0); 
}