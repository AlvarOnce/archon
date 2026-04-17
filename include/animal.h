#pragma once
#include <iostream>
#include "ETSIDI.h"
#include "renderizador.h"

enum modoJuego
{
	TABLERO, BATALLA
};

enum animacionTipo
{
	QUIETO, CAMINAR, ATACAR,
};

enum direccion
{
	R, L, U, D, UR, UL, DR, DL
};

class Animal {

public:

	Animal(float posx, float posy, float capa, int vida);

	virtual ~Animal() {}
	
	// Lógica
	float posx_{ 100 };
	float posy_{ 100 };
	float capaz_;
	float velx_{0};
	float vely_{0};
	int equipo_;
	int vida_;
	int ataque_;

	int casillaInicial_[2];

	void mover(modoJuego modo, direccion dir);
	virtual void atacar()
	{
		std::cout << "Soy un animal genérico, mi ataque no está definido.";
	}

	float getPosX() const { return posx_; }
	float getPosY() const { return posy_; }
	float getVelX() const { return velx_; }
	float getVelY() const { return vely_; }

//protected: // Solo los hijos animales pueden modificar sus posiciones

	void setPosX(float posx) { posx_ = posx;}
	void setPosy(float posy) { posy_ = posy; }
	void setVelX(float velx) { velx_ = velx; } 
	void setVelY(float vely) { vely_ = vely; }

	// Dibujo y animación
	int frameActualX_ = 0;
	int frameActualY_ = 1;
	int nFrames;
	float timer = 0;
	float msStep = 100;
	bool pausa = true;
	int ancho;
	int alto;
	void setState(int frameX, int frameY);
	void animar(float dt);

	virtual void actualizar(float dt);
	virtual void dibujar(Renderizador* motor);

};
