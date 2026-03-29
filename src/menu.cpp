#include "menu.h"
#include <string>
#include <iostream>
#include "math.h"

void Menu::actualiza() 
{
	angulo += 0.05;
	if (angulo > 360) angulo = 0;
}

void Menu::dibuja(Renderizador* motor)
{
	motor->dibujarSprite("../assets/Sprites/menu/fondo.png", 160/2, 90/2, 0, 160, 90); // fondo

	for (int i = 0; i < 6; i++)
	{
		titulo[i].altura = 56 + 10 + 5 * sin(angulo + i/2.0); // +10 porque ahora dibuja posiciones en el centro de imagen
		titulo[i].horiz = 18 * i + 9; // +9 porque ahora dibuja posiciones en el centro de imagen

		if (i == 0)   titulo[i].horiz--;

		const std::string ruta = std::string("../assets/Sprites/menu/titulo") + std::to_string(i) + ".png";

		motor->dibujarSprite(ruta.c_str(), 26 + titulo[i].horiz, titulo[i].altura, -1, 18, 20);  // letras
	}

	motor->dibujarSprite("../assets/Sprites/menu/paloma.png", 28 + titulo[0].horiz - 4, titulo[0].altura + 19 - 6, -2, 8, 8); // paloma

	return;
}




