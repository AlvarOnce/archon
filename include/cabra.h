#pragma once
#include "animal.h"

class Cabra: public Animal {

public:


	Cabra(float posx,float posy, float capa, int vida ) : Animal(posx,posy,capa,vida) {

		frameActualX = 0;
	    frameActualY = 0;

	}	

	void actualizar(float dt) override;
	void dibujar(Renderizador* motor) override;
};