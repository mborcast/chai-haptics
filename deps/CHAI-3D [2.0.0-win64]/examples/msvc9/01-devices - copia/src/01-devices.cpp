/********************************************
*
*	Programa ejemplo, inicializaci�n del dispositivo h�ptico
*   y creaci�n de mundo virtual usando cMesh (tri�ngulos)
*	Taller de aplicaciones con h�pticos
*	usando chai3d
*
*   Autor: Eusebio Ric�rdez V�zquez
*********************************************/

#include "stdafx.h"
#include "chai3d.h"

//------------------------------------------------------------
//Definici�n de variables globales
// El mundo que contendr� todo
cWorld* world;

// La camara a trav�s de la cual observaremos el mundo
cCamera* camera;

// Fuente de luz
cLight *light;

cTexture2D* texture;
// Ancho y alto de la pantalla gr�fica
int displayW = 0;
int displayH = 0;

// Dimensiones que tendr� la pantalla gr�fica
const int WINDOW_SIZE_W = 600;
const int WINDOW_SIZE_H = 600;

// Opciones para el menu del rat�n 
const int OPTION_FULLSCREEN = 1;
const int OPTION_WINDOWDISPLAY = 2;

// Manejador del dispositivo h�ptico
cHapticDeviceHandler *handler;

// avatar del dispositivo virtual
cGeneric3dofPointer* tool;

// Objeto hecho de triangulos
cMesh* object;

// Variable de control para la simulaci�n
bool simulationRunning = false;

// Variable para detectar el fin de la simulaci�n
bool simulationFinished = false;

//---------------------------------------------------------------------------
// Prototipos de funciones
//---------------------------------------------------------------------------

// funci�n de resize para OpenGL
void resizeWindow(int w, int h);

// Detecci�n de teclas 
void keySelect(unsigned char key, int x, int y);

// Menu para el mouse
void menuSelect(int value);

// Funci�n para terminar las ejecuciones antes de cerrar
void close(void);

// Rutina gr�fica principal
void updateGraphics(void);

// Rutina principal h�ptica
void updateHaptics(void);


int main(int argc, char* argv[])
{
	//-----------------------------------------------------------------------
	// INICIALIZACION
	//-----------------------------------------------------------------------

	printf("\n");
	printf("-----------------------------------\n");