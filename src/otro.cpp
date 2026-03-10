#include "freeglut.h"
#include "ETSIDI.h"
#include "otro.h"

void Dibujar(const char* rutaImagen,double tam, double posx, double posy) 
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(rutaImagen).id); //Ruta foto

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //Estos dos mejoran calidad imagen
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(-tam, -tam, -0.1);  // abajo izquierda
	glTexCoord2d(1, 1);    glVertex3f(tam, -tam, -0.1);   // abajo derecha
	glTexCoord2d(1, 0);    glVertex3f(tam, tam, -0.1);    // arriba derecha
	glTexCoord2d(0, 0);    glVertex3f(-tam, tam, -0.1);   // arriba izquierda
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	return;
}