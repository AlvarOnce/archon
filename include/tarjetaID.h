#pragma once
#include "renderizador.h"
#include "animal.h"

class Tarjeta {

public:

	Animal* animalSeleccionado = nullptr;
	enum lado {IZQ = 69, DER = 480 - 69};
	float posy = 32;


	void dibujar(Renderizador* motor);

};
