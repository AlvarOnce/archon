#include "tarjetaID.h"
#include "renderizador.h"


void Tarjeta::dibujar(Renderizador* motor)
{
	motor->dibujarSprite("../assets/Sprites/tablero/tarjetasID.png", 128, 64, IZQ, posy, -5);
}