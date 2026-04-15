#pragma once
#include "cursor.h"
#include "animal.h"

class Renderizador; // Forward declaration

class Jugador {
public:
    Jugador();
    ~Jugador();
    
    Cursor cursor;
    Animal* animales[9]; // Array de animales del jugador

    void inicializar(int numAnimales);
    void agregarAnimal(int indice, Animal* animal);
    void limpiar();

    void actualizar(float dt);
    void dibujar(Renderizador* motor);

private:

    int numAnimales;
};