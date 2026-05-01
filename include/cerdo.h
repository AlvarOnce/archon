#pragma once
#include "animal.h"

class Cerdo : public Animal {

public:


	Cerdo(float posx, float posy, float capa, int vida, float xinicial) 
		: Animal(posx, posy, capa, vida, xinicial) {

		nFrames = 6;
		max_casillas_movidas_ = 5;
		setState(0, 0);

	}

	void actualizar(float dt) override;
	void dibujar(Renderizador* motor) override;
};