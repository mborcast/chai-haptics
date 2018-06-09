#include "stdafx.h"
#include "chai3d.h"
 
#include "Simulation.h"

const int WINDOW_SIZE_W = 800;
const int WINDOW_SIZE_H = 600;

double currentWidth = 0;
double currentHeight = 0;

void resizeWindow(int w, int h);
void keySelect(unsigned char key, int x, int y);
void updateGraphics(void);
void updateHaptics(void);
void close(void);

cPrecisionClock simClock;

cThread* hapticsThread;

Simulation* simulation;

void updateGraphics(void) {

	simulation->renderCamera(currentWidth, currentHeight);

	glutSwapBuffers();

	if (glGetError() != GL_NO_ERROR) {
		printf("Error:  %s\n", gluErrorString(glGetError()));
	}
	if (simulation->isRunning) {
		glutPostRedisplay();
	}
}
void keySelect(unsigned char key, int x, int y) {
	switch (key) {
	case 27: case 'x':
		close();
		exit(0);
	}
}
void resizeWindow(int w, int h) {
	currentWidth = w;
	currentHeight = h;
	glViewport(0, 0, currentWidth, currentHeight);
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - WINDOW_SIZE_W) / 2, 
		(glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_SIZE_H) / 2
	);
	glutInitWindowSize(WINDOW_SIZE_W, WINDOW_SIZE_H);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(updateGraphics);
	glutKeyboardFunc(keySelect);
	glutReshapeFunc(resizeWindow);
	glutSetWindowTitle("Piston Haptics");

	simulation = new Simulation();

	hapticsThread = new cThread();
	hapticsThread->set(updateHaptics, CHAI_THREAD_PRIORITY_HAPTICS);

	glutMainLoop();

	return 0;
}
void close(void) {

	simulation->isRunning = false;

	while (!simulation->isFinished) { cSleepMs(100); }
	simulation->closeGracefully();
	delete simulation;
	delete hapticsThread;
}

void updateHaptics(void) {
	simClock.reset();
	double lDt = 0;

	while (simulation->isRunning) {
		simulation->updateHaptics();
		simClock.stop();

		simulation->update(simClock.getCurrentTimeSeconds());

		simClock.reset();
		simClock.start();

	}
	simulation->isFinished = true;
}