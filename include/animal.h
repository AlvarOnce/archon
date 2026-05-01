#pragma once
#include <iostream>
#include "ETSIDI.h"
#include "renderizador.h"

enum modoJuego
{
	TABLERO, BATALLA, CANCELAR
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
	float avanzando_casilla_ = 0; // para saber cuanto se ha movido el animal, y asi saber cuando parar la animacion de caminar
	bool en_movimiento_ = false;
	int casillas_movidas_x_ = 0;
	int casillas_movidas_y_ = 0;
	int casillas_movidas_ = 0; 
	int max_casillas_movidas_ = 100; // esto se puede modificar en cada clase hija, para que cada animal tenga un número de casillas a mover diferente

	int casillaInicial_[2];

	bool mover(modoJuego modo, direccion dir);
	virtual void atacar()
	{
		std::cout << "Soy un animal genérico, mi ataque no está definido.";
	}

	float getPosX() const { return posx_; }
	float getPosY() const { return posy_; }
	float getVelX() const { return velx_; }
	float getVelY() const { return vely_; }
	bool getEnMovimiento() const { return en_movimiento_; }
	int getMaxCasillasMovidas() const { return max_casillas_movidas_; }

//protected: // Solo los hijos animales pueden modificar sus posiciones

	void setPosX(float posx) { posx_ = posx;}
	void setPosy(float posy) { posy_ = posy; }
	void setVelX(float velx) { velx_ = velx; } 
	void setVelY(float vely) { vely_ = vely; }
	void setEnMovimiento(bool en_movimiento) { en_movimiento_ = en_movimiento; }

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
