#include "dibujar.h"
#include "menu.h"
#include <string>
#include <iostream>
#include "math.h"

float angulo = 0;

void  mostrarMenu()
{

letra titulo[6];

//Dibujar("../assets/Sprites/Pruebas/Sprite-0003.png", 0, 0, -20,50,50);
//Dibujar("../assets/Sprites/Pruebas/Sprite-0004.png", 0, 0, -21, 50, 50);
//Dibujar("../assets/Sprites/Pruebas/Sprite-0005.png", 30, 30, -22, 50, 50);

	Dibujar("assets/Sprites/Pruebas/aaa1.png", 160/2, 90/2, 0, 160, 90); // fondo

	for (int i = 0; i < 6; i++)
	{
		titulo[i].altura = 55 + 10 + 5 * sin(angulo + i/2.0); // +10 porque ahora dibuja posiciones en el centro de imagen
		titulo[i].horiz = 18 * i + 9; // +9 porque ahora dibuja posiciones en el centro de imagen

		if (i == 0)   titulo[i].horiz--;

		const std::string ruta = std::string("assets/Sprites/menu/titulo") + std::to_string(i) + ".png";

		Dibujar(ruta.c_str(), 26 + titulo[i].horiz, titulo[i].altura, -1, 18, 20);  // letras
	}

	Dibujar("assets/Sprites/menu/paloma.png", 28 + titulo[0].horiz - 4, titulo[0].altura + 19 - 6, -2, 8, 8); // paloma

	angulo += 0.05;
	if (angulo > 360)   angulo = 0;

	return;
}




