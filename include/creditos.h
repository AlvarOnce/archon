#pragma once
#include "renderizador.h"

class Creditos {

public:

	float posx_{ 726 };
	float posy_{ 135 };
	float capaz_;

	void actualizar(float dt);
	void dibujar(Renderizador* motor);
};