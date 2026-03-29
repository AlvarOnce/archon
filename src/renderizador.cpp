#include "renderizador.h"

void Renderizador::limpiarPantalla() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderizador::dibujarSprite(const char* rutaImagen, float posx, float posy, float posz, float ancho, float alto) {
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(rutaImagen).id); // ruta foto

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // mejora calidad
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_LIGHTING);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);

    // ahora posicion x e y corresponden a centro de imagen
    glTexCoord2d(0, 1);    glVertex3f(posx - ancho / 2, posy - alto / 2, posz); // abajo izquierda
    glTexCoord2d(1, 1);    glVertex3f(posx + ancho / 2, posy - alto / 2, posz); // abajo derecha
    glTexCoord2d(1, 0);    glVertex3f(posx + ancho / 2, posy + alto / 2, posz); // arriba derecha
    glTexCoord2d(0, 0);    glVertex3f(posx - ancho / 2, posy + alto / 2, posz); // ariiba izquierda

    glEnd();
    //glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}