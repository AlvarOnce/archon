#pragma once
#include "animal.h"

class Granjero : public Animal {

public:


	Granjero(float posx, float posy, float capa, int vida, float xinicial) 
		: Animal(posx, posy, capa, vida, xinicial) {

		nFrames = 5;
		setState(0, 0);

	}

	void actualizar(float dt) override;
	void dibujar(Renderizador* motor) override;
};