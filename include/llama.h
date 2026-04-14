#pragma once
#include "animal.h"

class Llama : public Animal {

public:


	Llama(float posx, float posy, float capa, int vida) : Animal(posx, posy, capa, vida) {

		setState(0, 0);

	}

	void actualizar(float dt) override;
	void dibujar(Renderizador* motor) override;
};