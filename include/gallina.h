#pragma once
#include "animal.h"

class Gallina : public Animal {

public:


	Gallina(float posx, float posy, float capa, int vida) : Animal(posx, posy, capa, vida) {

		setState(0, 0);
	}

	void actualizar(float dt) override;
	void dibujar(Renderizador* motor) override;
};