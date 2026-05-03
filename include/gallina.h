#pragma once
#include "animal.h"

class Gallina : public Animal {

public:


	Gallina(float posx, float posy, float capa, int vida, float xinicial) : Animal(posx, posy, capa, vida, xinicial) {

		max_casillas_movidas_ = 2;
		nFrames = 8;
		setState(0, 0);
	}

	void dibujar(Renderizador* motor) override;
};