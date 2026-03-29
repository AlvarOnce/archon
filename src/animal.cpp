#include "animal.h"

void Animal::mover(modoJuego m)  // Para que el animal sepa que tipo de movimiento debe realizar, se le debe indicar en que modo estamos
{

    switch (m) {

    case TABLERO: // Se llama desde tablero con animal.mover(TABLERO)


        break;

    case BATALLA: // Se llama desde batalla con animal.mover(BATALLA)


        break;
    }


}

void Animal::dibujar(Renderizador* motor)
{

}