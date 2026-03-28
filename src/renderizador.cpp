#include "renderizador.h"

void Renderizador::limpiarPantalla() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Codigo del antiguo dibujar.cpp 
void Renderizador::dibujarSprite(const char* rutaImagen, float posx, float posy, float posz, float ancho, float alto) {
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Llama a la librería de la ETSIDI para obtener la textura
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(rutaImagen).id);

    // Filtros pixel-art
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_LIGHTING);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);

    glTexCoord2d(0, 1);    glVertex3f(posx - ancho / 2, posy - alto / 2, posz);
    glTexCoord2d(1, 1);    glVertex3f(posx + ancho / 2, posy - alto / 2, posz);
    glTexCoord2d(1, 0);    glVertex3f(posx + ancho / 2, posy + alto / 2, posz);
    glTexCoord2d(0, 0);    glVertex3f(posx - ancho / 2, posy + alto / 2, posz);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Renderizador::dibujarMenu() {
    // dibujarSprite("../assets/Sprites/", ...);
}

void Renderizador::dibujarFondoTablero() {
    
    dibujarSprite("../assets/Sprites/tablero y escenario/tablero.png", 80, 45, 1, 40, 40);
}

void Renderizador::dibujarFondoArena() {
    // dibujarSprite("../assets/Sprites/tablero y escenario/arena.png", ...);
}