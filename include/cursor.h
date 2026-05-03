#pragma once
#include "renderizador.h"

class Cursor {

public:

	int posx = 240;			//esto antes eran floats, los he cambiado
	int posy = 135;
	int columna = 4;
	int fila = 4;
	void mover(int x, int y);
	void dibujar(Renderizador* motor);

};
