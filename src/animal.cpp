#include "animal.h"

Animal::Animal(float posx, float posy, float capa, int vida) {

    posx_ = posx;
    posy_ = posy;
    vida_ = vida;
    capaz_ = capa;
}
void Animal::actualizar(float dt) {

    // movimiento
	posx_ = posx_ + velx_;      //antes esto era velx_ * dt, pero
    posy_ = posy_ + vely_;      // no le veia el sentido, me da miedo haberlo quitado
    avance_ = avance_ + abs(velx_ ) + abs(vely_);
    if (avance_ >= 22) { // si el animal se ha movido más de una casilla, se para
        velx_ = 0;
        vely_ = 0;
        avance_ = 0;
		en_movimiento_ = false;
	}

    animar(dt);
}

void Animal::mover(modoJuego modo, direccion dir)  // Para que el animal sepa que tipo de movimiento debe realizar, se le debe indicar en que modo estamos
{
    // Agregar dt en los cambios de posición

    switch (modo) {

    case TABLERO: // Se llama desde tablero con animal.mover(TABLERO, direccion)

		en_movimiento_ = true;
        if (dir == R) velx_ = 1; // optimizable
        if (dir == L) velx_ = -1;
        if (dir == U) vely_ = 1;
        if (dir == D) vely_ = -1;

        if (dir == UR) velx_ = 0.71, vely_ = 0.71; //avance = -sqrt(2) + 1;
        if (dir == UL) velx_ = -0.71, vely_ = 0.71;
        if (dir == DR) velx_ = 0.71, vely_ = -0.71;
        if (dir == DL) velx_ = -0.71, vely_ = -0.71;

        break;

    case BATALLA: // Se llama desde batalla con animal.mover(BATALLA, direccion)

        break;
    }

}

void Animal::animar(float dt) {

        timer = timer + dt;
        if (timer > msStep)
        {
            if (frameActualX_ < nFrames-1) frameActualX_++;
            else frameActualX_ = 0;
            timer = timer - msStep;
        }

}



void Animal::setState(int frameX, int frameY) {

    frameActualX_ = frameX;
    frameActualY_ = frameY;
    pausa = true;

}


void Animal::dibujar(Renderizador* motor)
{
    
}