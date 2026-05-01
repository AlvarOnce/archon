#include "animal.h"

Animal::Animal(float posx, float posy, float capa, int vida) 
    : posx_(posx), posy_(posy), capaz_(capa), vida_(vida){
        
}
void Animal::actualizar(float dt) {

    if (!en_movimiento_) {
        animar(dt);
        return;
    }
    // movimiento podriamos usar Vector 2D
	posx_ += velx_*dt/25;     
    posy_ += vely_*dt/25;      

    avanzando_casilla_ += abs(velx_ )*dt/25 + abs(vely_)*dt/25;

    if (avanzando_casilla_ >= 22) { // si el animal se ha movido más de una casilla, se para
        velx_ = 0;
        vely_ = 0;
        avanzando_casilla_ = 0;
		en_movimiento_ = false;
	}

    animar(dt);
}

bool Animal::mover(modoJuego modo, direccion dir){   // Para que el animal sepa que tipo de movimiento debe realizar, se le debe indicar en que modo estamos
    // Agregar dt en los cambios de posición

    switch (modo) {

    case TABLERO: // Se llama desde tablero con animal.mover(TABLERO, direccion)

		en_movimiento_ = true;
        if (dir == R)           velx_ = 1, casillas_movidas_x_++; // optimizable
        else if (dir == L)      velx_ = -1, casillas_movidas_x_--;
        else if (dir == U)      vely_ = 1, casillas_movidas_y_++;
        else if (dir == D)      vely_ = -1, casillas_movidas_y_--;

        else if (dir == UR)     velx_ = 0.71, vely_ = 0.71; //avance = -(2*0.71)+ 1;
        else if (dir == UL)     velx_ = -0.71, vely_ = 0.71;
        else if (dir == DR)     velx_ = 0.71, vely_ = -0.71;         //como hariamos para que le llegue la señal de que queremos diagonal??
        else if (dir == DL)     velx_ = -0.71, vely_ = -0.71;        //se podria hacer con las teclas e y q, z y c, pero no lo veo

        casillas_movidas_ = abs(casillas_movidas_x_) + abs(casillas_movidas_y_);
        if (casillas_movidas_ > getMaxCasillasMovidas()) return mover(CANCELAR, dir);
		else return true;


    case BATALLA: // Se llama desde batalla con animal.mover(BATALLA, direccion)

        return false;

	case CANCELAR: 
        velx_ = 0;
        vely_ = 0;
        if (dir == R)       casillas_movidas_x_--; 
        else if (dir == L)  casillas_movidas_x_++;
        else if (dir == U)  casillas_movidas_y_--;
        else if (dir == D)  casillas_movidas_y_++;
		en_movimiento_ = false;


        return false;
    }
	return false;

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