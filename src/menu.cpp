#include "menu.h"

#include <string>
#include <iostream>
#include "math.h"
#include "renderizador.h"

void Menu::actualiza() 
{
	angulo += 0.05;
	if (angulo > 360) angulo = 0;
}

void Menu::dibuja(Renderizador* motor, double ancho, double alto)
{
	motor->dibujarSprite("../assets/Sprites/menu/fondo.png", ancho/2, alto/2, 0, ancho, alto); // fondo en posición centro (ancho/2,alto/2,0) de tamaño (ancho,alto)

	for (int i = 0; i < 6; i++)
	{
		titulo[i].altura = 0.73333*alto + 0.05555*alto * sin(angulo + i/2.0); // Desplazamientos relativos a ancho y alto
		titulo[i].horiz = 0.05625*ancho + 0.1125*ancho * i;

		if (i == 0)  titulo[i].horiz -= 0.00625*ancho; // Ajuste a la izquierda por ser la 'R' más grande

		const std::string ruta = std::string("../assets/Sprites/menu/titulo") + std::to_string(i) + ".png";

		motor->dibujarSprite(ruta.c_str(), 0.1625*ancho + titulo[i].horiz, titulo[i].altura, -1, 54, 60);  // letras
	}

	motor->dibujarSprite("../assets/Sprites/menu/paloma.png", 0.15*ancho + titulo[0].horiz, 0.14444*alto + titulo[0].altura, -2, 24, 24); // paloma

	return;
}




