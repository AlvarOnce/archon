#pragma once
#include "renderizador.h"

class Transicion {

public:

    bool activo = false;
    float tamano = 600;

    enum Estado{ESPERANDO, CERRANDO, CERRADO, ABRIENDO};
    Estado estado = ESPERANDO;
   
 
    Estado getEstado() { return estado; }
    void empieza() { activo = true;}
    void termina() { activo = false;}

    void actualizar(float dt);
    void dibujar(Renderizador* motor);
};
