#pragma once
#include "animal.h"

class Cabra: public Animal {

public:


	Cabra(float posx, float posy, float capa, int vida, int equipo) : Animal(posx, posy, capa, vida, equipo) {

		frameActualX = 0;
	    frameActualY = 0;

	}	

	void actualizar(float dt) override;
	void dibujar(Renderizador* motor) override;
	void dibujarEnCoordenadas(Renderizador* motor, float xPixel, float yPixel) override;
};