#include "freeglut.h"
#include "ETSIDI.h"
#include "dibujar.h"

void Dibujar(const char* rutaImagen, float posx, float posy, float posz, float ancho, float alto)
{
	glEnable(GL_TEXTURE_2D);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(rutaImagen).id); //Ruta foto

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //Estos dos mejoran calidad imagen
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0.0, 1.0);    glVertex3f(posx, posy, posz);  // Abajo izquierda
	glTexCoord2d(1.0, 1.0);    glVertex3f(posx + ancho, posy, posz);   // Abajo derecha
	glTexCoord2d(1.0, 0.0);    glVertex3f(posx + ancho, posy + alto, posz);    // Arriba derecha
	glTexCoord2d(0.0, 0.0);    glVertex3f(posx, posy + alto,posz);   // Arriba izquierda

	// Estas funciones ponen la posicion x e y de la imagen en su esquina inferior izq. Además suponen que la imagen es un 
	// cuadrado de lado tam, lo que hay que solucionar cambiando los parametros al pedir un dibujo desde main con Dibujar().

	glEnd();
	//glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	return;
}