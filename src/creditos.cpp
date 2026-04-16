#include "creditos.h"

void GallinaCreditos::animar(float dt) {

    timer = timer + dt;
    if (timer > msStep)
    {
        if (frameActualX_ < nFrames - 1) frameActualX_++;
        else frameActualX_ = 0;
        timer = timer - msStep;
    }

}

void Creditos::reset() {

    posx_ = 726 ;
    posy_ = 135;
    fin_ = false;
}

void Creditos::actualizar(float dt) {

    if (posx_ > posFinal_)
        posx_ -= 0.8;
    else
        fin_ = true;

    gallina.animar(dt);

}


void Creditos::dibujar(Renderizador* motor) {

    motor->dibujarSprite("../assets/Sprites/creditos/creditos.png", 2048, 512, posx_, posy_, -1);
    motor->dibujarSprite("../assets/Sprites/creditos/gallinaCreditos.png", 3*256, 3*32, gallina.posx_, gallina.posy_, -2, 1, 8, gallina.frameActualX_, gallina.frameActualY_);
  

}


