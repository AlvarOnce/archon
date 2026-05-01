#pragma once
#include "animal.h"

class Cerdo : public Animal {

public:


	Cerdo(float posx, float posy, float capa, int vida) : Animal(posx, posy, capa, vida) {

		max_casillas_movidas_ = 5;
		setState(0, 0);

	}

	void actualizar(float dt) override;
	void dibujar(Renderizador* motor) override;
};