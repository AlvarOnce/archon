#include "menu.h"

#include <string>
#include <iostream>
#include "math.h"

void Menu::actualizar(float dt) 
{
	anguloLetras += 0.05; 
	if (anguloLetras > 360) anguloLetras = 0; // LETRAS

	for (int i = 0; i < 6; i++) // LETRAS 
	{
		titulo[i].altura = 0.73333 * alto + 0.05555 * alto * sin(anguloLetras + i / 2.0); // Desplazamientos relativos a ancho y alto
		titulo[i].horiz = 0.05625 * ancho + 0.1125 * ancho * i;
		if (i == 0)  titulo[i].horiz -= 0.00625 * ancho; // Ajuste a la izquierda por ser la 'R' más grande
	}

	if (tractor.posx > -200) tractor.posx -= 0.8; // TRACTOR


	if (paloma.posx < 0.15 * ancho + titulo[0].horiz)
	{
		paloma.posx++;

			paloma.timer = paloma.timer + dt;
		if (paloma.timer > paloma.msStep)
		{
			if (paloma.frameActualX < 3) paloma.frameActualX++;
			else                   paloma.frameActualX = 0;
			paloma.timer = paloma.timer - paloma.msStep;
		}
	}
				
	else

	{
		paloma.frameActualX = 0;
		paloma.frameActualY = 0;
		paloma.posx = 0.15 * ancho + titulo[0].horiz;
		paloma.posy = 0.14444 * alto + titulo[0].altura; // PALOMA (Es posible hacer paloma.actualizar(dt) y llamar aquí)

	}

}

void Menu::dibujar(Renderizador* motor)
{

	motor->dibujarSprite("../assets/Sprites/menu/fondo.png", ancho, alto, ancho/2, alto/2, 0); // FONDO de tamaño (ancho,alto) en posicion (0,0) capa (0)

	for (int i = 0; i < 6; i++)
	{
		const std::string ruta = std::string("../assets/Sprites/menu/titulo") + std::to_string(i) + ".png";
		motor->dibujarSprite(ruta.c_str(), 54, 60, 0.1625*ancho + titulo[i].horiz, titulo[i].altura, -1);  // LETRAS
	}

	motor->dibujarSprite("../assets/Sprites/Pruebas/palomaVolando.png", 128, 64, paloma.posx, paloma.posy, -2,2,4, paloma.frameActualX, paloma.frameActualY); // PALOMA
	motor->dibujarSprite("../assets/Sprites/menu/tractorSpritesheet.png", 256, 128, tractor.posx, tractor.posy, -2); // TRACTOR

}







