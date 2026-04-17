#include "cerdo.h"

void Cerdo::dibujar(Renderizador* motor)
{
	motor->dibujarSprite("../assets/Sprites/cerdo/cerdoSpritesheet.png", 256, 128, posx_, posy_, capaz_, 4, 8, frameActualX_, frameActualY_);
}

void Cerdo::actualizar(float dt)
{
	// actualizar posicion
	if (posx_ < (480 - 198) / 2 + 11) posx_++;


	//actualizar animacion
	nFrames = 6;
	if (posx_ < (480 - 198) / 2 + 11)
		animar(dt);

	else
		setState(0, 0); 
}