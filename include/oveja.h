#pragma once
#include "animal.h"

class Oveja : public Animal {

public:


	Oveja(float posx, float posy, float capa, int vida, float xinicial) : Animal(posx, posy, capa, vida, xinicial) {

		max_casillas_movidas_ = 10;
		nFrames = 5;
		setState(0, 0);
	}

	void actualizar(float dt) override;
	void dibujar(Renderizador* motor) override;
};