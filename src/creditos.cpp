#include "creditos.h"


void Creditos::actualizar(float dt) {

    posx_-= 0.8;
}


void Creditos::dibujar(Renderizador* motor) {

    motor->dibujarSprite("../assets/Sprites/creditos/creditos.png", 2048, 512, posx_, posy_, -1);

}