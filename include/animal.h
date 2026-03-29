#pragma once
#include <iostream>
#include "ETSIDI.h"
#include "renderizador.h"

enum modoJuego
{
	TABLERO,
	BATALLA
};

class Animal {

	// Lógica

	float posx_;
	float posy_;
	float capaz_;
	
	float velx_;
	float vely_;

	int equipo;

	void mover(modoJuego m);
	virtual void atacar()
	{
		std::cout << "Soy un animal genérico, mi ataque no está definido.";
	}

	// Dibujo 

	int ancho;
	int alto;
	ETSIDI::SpriteSequence* visual; // Esta línea le permite a la clase Animal acceder a métodos de la clase SpriteSequence (Composición)


public:

	float getPosX() const { return posx_; }
	float getPosY() const { return posy_; }

	float getVelX() const { return velx_; }
	float getVelY() const { return vely_; }

protected: // Solo los hijos animales pueden modificar sus posiciones

	void setPosX(float posx) { posx_ = posx;}
	void setPosy(float posy) { posy_ = posy; }

	void setVelX(float velx) { velx_ = velx; } // Es probable que las velocidades sean fijas, en cuyo caso, se eliminarían los setvel();
	void setVelY(float vely) { vely_ = vely; }

	void dibujar(Renderizador* motor);


};
