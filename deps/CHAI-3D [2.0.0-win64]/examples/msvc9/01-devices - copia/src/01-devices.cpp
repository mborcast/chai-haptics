/********************************************
*
*	Programa ejemplo, inicialización del dispositivo háptico
*   y creación de mundo virtual usando cMesh (triángulos)
*	Taller de aplicaciones con hápticos
*	usando chai3d
*
*   Autor: Eusebio Ricárdez Vázquez
*********************************************/

#include "stdafx.h"
#include "chai3d.h"

//------------------------------------------------------------
//Definición de variables globales
// El mundo que contendrá todo
cWorld* world;

// La camara a través de la cual observaremos el mundo
cCamera* camera;

// Fuente de luz
cLight *light;

cTexture2D* texture;
// Ancho y alto de la pantalla gráfica
int displayW = 0;
int displayH = 0;

// Dimensiones que tendrá la pantalla gráfica
const int WINDOW_SIZE_W = 600;
const int WINDOW_SIZE_H = 600;

// Opciones para el menu del ratón 
const int OPTION_FULLSCREEN = 1;
const int OPTION_WINDOWDISPLAY = 2;

// Manejador del dispositivo háptico
cHapticDeviceHandler *handler;

// avatar del dispositivo virtual
cGeneric3dofPointer* tool;

// Objeto hecho de triangulos
cMesh* object;

// Variable de control para la simulación
bool simulationRunning = false;

// Variable para detectar el fin de la simulación
bool simulationFinished = false;

//---------------------------------------------------------------------------
// Prototipos de funciones
//---------------------------------------------------------------------------

// función de resize para OpenGL
void resizeWindow(int w, int h);

// Detección de teclas 
void keySelect(unsigned char key, int x, int y);

// Menu para el mouse
void menuSelect(int value);

// Función para terminar las ejecuciones antes de cerrar
void close(void);

// Rutina gráfica principal
void updateGraphics(void);

// Rutina principal háptica
void updateHaptics(void);


int main(int argc, char* argv[])
{
	//-----------------------------------------------------------------------
	// INICIALIZACION
	//-----------------------------------------------------------------------

	printf("\n");
	printf("-----------------------------------\n");