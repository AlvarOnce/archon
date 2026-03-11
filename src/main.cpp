#include "placeholder.h" // Biblioteca vacía
#include "iostream"
#include "ETSIDI.h" // Biblioteca para sprites y sonidos
#include "freeglut.h" // Biblioteca de ventana, dibujo y manejo teclado

#include "dibujar.h"
#include "menu.h"


// los callback, funciones que seran llamadas automaticamente por la glut cuando sucedan eventos (NO HACE FALTA LLAMARLAS EXPLICITAMENTE)
void OnDraw(void);		 // llamada para dibujar
void OnTimer(int value); // llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); // cuando se pulse una tecla	
void OnSpecialDown(int key, int x, int y); // cuando se pulse una tecla	

enum estadosPosibles
{
	MENU,
	CREDITOS,
	TABLERO,
	BATALLA
};

estadosPosibles estado = MENU;

float tamano = 40;
float x = 0, y = 0;
double ancho = 160, alto = 90;


int main(int argc, char* argv[])
{
	std::cout << "Iniciando Rancho...\n";
	ETSIDI::playMusica("../assets/Audio/ranchoMainTheme.mpeg", true);
	
	//Inicializar el gestor de ventanas GLUT y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(1920,1080);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Rancho");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);
	glDisable(GL_LIGHTING);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, ancho, 0, alto,50,-50); // en vez de gluPerspective( 40.0, 800/600.0f, 0.1, 150);
	glutFullScreen();
	
		//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(OnKeyboardDown);
	glutSpecialFunc(OnSpecialDown);

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

	//gluLookAt(0,0,-40,  // posición del ojo
	//	0.0, 0, 0.0,      // hacia que punto mira  (0,0,0) 
	//	0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y) 

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(40, 45, 0);
	glutSolidSphere(10, 20, 20);
	glTranslated(40, 0, -8);
	glutSolidSphere(10, 20, 20);
	glTranslated(40, 0, -8);
	glutSolidSphere(10, 20, 20);
	glPopMatrix();

	switch (estado)
	{

	case MENU:
		mostrarMenu();

		break;


	default:
		break;

	}


	Dibujar("../assets/Sprites/tablero y escenario/tablero.png",0,0,-2,tamano, tamano); //Función propia en otro.cpp para dibujar de forma más fácil
	Dibujar("../assets/Sprites/Pruebas/borrar20-Sheet.png", x, y, -3, 20.0, 20.0);

	glutSwapBuffers();	// no borrar esta linea ni poner nada despues
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	if (key == 27)  // Al pulsar "Esc", cierra la ventana gráfica.
		exit(0);
	
	if (key == '+') 
		tamano++;

	if (key == '-') 
		tamano--;
}

void OnSpecialDown(int key, int x_t, int y_t)
{
	if (key == GLUT_KEY_RIGHT) 
		x++;
	
	if (key == GLUT_KEY_LEFT) 
		x--;

	if (key == GLUT_KEY_UP)
		y++;

	if (key == GLUT_KEY_DOWN)
		y--;
}

void OnTimer(int value)
{
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}