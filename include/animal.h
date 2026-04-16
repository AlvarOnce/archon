#pragma once
#include <iostream>
#include "ETSIDI.h"
#include "renderizador.h"

enum modoJuego { TABLERO, BATALLA };
enum animacionTipo { QUIETO, CAMINAR, ATACAR };
enum direccion { R, L, U, D, UR, UL, DR, DL };

class Animal {

public:
	Animal(float posx, float posy, float capa, int vida, int equipo);
	virtual ~Animal() {}
	
	void mover(modoJuego modo, direccion dir);
	virtual void atacar()
	{
		std::cout << "Soy un animal genérico, mi ataque no está definido.";
	}

	float getPosX() const { return posx_; }
	float getPosY() const { return posy_; }
	float getVelX() const { return velx_; }
	float getVelY() const { return vely_; }
	int obtenerBando() const { return equipo_; }

	virtual void actualizar(float dt);
	virtual void dibujar(Renderizador* motor);
	virtual void dibujarEnCoordenadas(Renderizador* motor, float xPixel, float yPixel);

protected: // Solo los hijos animales pueden modificar sus posiciones
	float posx_{ 100 };
	float posy_{ 100 };
	float capa_;
	float velx_{ 0 };
	float vely_{ 0 };
	int equipo_;
	int vida_;

	void setPosX(float posx) { posx_ = posx;}
	void setPosy(float posy) { posy_ = posy; }
	void setVelX(float velx) { velx_ = velx; } // Es probable que las velocidades sean fijas, en cuyo caso, se eliminarían los setvel();
	void setVelY(float vely) { vely_ = vely; }

	// Dibujo y animación
	int frameActualX = 0;
	int frameActualY = 1;
	float timer = 0;
	float msStep = 100;
	int ancho;
	int alto;
};
