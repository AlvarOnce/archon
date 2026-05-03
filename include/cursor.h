#pragma once
#include "renderizador.h"

class Cursor {

public:

	float posx = 240;			
	float posy = 135;
	int columna = 4;
	int fila = 4;
	void mover(int x, int y);
	void dibujar(Renderizador* motor);

};
