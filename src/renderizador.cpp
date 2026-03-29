#include "renderizador.h"

void Renderizador::limpiarPantalla() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderizador::dibujarSprite(const char* rutaImagen, float ancho, float alto, float posx, float posy, float capa) {
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
    glColor3f(1, 1, 1);

    glPushMatrix();  // El renderizador se encarga de mover el origen antes de dibujar en el (0,0)
    glTranslatef(posx, posy, capa); // ahora posicion (x,y) en su capa (capa) corresponden a centro de imagen
    glBegin(GL_POLYGON);
    glTexCoord2d(0, 1);    glVertex3f( - ancho / 2,  - alto / 2, 0); // abajo izquierda
    glTexCoord2d(1, 1);    glVertex3f(  ancho / 2,  - alto / 2, 0); // abajo derecha
    glTexCoord2d(1, 0);    glVertex3f(  ancho / 2,   alto / 2, 0); // arriba derecha
    glTexCoord2d(0, 0);    glVertex3f( - ancho / 2,   alto / 2, 0); // ariiba izquierda
    glEnd();
    glPopMatrix();

    //glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
}