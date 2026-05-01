#pragma once
#include "animal.h"

class Cabra: public Animal {

	

public:


	Cabra(float posx,float posy, float capa, int vida, float xinicial ) 
		: Animal(posx,posy,capa,vida,xinicial) {

		max_casillas_movidas_ = 3;
		nFrames = 5;
		setState(0, 0);

	}

	//void actualizar(float dt) override;
	void dibujar(Renderizador* motor) override;
};