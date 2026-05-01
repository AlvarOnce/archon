#include "granjero.h"

void Granjero::dibujar(Renderizador* motor)
{
	motor->dibujarSprite("../assets/Sprites/cabra/cabraSpritesheet.png", 256, 32, posx_, posy_, capaz_, 1, 8, frameActualX_, frameActualY_);
}

void Granjero::actualizar(float dt)
{
	Animal::actualizar(dt);
	
	setState(0, 0);
}