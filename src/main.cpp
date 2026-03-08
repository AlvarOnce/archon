#include "placeholder.h" // Biblioteca vacía
#include "iostream"
#include "ETSIDI.h" // Biblioteca para sprites y sonidos
#include "freeglut.h" // Biblioteca de ventana, dibujo y manejo teclado


// los callback, funciones que seran llamadas automaticamente por la glut cuando sucedan eventos (NO HACE FALTA LLAMARLAS EXPLICITAMENTE)
void OnDraw(void);		 // llamada para dibujar
void OnTimer(int value); // llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); // cuando se pulse una tecla	

float angulo = 0;

int main(int argc, char* argv[])
{
	std::cout << "Iniciando Rancho";
	ETSIDI::playMusica("../assets/Audio/ranchoMainTheme.mpeg", true);
	
	//Inicializar el gestor de ventanas GLUT y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Rancho");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);

	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

}

void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(20,10,-10,  // posición del ojo
		0.0, 0, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y) 

	glColor3ub(200, 200, 100);
	glutSolidCube(5);

	glRotated(angulo, 1, 0, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("../assets/Sprites/tablero y escenario/tablero.png").id); //Ruta foto

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //Estos dos mejoran calidad imagen
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(-8, 0, -0.1);  // coordenada (0,1) textura se asocia con vertice de arriba izquierda
	glTexCoord2d(1, 1);    glVertex3f(8, 0, -0.1);  // lo mismo pero (1,1) es arriba derecha
	glTexCoord2d(1, 0);	    glVertex3f(8, 8, -0.1);
	glTexCoord2d(0, 0);   	glVertex3f(-8, 8, -0.1);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();	// no borrar esta linea ni poner nada despues
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{

}

void OnTimer(int value)
{
	angulo+=2;
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}