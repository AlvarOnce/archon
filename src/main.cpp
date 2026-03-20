#include "placeholder.h" // Biblioteca vacía
#include "iostream"
#include "ETSIDI.h" // Biblioteca para sprites y sonidos
#include "freeglut.h" // Biblioteca de ventana, dibujo y manejo teclado

#include "dibujar.h"
#include "menu.h"

//cambio para segio

// los callback, funciones que seran llamadas automaticamente por la glut cuando sucedan eventos (NO HACE FALTA LLAMARLAS EXPLICITAMENTE)
void OnDraw(void);		 // llamada para dibujar
void OnTimer(int value); // llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); // cuando se pulsa una tecla	
void OnSpecialDown(int key, int x, int y); // cuando se pulsa una tecla	
void OnSpecialUp(int key, int x, int y); // cuando se suelta la tecla

// interruptores para saber que flechas están pulsadas, IDEA: hacer una clase?
bool teclaArriba = false;
bool teclaAbajo = false;
bool teclaDerecha = false;
bool teclaIzquierda = false;

enum estadosPosibles
{
	MENU,
	CREDITOS,
	TABLERO,
	BATALLA
};

estadosPosibles estado = TABLERO;

float tamano = 40;
double ancho = 160, alto = 90;
float x = ancho/2, y = alto/2;

int main(int argc, char* argv[])
{
	std::cout << "Iniciando Rancho...\n";
	ETSIDI::playMusica("../assets/Audio/ranchoMainTheme.mpeg", true);
	
	//Inicializar el gestor de ventanas GLUT y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(160,90);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Rancho");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
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
	glutSpecialUpFunc(OnSpecialUp);


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

	// Estados posibles del juego
	switch (estado)
	{
	case MENU:
		mostrarMenu();
		break;

	default:
		break;
	}

	Dibujar("../assets/Sprites/tablero y escenario/tablero.png",ancho/2,alto/2,1,tamano, tamano); //Función propia en otro.cpp para dibujar de forma más fácil
	Dibujar("../assets/Sprites/Pruebas/borrar20-Sheet.png", x, y, 0, 20, 20);

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

	if (key == 13) // enter
	{

	}
}

void OnSpecialDown(int key, int x_t, int y_t)
{
	if (key == GLUT_KEY_RIGHT) teclaDerecha = true;
	if (key == GLUT_KEY_LEFT)  teclaIzquierda = true;
	if (key == GLUT_KEY_UP)    teclaArriba = true;
	if (key == GLUT_KEY_DOWN)  teclaAbajo = true;
}

void OnSpecialUp(int key, int x_t, int y_t)
{
	if (key == GLUT_KEY_RIGHT) teclaDerecha = false;
	if (key == GLUT_KEY_LEFT)  teclaIzquierda = false;
	if (key == GLUT_KEY_UP)    teclaArriba = false;
	if (key == GLUT_KEY_DOWN)  teclaAbajo = false;
}

void OnTimer(int value)
{
	// conversion de flechas a dos direcciones que pueden ser + o -
	float dirX = 0;
	float dirY = 0;

	if (teclaDerecha)  dirX += 1;
	if (teclaIzquierda) dirX -= 1;
	if (teclaArriba)    dirY += 1;
	if (teclaAbajo)     dirY -= 1;

	// si nos movemos en diagonal, normalizamos con raiz de 2
	if (dirX != 0 && dirY != 0) {
		dirX *= 0.7071f;
		dirY *= 0.7071f;
	}

	// aplicamos el movimiento multiplicado por la velocidad que queramos
	float velocidad = 1.0f; // velocidad modificable

	x += dirX * velocidad;
	y += dirY * velocidad;

	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}