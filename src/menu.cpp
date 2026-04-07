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
	tractor.timer = tractor.timer + dt;
	if (tractor.timer > tractor.msStep)
	{
		if (tractor.frameActualX < 1) tractor.frameActualX++;
		else                   tractor.frameActualX = 0;
		tractor.timer = tractor.timer - tractor.msStep;
	}

	for (auto& n : nube) // NUBES 
		if (n.posx <480) n.posx += 0.2;
		else n.posx = 0;

	if (paloma.posx < 0.15 * ancho + titulo[0].horiz) // PALOMA (Es posible hacer paloma.actualizar(dt) y llamar aquí)
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
		paloma.posy = 0.14444 * alto + titulo[0].altura; 
	}
}

void Menu::dibujar(Renderizador* motor)
{

	motor->dibujarSprite("../assets/Sprites/menu/fondo.png", 512, 512, ancho/2, alto/2, 0); // FONDO en posicion (ancho/2, alto/2)

	for (auto& n : nube) // NUBES
		motor->dibujarSprite("../assets/Sprites/menu/nube2.png", 512, 128, n.posx, n.posy, n.capa);

	motor->dibujarSprite("../assets/Sprites/menu/granerovallas.png", 512, 512, ancho / 2, alto / 2, -1.9); // GRANERO Y VALLAS

	for (int i = 0; i < 6; i++) // LETRAS
	{
		const std::string ruta = std::string("../assets/Sprites/menu/titulo") + std::to_string(i) + ".png";
		motor->dibujarSprite(ruta.c_str(), 64, 64, 0.1625 * ancho + titulo[i].horiz, titulo[i].altura, titulo[i].capa);
	}

	motor->dibujarSprite("../assets/Sprites/menu/opciones.png", 128, 128, 245, 103, -2.8); // OPCIONES
	motor->dibujarSprite("../assets/Sprites/menu/selector.png", 16, 16, 178, 140, -3.2); // SELECTOR

	motor->dibujarSprite("../assets/Sprites/menu/palomaSpritesheet.png", 128, 64, paloma.posx, paloma.posy, -3, 2, 4, paloma.frameActualX, paloma.frameActualY); // PALOMA
	motor->dibujarSprite("../assets/Sprites/menu/tractorSpritesheet.png", 512, 128, tractor.posx, tractor.posy, -5, 1, 2, tractor.frameActualX, tractor.frameActualY); // TRACTOR
	

}







