#include "cerdo.h"

void Cerdo::dibujar(Renderizador* motor)
{
	motor->dibujarSprite("../assets/Sprites/cerdo/cerdoSpritesheet.png", 256, 128, posx_, posy_, capaz_, 4, 8, frameActualX_, frameActualY_);
}

void Cerdo::actualizar(float dt)
{
	Animal::actualizar(dt);
	
	setState(0, 0); 
}