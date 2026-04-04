#pragma once
#include "animal.h"

class Cabra: public Animal {

public:

	// Dibujo y animación

	Cabra() {

		posx_ = 100;
		posy_ = 100;
		frameActualX = 0;
		frameActualY = 1;
		timer = 0;
		msStep = 100;

	}	

	void dibujar(Renderizador* motor) override;
};